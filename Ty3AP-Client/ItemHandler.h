#pragma once
#include "GameHandler.h"
#include "SaveDataHandler.h"
#include "SaveData.h"
#include "Mission.h"
#include "Item.h"

enum Ty3Item {
    Sly = 0x981,
    Duke = 0x982,
    Karlos = 0x983,
    Crabmersible = 0x984,
    SouthernRiversGate = 0x985,
    CinderCanyon = 0x946,
    DeadDingoMarsh = 0x947,
    GoobooGully = 0x948,
    KakaBoomIsland = 0x949,
    MountBoomBasin = 0x94A,
    ShadowBeam = 0x51,
    GravGrenade = 0x52,
    SatelliteStrike = 0x53,
    ThermoCannon = 0x54,
    NucleonShield = 0x55,
    Orbidrills = 0x56,
    MissingPersonsMap = 0x57,
    ShinyThingMap = 0x58,
    SekritMap = 0x59,
    PricelessArtMap = 0x5a,
    ForbiddenFruitMap = 0x5b,
    BunyipGauntlet = 0x5c,
    ShadowStone1 = 0x5d,
    ShadowStone2 = 0x5e,
    ShadowStone3 = 0x5f,
    MonoChassis = 0x01,
    DuoChassis = 0x02,
    LashChassis = 0x03,
    SmashChassis = 0x04,
    MegaChassis = 0x05,
    RingChassis = 0x06,
    ShadowChassis = 0x07,
    DoomChassis = 0x08,
    FireStone = 4601,
    WaterStone = 4602,
    AirStone = 4603,
    EarthStone = 4604,
    ChronoStone = 4605,
    WarpStone = 4606,
    UltraStone = 4607,
    MegaStone = 4608,
    MultiStone = 4609,
    ZoomStone = 4610,
    MagnetStone = 4611,
    KromiumOrb = 0x20,
    GoobooBerry = 0x21,
    Bilby = 0x22,
    Opals50 = 0x25,
    Opals100 = 0x26,
    Opals250 = 0x27,
    Opals500 = 0x28,
    Opals1k = 0x29,
    FullHeal = 0x2A,
};

class ItemHandler
{
public:
    static void HandleItem(APClient::NetworkItem item);
    static void HandleStoredItems();
    static std::queue<APClient::NetworkItem> storedItems;
private:
    static void AddOpals(int amount) {
        using Addopals = uint32_t(__thiscall*)(uintptr_t thisPtr, uintptr_t objPtr);
        Addopals addopals = reinterpret_cast<Addopals>(Core::moduleBase + 0x10FE90);
        uintptr_t thisPtr = (uintptr_t)API::Get()->param()->TyHModule + 0x4C2EF8;
        addopals(thisPtr, amount);
        return;
    }
};

