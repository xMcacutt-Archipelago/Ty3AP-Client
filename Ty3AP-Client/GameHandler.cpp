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

int __stdcall GameHandler::CanActivateMission(uintptr_t* missionPtr)
{
	auto const* mission = (MissionStruct*)(reinterpret_cast<std::byte*>(missionPtr));
	auto missionId = mission->missionId & 0xffff;
	if ((missionId > Mission::QUINKING && missionId < Mission::GO_FIND_BOSS_CASS))
		return 1;
	if (gameActiveMissions.end() != std::find(gameActiveMissions.begin(), gameActiveMissions.end(), missionId)) {
//API::LogPluginMessage("CanActivateMission: " + std::to_string(missionId) + " allowed");
		return 1;
	}
	auto& savedAllowed = ArchipelagoHandler::customSaveData->allowedActiveMissions;
	if (savedAllowed.end() != std::find(savedAllowed.begin(), savedAllowed.end(), missionId)) {
//API::LogPluginMessage("CanActivateMission: " + std::to_string(missionId) + " allowed");
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
