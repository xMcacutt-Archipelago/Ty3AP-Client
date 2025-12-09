#include "pch.h"
#include "SaveDataHandler.h"

void createDirectoriesIfNeeded(const std::string& filepath) {
	std::filesystem::path path(filepath);
	std::filesystem::create_directories(path.parent_path());
}

int SaveDataHandler::RecalcSaveDataSize() {
	int size = 0;
	std::string filePath = "./Saves/" + ArchipelagoHandler::GetSaveIdentifier();
	createDirectoriesIfNeeded(filePath);
	std::ifstream file(filePath + ".bin", std::ios::binary);
	if (file.is_open()) {

		file.read(reinterpret_cast<char*>(&size), sizeof(int));
		file.close();
	}
	return size;
}

bool SaveDataHandler::doesSaveExist() {
	std::string filePath = "./Saves/" + ArchipelagoHandler::GetSaveIdentifier() + ".json";
	std::ifstream file(filePath);
	return file.good();
}

void SaveDataHandler::LoadAPSaveFile() {
	std::string filePath = "./Saves/" + ArchipelagoHandler::GetSaveIdentifier();
	/*API::LogPluginMessage(filePath);*/
	createDirectoriesIfNeeded(filePath);
	std::ifstream file(filePath + ".bin", std::ios::binary);
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		saveFileLength = file.tellg();
		file.seekg(0, std::ios::beg);
		if (saveFileLength > 0) {
			// Allocate buffer and read the rest of the file
			saveFileBuffer = new char[saveFileLength];
			if (!file.read(saveFileBuffer, saveFileLength)) {
				delete[] saveFileBuffer;
				saveFileBuffer = nullptr;
				saveFileLength = 0;
				//API::LogPluginMessage("Failed to read save file.");
			}
		}

		file.close();

		read_json_file(filePath + ".json");

		*(DWORD*)(Core::moduleBase + 0x4CBD78 + 0x238) = 1;

		g_SaveCallback.active = true;
		g_SaveCallback.esi = Core::moduleBase + 0x4CBD78;
		g_SaveCallback.framesRemaining = 5;
		g_SaveCallback.callback = []() {
			using CallbackFn = int(__thiscall*)(void* thisptr, void* arg1, int arg2);
			CallbackFn fn = (CallbackFn)(Core::moduleBase + 0x377AE0);

			void* thisptr = (void*)(Core::moduleBase + 0x4CBD78);

			uint8_t dataBuffer[] = {
				0x46, 0xC1, 0xF7, 0xCD,
				0x18, 0x74, 0xD7, 0x09,
				0x01, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00
			};

			dataBuffer[0x10] = (uint8_t)(saveFileLength & 0xFF);
			dataBuffer[0x11] = (uint8_t)((saveFileLength >> 8) & 0xFF);
			dataBuffer[0x12] = (uint8_t)((saveFileLength >> 16) & 0xFF);
			dataBuffer[0x13] = (uint8_t)((saveFileLength >> 24) & 0xFF);

			int arg2 = 0;

			// Call the function
			int result = fn(thisptr, dataBuffer, arg2);
			};

	}
	else {
		API::LogPluginMessage("Save file not found.");
		saveFileLength = 0;
		saveFileBuffer = nullptr;
	}
}

int SaveDataHandler::SaveFile(const char* filename, void* data, int size) {
	std::string filePath = "./Saves/" + ArchipelagoHandler::GetSaveIdentifier();
	createDirectoriesIfNeeded(filePath);
	FILE* f = nullptr;
	if (fopen_s(&f, (filePath + ".bin").c_str(), "wb") == 0 && f) {
		fwrite(data, 1, size, f);
		fclose(f);
		API::LogPluginMessage("Save file Saved.");
	}

	write_json_file(filePath + ".json");

	g_SaveCallback.esi = Core::moduleBase + 0xEB99A8;
	g_SaveCallback.framesRemaining = 5; // delay 5 frames
	g_SaveCallback.active = true;

	return 1;
}

void SaveDataHandler::write_json_file(const std::string& filename) {
	json j;

	// Populate the JSON object
	j["LastRecievedIndex"] = ArchipelagoHandler::customSaveData->pLastReceivedIndex;
	j["CogCount"] = SaveData::GetData()->CogCollected;
	j["OrbCount"] = SaveData::GetData()->OrbCollected;
	j["ShopData"] = ArchipelagoHandler::customSaveData->ItemMap;
	j["UnlockedParkingBays"] = ArchipelagoHandler::customSaveData->UnlockedParkingPads;
	j["UnlockedBarriers"] = ArchipelagoHandler::customSaveData->UnlockedBarriers;

	// Write to file
	std::ofstream file(filename);
	if (file.is_open()) {
		file << j.dump(4);  // pretty print with indent of 4
		file.close();
	}
	else {
		std::cerr << "Could not open file for writing: " << filename << std::endl;
	}
}

void SaveDataHandler::read_json_file(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return;
	}

	json j;
	file >> j;

	// Access data
	ArchipelagoHandler::customSaveData->pLastReceivedIndex = j["LastRecievedIndex"];
	ArchipelagoHandler::customSaveData->berryCount = j["BerryCount"];
	ArchipelagoHandler::customSaveData->orbCount = j["OrbCount"];
	ArchipelagoHandler::customSaveData->bilbyCount = j["BilbyCount"];
	ArchipelagoHandler::customSaveData->ItemMap = j["ShopData"].get<std::map<int, bool>>();
}

bool SaveDataHandler::hasRunSetup = false;
void SaveDataHandler::RunLoadSetup(SlotData* slotdata) {
	SaveData::GetData()->BerryCollected = ArchipelagoHandler::customSaveData->berryCount;
	SaveData::GetData()->OrbCollected = ArchipelagoHandler::customSaveData->orbCount;
	SaveData::GetData()->BilbyCollected = ArchipelagoHandler::customSaveData->bilbyCount;
	ShopHandler::SetShopItems(slotdata);

	ItemHandler::HandleStoredItems();

	hasRunSetup = true;
}