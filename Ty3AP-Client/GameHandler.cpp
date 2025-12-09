#include "pch.h"
#include "GameHandler.h"
using nlohmann::json;

typedef void(__thiscall* StateTransitionFunc)(void* thisPtr, int firstArg, int secondArg);
StateTransitionFunc StateTransitionOrigin = nullptr;

void GameHandler::Initialize()
{
	MH_Uninitialize();
	MH_Initialize();
	Hooks::SetupHooks();
	MH_EnableHook(MH_ALL_HOOKS);
}

void GameHandler::SetToNoOperation(void* address, size_t size) {
	DWORD oldProtect;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(address, 0x90, size);
	VirtualProtect(address, size, oldProtect, &oldProtect);
	FlushInstructionCache(GetCurrentProcess(), address, size);
}

void GameHandler::SetToJmp(void* address) {
	DWORD oldProtect;
	VirtualProtect(address, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(address, 0xEB, 1);
	VirtualProtect(address, 1, oldProtect, &oldProtect);
	FlushInstructionCache(GetCurrentProcess(), address, 1);
}

void GameHandler::OnChunkLoaded() {
	API::LogPluginMessage("OnChunkLoaded");
}

void GameHandler::OnGameLoaded()
{
	API::LogPluginMessage("GameLoaded");
}

void GameHandler::OnMenuLoaded()
{
	API::LogPluginMessage("MenuLoaded");
}
