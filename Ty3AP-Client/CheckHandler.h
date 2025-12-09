#pragma once
#include "gui.h"
#include "InfoWindow.h"
#include "MinHook.h"
#include "APSaveData.h"

class CheckHandler
{
public:
	static void OnCollectCollectible(int id, int type);
    static void OnCompleteMission(void* mission, int status);
    static void OnBuyItem(void* item);

    struct Collectible {
        int level = -1;
        std::string name;
    };

    static inline const std::array<Collectible, 6> collectibles{
        Collectible{0, "Berry"},
        Collectible{1, "Bilby"},
        Collectible{2, "Frame"},
        Collectible{3, "Kromium Orb"},
        Collectible{4, "Steve"},
        Collectible{6, "Bunyip Stones"},
    };
};