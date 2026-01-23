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

	if (id == Mission::QUINKING_PRE) {
		API::LogPluginMessage("GOALLLLL");
		ArchipelagoHandler::Release();
		return;
	}

	ArchipelagoHandler::SendLocation(0x6d00 + id);
	ArchipelagoHandler::customSaveData->CheckGoal();
}

void CheckHandler::OnBuyItem(void* itemPtr) {
	auto* item = reinterpret_cast<ItemStruct*>(reinterpret_cast<char*>(itemPtr));
	int id = item->itemId & 0xffff;
	ArchipelagoHandler::SendLocation(0x6900 + id);
	ArchipelagoHandler::customSaveData->updateBoughtItem(id, true);
	item->maxNumPurchased = 0;
}

void CheckHandler::OnGetShadowPiece(uintptr_t* shadowPiecePtr)
{
	auto mkObjId = *(uint32_t*)(shadowPiecePtr + 0x20);
	if (mkObjId != 10877 && mkObjId != 10878 && mkObjId != 10879)
		return;
	auto pieceIndex = mkObjId - 10876;
	ArchipelagoHandler::SendLocation(pieceIndex + 900);
}

void CheckHandler::OnFindItem(void* itemPtr) {
	auto* item = reinterpret_cast<ItemStruct*>(reinterpret_cast<char*>(itemPtr));
	auto& validShopItems = ShopHandler::validShopItems;
	int id = item->itemId & 0xffff;
	if (std::find(validShopItems.begin(), validShopItems.end(), id) != validShopItems.end())
		return;
	ArchipelagoHandler::SendLocation(0x6900 + id);
}


