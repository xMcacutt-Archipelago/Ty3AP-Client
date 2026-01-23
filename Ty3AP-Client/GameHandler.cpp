#include "pch.h"
#include "GameHandler.h"
using nlohmann::json;

void GameHandler::Initialize()
{
	MH_Uninitialize();
	MH_Initialize();
	Hooks::SetupHooks();
	MH_EnableHook(MH_ALL_HOOKS);
}

void GameHandler::SetToNoOperation(uintptr_t* address, size_t size) {
	DWORD oldProtect;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(address, 0x90, size);
	VirtualProtect(address, size, oldProtect, &oldProtect);
	FlushInstructionCache(GetCurrentProcess(), address, size);
}

void GameHandler::SetToJmp(uintptr_t* address) {
	DWORD oldProtect;
	VirtualProtect(address, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(address, 0xEB, 1);
	VirtualProtect(address, 1, oldProtect, &oldProtect);
	FlushInstructionCache(GetCurrentProcess(), address, 1);
}

void GameHandler::KillTy()
{
	if (GameState::IsInGame()) {
		auto transitionFunc = (StateTransitionFunc)(Core::moduleBase + 0x1608C0);
		auto ty = MKObject::GetMKObject(204);
		if (!ty) {
			return;
		}
		auto* tyStateHandler = (uintptr_t*)(ty + 0x530);
		int stateid = 0xe;
		int source = 9000;
		transitionFunc(tyStateHandler, stateid, source);
	}
}

void RestoreBunyipMissionStatuses() {
	for (const auto& [missionId, status] : ArchipelagoHandler::customSaveData->savedBunyipStatuses)
	{
		auto mission = SaveData::FindMissionById(missionId);
		if (mission->missionState != MissionState::COMPLETE && mission->missionState != MissionState::REPLAYABLE)
			mission->missionState = status;
	}
}

void GameHandler::OnWriteLevel(uintptr_t strPtr) {
	auto levelName = reinterpret_cast<const char*>(strPtr);
	std::string chunkNameStr(levelName);
	if (levelName == "O1" || levelName == "O2")
		RestoreBunyipMissionStatuses();
}

Bunyip selectedBunyip = Bunyip::SHADOW;
void GameHandler::OnChunkQueued(uintptr_t chunkPtr) {
	auto chunkName = reinterpret_cast<const char*>(chunkPtr);
	std::string chunkNameStr(chunkName);
	API::LogPluginMessage("OnChunkQueued: " + chunkNameStr);
	if (chunkNameStr == "RM7_Chunk_01")
	{
		API::LogPluginMessage("M7 QUEUED");
		auto shadow1 = SaveData::FindMissionById(Mission::QUINKAN_ARMADA);
		auto extreme1 = SaveData::FindMissionById(Mission::EGG_HUNT);
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::EGG_HUNT] = extreme1->missionState;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::QUINKAN_ARMADA] = shadow1->missionState;
		if (selectedBunyip == Bunyip::SHADOW) {
			API::LogPluginMessage("SHADOW BUNYIP");
			extreme1->missionState = MissionState::UNAVAILABLE;
			shadow1->missionState = MissionState::ACTIVE;
		}
		if (selectedBunyip == Bunyip::EXTREME) {
			API::LogPluginMessage("EXTREME BUNYIP");
			shadow1->missionState = MissionState::UNAVAILABLE;
			extreme1->missionState = MissionState::ACTIVE;
		}
	}
	else if (chunkNameStr == "RM17_chunk_01")
	{
		API::LogPluginMessage("M17 QUEUED");
		auto shadow2 = SaveData::FindMissionById(Mission::POWER_STRUGGLE);
		auto extreme2 = SaveData::FindMissionById(Mission::REDBACK_RUNDOWN);
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::REDBACK_RUNDOWN] = extreme2->missionState;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::POWER_STRUGGLE] = shadow2->missionState;
		if (selectedBunyip == Bunyip::SHADOW) {
			API::LogPluginMessage("SHADOW BUNYIP");
			extreme2->missionState = MissionState::UNAVAILABLE;
			shadow2->missionState = MissionState::ACTIVE;
		}
		if (selectedBunyip == Bunyip::EXTREME) {
			API::LogPluginMessage("EXTREME BUNYIP");
			shadow2->missionState = MissionState::UNAVAILABLE;
			extreme2->missionState = MissionState::ACTIVE;
		}
	}
	else if (chunkNameStr == "RM29_chunk_01")
	{
		auto shadow3 = SaveData::FindMissionById(Mission::RANGER_ENDANGER);
		auto extreme3 = SaveData::FindMissionById(Mission::MELTDOWN);
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::MELTDOWN] = extreme3->missionState;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::RANGER_ENDANGER] = shadow3->missionState;
		if (selectedBunyip == Bunyip::SHADOW) {
			extreme3->missionState = MissionState::UNAVAILABLE;
			shadow3->missionState = MissionState::ACTIVE;
		}
		if (selectedBunyip == Bunyip::EXTREME) {
			shadow3->missionState = MissionState::UNAVAILABLE;
			extreme3->missionState = MissionState::ACTIVE;
		}
	}
	else {
		return;
	}

	std::string filePath = "./Saves/" + ArchipelagoHandler::GetSaveIdentifier();
	SaveDataHandler::write_json_file(filePath + ".json");

	*(int*)(Core::moduleBase + 0x490400) = 0;
	void (*save)() = reinterpret_cast<void(*)()>(Core::moduleBase + 0x2527A0);
	save();
}

void GameHandler::OnChunkQueuedWithoutQueuer(uintptr_t chunkPtr) {
	auto strPtr = *(uintptr_t*)(chunkPtr);
	auto chunkName = reinterpret_cast<const char*>(strPtr);
	std::string chunkNameStr(chunkName);
	API::LogPluginMessage("OnChunkQueuedWithoutQueuer: " + chunkNameStr);
	if (chunkNameStr == "RT1_Chunk_01" || chunkNameStr == "RT2_Chunk_01")
		RestoreBunyipMissionStatuses();
	else
		return;

	//std::string filePath = "./Saves/" + ArchipelagoHandler::GetSaveIdentifier();
	//SaveDataHandler::write_json_file(filePath + ".json");

	//*(int*)(Core::moduleBase + 0x490400) = 0;
	//void (*save)() = reinterpret_cast<void(*)()>(Core::moduleBase + 0x2527A0);
	//save();
}


void GameHandler::OnChunkLoaded() {
	if (auto rescueJuliusDoor = MKObject::GetMKObject(90284)) {
		auto shouldOpen = SaveData::FindMissionById(Mission::KARLOS_MISSION)->missionState != (int)MissionState::UNAVAILABLE;
		auto isOpen = *(int*)(rescueJuliusDoor + 0x168) < 3;
		if (shouldOpen != isOpen)
			*(int*)(rescueJuliusDoor + 0x16C) = shouldOpen ? 2 : 4;
	}
	if (auto cinderCanyonDoor = MKObject::GetMKObject(90345)) {
		auto shouldOpen = SaveData::FindMissionById(Mission::BROWN_KIWI_DOWN)->missionState != (int)MissionState::UNAVAILABLE;
		auto isOpen = *(int*)(cinderCanyonDoor + 0x168) < 3;
		if (shouldOpen != isOpen)
			*(int*)(cinderCanyonDoor + 0x16C) = shouldOpen ? 2 : 4;
	}
	if (auto cassopolisDoor = MKObject::GetMKObject(60421)) {
		auto shouldOpen = SaveData::FindMissionById(Mission::CRAB_MISSION)->missionState != (int)MissionState::UNAVAILABLE;
		auto isOpen = *(int*)(cassopolisDoor + 0x168) < 3;
		if (shouldOpen != isOpen)
			*(int*)(cassopolisDoor + 0x16C) = shouldOpen ? 2 : 4;
	}
	API::LogPluginMessage("OnChunkLoaded");
}

bool GameHandler::IsSaveSelected()
{
	return *(int*)(Core::moduleBase + 0x4903FC) != -1;
}

void GameHandler::OnSelectBunyip(UIElementStruct* buttonsPtr)
{
	if (buttonsPtr->firstChildUiElement == nullptr || buttonsPtr->firstChildUiElement->TypeName == NULL)
		return;
	auto buttonChildName = std::string(buttonsPtr->firstChildUiElement->TypeName);
	API::LogPluginMessage("Button selected: " + buttonChildName);
	if (buttonChildName != "ButtonUsePrimary")
		return;
	selectedBunyip = *reinterpret_cast<Bunyip*>(reinterpret_cast<char*>(buttonsPtr) + 0x504);
	API::LogPluginMessage("Bunyip selected: " + std::to_string((int)selectedBunyip));
}

int __stdcall GameHandler::CanActivateMission(uintptr_t* missionPtr)
{
	auto const* mission = (MissionStruct*)(reinterpret_cast<std::byte*>(missionPtr));
	auto missionId = mission->missionId & 0xffff;
	if ((missionId > Mission::QUINKING && missionId < Mission::GO_FIND_BOSS_CASS))
		return 1;
	if (gameActiveMissions.end() != std::find(gameActiveMissions.begin(), gameActiveMissions.end(), missionId)) {
		return 1;
	}
	if (autoActiveMissions.end() != std::find(autoActiveMissions.begin(), autoActiveMissions.end(), missionId)) {
		return 1;
	}
	if (autoAvailableMissions.end() != std::find(autoAvailableMissions.begin(), autoAvailableMissions.end(), missionId)) {
		return 1;
	}
	auto& savedAllowed = ArchipelagoHandler::customSaveData->allowedActiveMissions;
	if (savedAllowed.end() != std::find(savedAllowed.begin(), savedAllowed.end(), missionId)) {
		return 1;
	}
	return 0;
}

void GameHandler::OnGameLoaded()
{
	API::LogPluginMessage("GameLoaded");
	SaveDataHandler::RunLoadSetup(ArchipelagoHandler::slotdata);
	for (auto mission : GameHandler::autoAvailableMissions) {
		auto missionState = SaveData::FindMissionById(mission)->missionState;
		if (missionState == MissionState::UNAVAILABLE) {
			SaveData::FindMissionById(mission)->missionState = MissionState::AVAILABLE;
		}
	}
	for (auto mission : GameHandler::autoActiveMissions) {
		auto missionState = SaveData::FindMissionById(mission)->missionState;
		if (missionState == MissionState::UNAVAILABLE) {
			SaveData::FindMissionById(mission)->missionState = MissionState::ACTIVE;
		}
	}
}

void GameHandler::OnMenuLoaded()
{
	API::LogPluginMessage("MenuLoaded");
	LoginHandler::DisableLoadButtons();
}

void __fastcall GameHandler::OnDeath(uintptr_t* tyPtr, int edx, int state, int source) {
	if (source != 9000 && state == 0xe) {
		if (!ArchipelagoHandler::slotdata->deathlink)
			return stateTransitionFunc(tyPtr, state, source);
		API::LogPluginMessage(std::to_string(source));
		ArchipelagoHandler::SendDeath();
	}
	stateTransitionFunc(tyPtr, state, source);
}
