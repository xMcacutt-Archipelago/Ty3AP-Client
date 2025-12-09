#include "pch.h"
#include "GameHandler.h"
#include "gui.h"

bool disabledButtons = false;

void TickBeforeGame(float deltaSeconds) {
    GUI::DrawUI();
    if (SaveDataHandler::g_SaveCallback.active) {
        if (--SaveDataHandler::g_SaveCallback.framesRemaining <= 0) {
            if (SaveDataHandler::g_SaveCallback.callback != nullptr) {
                SaveDataHandler::g_SaveCallback.callback();
                SaveDataHandler::g_SaveCallback.callback = nullptr;
            }
            else {
                *(DWORD*)(SaveDataHandler::g_SaveCallback.esi + 0x238) = 0;
            }
            SaveDataHandler::g_SaveCallback.active = false;
        }
    }
}

void OnTyInit() {
    GameHandler::Initialize();
    std::thread t(ArchipelagoHandler::Poll);
    t.detach();
}

void OnTyBeginShutdown() {
    ArchipelagoHandler::DisconnectAP();
}

extern "C" __declspec(dllexport) bool TygerFrameworkPluginInitialize(TygerFrameworkPluginInitializeParam* param) {
    if (!API::Initialize(param))
        return false;

    if (!Core::initialize((HMODULE)API::Get()->param()->TyHModule))
        return false;

    API::AddTickBeforeGame(TickBeforeGame);
    API::AddPluginImGuiWantCaptureMouse((ImGuiWantCaptureMouseFunc)GUI::ImGuiWantCaptureMouse);
    API::AddOnTyInitialized(OnTyInit);
    API::AddPluginWndProc((WndProcFunc)GUI::WndProc);
    return true;
}

extern "C" __declspec(dllexport) void TygerFrameworkPluginRequiredVersion(TygerFrameworkPluginVersion* version) {
    version->Major = 1;
    version->Minor = 1;
    version->Patch = 3;
    version->CompatibleGames = { 3 };
}