#pragma once
#include "GameHandler.h"
#include "SaveDataHandler.h"
#include "SaveData.h"

class ItemHandler
{
public:
    static void HandleItem(APClient::NetworkItem item);
    static void HandleStoredItems();
    static std::queue<APClient::NetworkItem> storedItems;
private:
    static void AddOpals(int amount) {
        using Addopals = uint32_t(__thiscall*)(uintptr_t thisPtr, uintptr_t objPtr);
        Addopals addopals = reinterpret_cast<Addopals>((uintptr_t)API::Get()->param()->TyHModule + 0x00119fb0);
        uintptr_t thisPtr = (uintptr_t)API::Get()->param()->TyHModule + 0x4EB580;

        addopals(thisPtr, amount);
        int* uiPtr = (int*)(Core::moduleBase + 0x4EB588);
        *uiPtr += amount;

        int* visualCount = (int*)(*(uintptr_t*)(Core::moduleBase + 0x4EEB9C) + 0x510);
        *visualCount += amount;
        return;
    }
};