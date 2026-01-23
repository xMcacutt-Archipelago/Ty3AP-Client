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

		*(DWORD*)(Core::moduleBase + 0xEB99A8 + 0x238) = 1;

		g_SaveCallback.active = true;
		g_SaveCallback.esi = Core::moduleBase + 0xEB99A8;
		g_SaveCallback.framesRemaining = 5;
		g_SaveCallback.callback = []() {

			using CallbackFn = int(__thiscall*)(void* thisptr, void* arg1, int arg2);
			CallbackFn fn = (CallbackFn)(Core::moduleBase + 0x3477C0);

			void* thisptr = (void*)(Core::moduleBase + 0xEB99A8);

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
	nlohmann::json j;

	// Populate the JSON object
	j["LastRecievedIndex"] = ArchipelagoHandler::customSaveData->pLastReceivedIndex;
	j["BerryCount"] = SaveData::GetData()->berriesCollected;
	j["OrbCount"] = SaveData::GetData()->orbsCollected;
	j["BilbyCount"] = SaveData::GetData()->bilbiesCollected;
	j["ShopData"] = ArchipelagoHandler::customSaveData->ItemMap;
	j["UnlockedDuke"] = ArchipelagoHandler::customSaveData->hasUnlockedDuke;
	j["UnlockedSly"] = ArchipelagoHandler::customSaveData->hasUnlockedSly;
	j["UnlockedKarlos"] = ArchipelagoHandler::customSaveData->hasUnlockedKarlos;
	j["UnlockedFinal"] = ArchipelagoHandler::customSaveData->hasUnlockedFinal;
	j["UnlockedGate"] = ArchipelagoHandler::customSaveData->hasSouthernRiversGate;
	j["HasCrab"] = ArchipelagoHandler::customSaveData->hasCrab;
	j["UnlockedKakaboom"] = ArchipelagoHandler::customSaveData->hasUnlockedKakaboom;
	j["UnlockedBasin"] = ArchipelagoHandler::customSaveData->hasUnlockedBasin;
	j["UnlockedCinder"] = ArchipelagoHandler::customSaveData->hasUnlockedCinder;
	j["HasShadowChassis"] = ArchipelagoHandler::customSaveData->hasShadowChassis;
	j["ShadowStones"] = ArchipelagoHandler::customSaveData->shadowStoneCount;
	j["HasGauntlet"] = ArchipelagoHandler::customSaveData->hasGauntlet;
	j["AllowedActiveMissions"] = ArchipelagoHandler::customSaveData->allowedActiveMissions;
	j["BunyipMissionStatuses"] = ArchipelagoHandler::customSaveData->savedBunyipStatuses;
	j["HasUnlockedGully"] = ArchipelagoHandler::customSaveData->hasUnlockedGully;
	j["HasUnlockedMarsh"] = ArchipelagoHandler::customSaveData->hasUnlockedMarsh;

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

	nlohmann::json j;
	file >> j;

	// Access data
	ArchipelagoHandler::customSaveData->pLastReceivedIndex = j["LastRecievedIndex"];
	ArchipelagoHandler::customSaveData->berryCount = j["BerryCount"];
	ArchipelagoHandler::customSaveData->orbCount = j["OrbCount"];
	ArchipelagoHandler::customSaveData->bilbyCount = j["BilbyCount"];
	ArchipelagoHandler::customSaveData->ItemMap = j["ShopData"].get<std::map<int, bool>>();
	ArchipelagoHandler::customSaveData->hasUnlockedDuke = j["UnlockedDuke"] == 1;
	ArchipelagoHandler::customSaveData->hasUnlockedSly = j["UnlockedSly"] == 1;
	ArchipelagoHandler::customSaveData->hasUnlockedKarlos = j["UnlockedKarlos"] == 1;
	ArchipelagoHandler::customSaveData->hasUnlockedFinal = j["UnlockedFinal"] == 1;
	ArchipelagoHandler::customSaveData->hasSouthernRiversGate = j["UnlockedGate"] == 1;
	ArchipelagoHandler::customSaveData->hasCrab = j["HasCrab"] == 1;
	ArchipelagoHandler::customSaveData->hasUnlockedKakaboom = j["UnlockedKakaboom"] == 1;
	ArchipelagoHandler::customSaveData->hasUnlockedBasin = j["UnlockedBasin"] == 1;
	ArchipelagoHandler::customSaveData->hasUnlockedCinder = j["UnlockedCinder"] == 1;
	ArchipelagoHandler::customSaveData->hasShadowChassis = j["HasShadowChassis"] == 1;
	ArchipelagoHandler::customSaveData->shadowStoneCount = j["ShadowStones"];
	ArchipelagoHandler::customSaveData->hasGauntlet = j["HasGauntlet"] == 1;
	ArchipelagoHandler::customSaveData->allowedActiveMissions = j["AllowedActiveMissions"].get<std::set<int>>();
	ArchipelagoHandler::customSaveData->savedBunyipStatuses = j["BunyipMissionStatuses"];
	ArchipelagoHandler::customSaveData->hasUnlockedGully = j["HasUnlockedGully"] == 1;
	ArchipelagoHandler::customSaveData->hasUnlockedMarsh = j["HasUnlockedMarsh"] == 1;
}

bool SaveDataHandler::hasRunSetup = false;
void SaveDataHandler::RunLoadSetup(SlotData* slotdata) {
	SaveData::GetData()->berriesCollected = ArchipelagoHandler::customSaveData->berryCount;
	SaveData::GetData()->orbsCollected =    ArchipelagoHandler::customSaveData->orbCount;
	SaveData::GetData()->bilbiesCollected = ArchipelagoHandler::customSaveData->bilbyCount;
	ShopHandler::SetShopItems();
	ItemHandler::HandleStoredItems();
	hasRunSetup = true;
}