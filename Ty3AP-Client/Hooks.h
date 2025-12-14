#pragma once
#include "MinHook.h"
#include "GameHandler.h"
#include "Core.h"

class Hooks
{
private:
	static void __stdcall CollectCollectibleHook();
	static void __stdcall CompleteMissionHook();
	static void __stdcall PurchaseItemHook();
	static void __stdcall GameLoadedHook();
	static void __stdcall MenuLoadedHook();
	static void __stdcall LoadSaveFileHook();
	static void __stdcall RecalcSaveDataSize1Hook();
	static void __stdcall RecalcSaveDataSize2Hook();
	static void __stdcall SaveFileHook();
	static void __stdcall ChunkLoadedHook();
	static void __stdcall DeathHook();
public:
	static void SetupHooks();
};

