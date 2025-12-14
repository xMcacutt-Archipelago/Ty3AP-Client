#pragma once
#include "gui.h"
#include "MinHook.h"
#include "APSaveData.h"
#include "cstdint"

class CheckHandler
{
public:
	static void OnCollectCollectible(int id, int type);
    static void OnCompleteMission(void* mission, int status);
    static void OnBuyItem(void* item);

    static inline const std::string collectibles[7] = {
        "Berry",
        "Bilby",
        "Frame",
        "Kromium Orb",
        "Steve",
        "Frill", // unused
        "Bunyip Stone",
    };
};