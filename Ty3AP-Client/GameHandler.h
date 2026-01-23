#pragma once
#include "ArchipelagoHandler.h"
#include "CheckHandler.h"
#include "APSaveData.h"
#include <Windows.h>
#include "Hooks.h"
#include "Mission.h"

class GameHandler
{
public:
	static void Initialize();
	static void SetToNoOperation(uintptr_t* address, size_t size);
	static void SetToJmp(uintptr_t* address);
	static void KillTy();
	static void OnGameLoaded();
	static void OnMenuLoaded();
	static void OnChunkLoaded();
	static bool IsSaveSelected();
	static void OnWriteLevel(uintptr_t strPtr);
	static void OnChunkQueued(uintptr_t chunkPtr);
	static void OnChunkQueuedWithoutQueuer(uintptr_t chunkPtr);
	static void OnSelectBunyip(UIElementStruct* buttonsPtr);
	static void __fastcall OnDeath(uintptr_t* tyPtr, int edx, int state, int source);
	static int __stdcall CanActivateMission(uintptr_t* missionPtr);
	static inline std::list<int> gameActiveMissions = { 
		Mission::SAVE_THE_DREAMING, 
		Mission::RESCUE_THE_GENERAL,
		Mission::THE_BIG_RACE,
	};
	static inline std::list<int> autoAvailableMissions = {
		Mission::EXPERI_MENTAL_CART,
		Mission::DENNIS_DILEMMA,
		Mission::DEMOLITION_DERBY,
		Mission::RESPECT_EFFECT,
		Mission::REDBACK_STASH,
	};
	static inline std::list<int> autoActiveMissions = {
		Mission::HEINOUS_HEXAQUIN,
		Mission::GO_FIND_BOSS_CASS,
	};
	typedef void(__thiscall* StateTransitionFunc)(uintptr_t* thisPtr, int firstArg, int secondArg);
	static inline StateTransitionFunc stateTransitionFunc = nullptr;
};