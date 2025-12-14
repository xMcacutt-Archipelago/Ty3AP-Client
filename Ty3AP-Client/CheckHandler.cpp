#include "pch.h"
#include "CheckHandler.h"
typedef void(__stdcall* FunctionType)();

void CheckHandler::OnCollectCollectible(int type, int id) {
	if (type < 0 || type > 6)
		API::LogPluginMessage("Unknown collectible type: " + std::to_string(type));
	ArchipelagoHandler::SendLocation(0x4000 + type * 0x100 + id);
}

void CheckHandler::OnCompleteMission(void* missionPtr, int status) {
	if (status != (int)MissionState::COMPLETE && status != (int)MissionState::REPLAYABLE) 
		return;

	auto* mission = reinterpret_cast<MissionStruct*>(reinterpret_cast<char*>(missionPtr));
	int id = mission->missionId & 0xffff;

	ArchipelagoHandler::SendLocation(0x6d00 + id);
	ArchipelagoHandler::customSaveData->CheckGoal();

	if (id != 34)
		return;

	API::LogPluginMessage("GOALLLLL");
	ArchipelagoHandler::Release();
}

void CheckHandler::OnBuyItem(void* itemPtr) {
	auto* item = reinterpret_cast<ItemStruct*>(reinterpret_cast<char*>(itemPtr));
	int id = item->itemId & 0xffff;
	ArchipelagoHandler::SendLocation(0x6900 + id);
	ArchipelagoHandler::customSaveData->updateBoughtItem(id, true);
	item->maxNumPurchased = 0;
}


