#include "pch.h"
#include "CheckHandler.h"
typedef void(__stdcall* FunctionType)();

void CheckHandler::OnCollectCollectible(int type, int id) {
	//dont send on sanity
	switch (type) {
	case 0: ArchipelagoHandler::SendLocation(('C' << 8) | id); break;
	case 1: ArchipelagoHandler::SendLocation(('B' << 8) | id); break;
	case 2: ArchipelagoHandler::SendLocation(('P' << 8) | id); break;
	case 3: ArchipelagoHandler::SendLocation(('K' << 8) | id); break;
	case 4: ArchipelagoHandler::SendLocation(('S' << 8) | id); break;
	case 5: ArchipelagoHandler::SendLocation(('F' << 8) | id); break;
	default:
		API::LogPluginMessage("Failure on collectable Type");
	}
	
	for (auto& window : GUI::windows) {
		if (auto infowindow = dynamic_cast<InfoWindow*>(window.get())) {
			infowindow->AddLogMessage(collectibles[type].name + " " +  std::to_string(id));
		}
	}
	//API::LogPluginMessage("maybe id: " + std::to_string(id) + " maybe type: " + std::to_string(type));
}

void CheckHandler::OnCompleteMission(void* mission, int status) {
	if (status != 5) {
		return;
	}

	uint8_t* base = static_cast<uint8_t*>(mission);
	//short status = *reinterpret_cast<short*>(base + 0x10); // read status
	
	int id = *reinterpret_cast<int*>(base + 0x4);
	int shortId = *reinterpret_cast<char*>(base + 0x4);

	if (shortId >= 980 && shortId <= 982) {
		return;
	}

	ArchipelagoHandler::SendLocation(id);

	short value = *reinterpret_cast<short*>(base + 0x4); // read short

	if (value == 83) { //this is the cass boss fight id
		API::LogPluginMessage("GOALLLLL");
		ArchipelagoHandler::Release();
	}
	char letter = *reinterpret_cast<char*>(base + 0x7);  // read char
	std::string Sid = std::string(1, letter) + std::to_string(value);
	for (auto& window : GUI::windows) {
		if (auto infowindow = dynamic_cast<InfoWindow*>(window.get())) {
			infowindow->AddLogMessage(Sid + " -> " + std::to_string(status));
		}
	}
	int missioncount = 0;
	SaveData::MissionList(5).forEach([&missioncount](MissionStruct m) {
		if (m.missionId < 100 && m.missionId != 86) {
			missioncount++;
		}
	});
	API::LogPluginMessage("misions done: " + std::to_string(missioncount) + " Need: " + std::to_string(ArchipelagoHandler::slotdata->missionsToGoal));
	if (missioncount >= ArchipelagoHandler::slotdata->missionsToGoal - 1) {
		auto mission = SaveData::findMissionByID(99);
		if (mission && mission->status == 0) {
			mission->numberPreconditionMissionNeeded = 0;
			Missions::UpdateMissionState(mission, 1, 0);
		}
	}
}

void CheckHandler::OnBuyItem(void* item) {
	uint8_t* base = static_cast<uint8_t*>(item);
	//short status = *reinterpret_cast<short*>(base + 0x10); // read status

	short value = *reinterpret_cast<short*>(base + 0x4); // read short
	char letter = *reinterpret_cast<char*>(base + 0x7);  // read char
	ArchipelagoHandler::customSaveData->updateBoughtItem(value, true);
	if (value >= 79 && value < 88) {
		if (auto nextItem = SaveData::findItemByID(SaveData::GetShopItemList(1), value + 1)) {
			nextItem->locked = false;
		}
	}

	if (value >= 5 && value < 7) {
		if (auto nextItem = SaveData::findItemByID(SaveData::GetShopItemList(4), value + 1)) {
			nextItem->locked = false;
		}
	}

	ArchipelagoHandler::SendLocation(value);

	std::string id = std::string(1, letter) + std::to_string(value);
	for (auto& window : GUI::windows) {
		if (auto infowindow = dynamic_cast<InfoWindow*>(window.get())) {
			infowindow->AddLogMessage("Buy " + id);
		}
	}
}


