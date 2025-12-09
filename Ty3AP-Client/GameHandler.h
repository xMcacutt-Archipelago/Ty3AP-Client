#pragma once
#include "ArchipelagoHandler.h"
#include "CheckHandler.h"
#include "APSaveData.h"
#include <windows.h>
#include "Hooks.h"

class GameHandler
{
public:
	static void Initialize();
	static void SetToNoOperation(void* address, size_t size);
	static void SetToJmp(void* address);
	static void OnGameLoaded();
	static void OnMenuLoaded();
	static void OnChunkLoaded();
private:
};