#pragma once
#include "ArchipelagoHandler.h"
#include "Shop.h"
#include "Item.h"

class ShopHandler
{
public:
	static void SetShopItems();
	static const char* GetShopItemName(int strId, bool hint);
	static void CollectItem(int shopId, int itemId);
	static void FillShopItemNames(const std::list<APClient::NetworkItem>& items);
    typedef int(__cdecl* GetStringFunc)(int param_1);
    static inline GetStringFunc getStringFunc = nullptr;
    static int __cdecl OnGetString(int param_1);
    static inline std::list<int> validShopItems = {
        Item::FIRE_STONE,
        Item::WATER_STONE,
        Item::AIR_STONE,
        Item::EARTH_STONE,
        Item::ULTRA_STONE,
        Item::MEGA_STONE,
        Item::WARP_STONE,
        Item::MULTI_STONE,
        Item::ZOOM_STONE,
        Item::CHRONO_STONE,
        Item::MAGNET_STONE,
        Item::SHADOW_STONE,
        Item::MEGA_CHASSIS,
        Item::SMASH_CHASSIS,
        Item::RING_CHASSIS,
        Item::DUO_CHASSIS,
        Item::LASH_CHASSIS,
        Item::SHADOW_CHASSIS,
        Item::DOOM_CHASSIS,
        Item::MISSING_PERSONS_MAP,
        Item::SHINY_THING_MAP,
        Item::SEKRIT_MAP,
        Item::PRICELESS_ART_MAP,
        Item::FORBIDDEN_FRUIT_MAP,
        Item::GRAV_GRENADE,
        Item::NUCLEON_SHIELD,
        Item::SHADOW_BEAM,
        Item::SATELLITE_STRIKE,
        Item::THERMO_CANNON,
        Item::ORBIDRILLS,
        Item::ORIGINAL_TY,
        Item::SLY,
        Item::TEAM_KROME,
        Item::COMMANDO,
        Item::ZOMBIE,
        Item::QUINKAN,
        Item::RIDGE,
        Item::GHOST_TIGER,
        Item::MIDNIGHT,
        Item::CRAB_TANK,
        Item::WHITE_KNIGHT,
        Item::MEAN_GREEN,
        Item::CAMMO,
        Item::BUSH_RESCUE,
        Item::NIGHTMARE,
        Item::SKY_FORCE,
        Item::SPITFIRE,
    };
private:
    static inline std::unordered_map<std::string, const char*> itemNameToImg = {
        {"Power Star", "AP_PowerStar"},
        {"Pagie", "AP_Pagie"},
        {"Egg", "AP_Egg"},
        {"Emblem", "AP_Emblem"},
        {"Gold Bolt", "AP_GoldBolt"},
        {"Golden Banana", "AP_GoldenBanana"},
        {"Golden Spatula", "AP_GoldenSpatula"},
        {"Jiggy", "AP_Jiggy"},
        {"Orb", "AP_Orb"},
        {"Platinum Bolt", "AP_PlatinumBolt"},
        {"Platinum Cog", "AP_PlatinumCog"},
        {"Precursor Orb", "AP_PrecursorOrb"},
        {"Shine Sprite", "AP_ShineSprite"},
        {"Time Piece", "AP_TimePiece"},
        {"Titanium Bolt", "AP_TitaniumBolt"},
        {"Strawberry", "AP_Strawberry"},
        {"Golden Cog", "AP_GoldenCog"},
        {"Picture Frame", "fe_999_totalpicture"},

        {"Fire Thunder Egg", "AP_ThunderEgg"},
        {"Ice Thunder Egg", "AP_ThunderEgg"},
        {"Air Thunder Egg", "AP_ThunderEgg"},

        {"50 Opals", "fe_000_opal"},
        {"100 Opals", "fe_000_opal"},
        {"200 Opals", "fe_000_opal"},
        {"250 Opals", "fe_000_opal"},
        {"500 Opals", "fe_000_opal"},
        {"1000 Opals", "fe_000_opal"},
        {"5000 Opals", "fe_000_opal"},
    
        // Ty 3 stuff:
        {"Air Stone", "fe_700_air"},
        {"Chrono Stone", "fe_700_chrono"},
        {"Earth Stone", "fe_700_earth"},
        {"Fire Stone", "fe_700_fire"},
        {"Magnet Stone", "fe_700_magento"},
        {"Mega Stone", "fe_700_mega"},
        {"Multi Stone", "fe_700_multi"},
        {"Ultra Stone", "fe_700_ultra"},
        {"Warp Stone", "fe_700_warp"},
        {"Water Stone", "fe_700_water"},
        {"Zoom Stone", "fe_700_zoom"},

        {"Duo Chassis", "fe_700_rang_duo"},
        {"Lash Chassis", "fe_700_rang_lash"},
        {"Smash Chassis", "fe_700_rang_Smash"},
        {"Mega Chassis", "fe_700_rang_mega"},
        {"Ring Chassis", "fe_700_rang_ring"},
        {"Doom Chassis", "fe_700_rang_doom"},

        {"Shadow Beam", "fe_700_shadowbeam"},
        {"Grav Grenade", "fe_700_grenade"},
        {"Satellite Strike", "fe_700_satstrike"},
        {"Thermo Cannon", "fe_700_flame"},
        {"Nucleon Shield", "fe_700_nucleon"},
        {"Orbidrills", "fe_700_drill"},

        {"Missing Persons Map", "fe_700_Bilbies"},
        {"Shiny Thing Map", "fe_700_Orbs"},
        {"Sekrit Map", "fe_700_Steves"},
        {"Priceless Art Map", "fe_700_Frames"},
        {"Forbidden Fruit Map", "fe_700_Berry"},

        {"Sly", "fe_999_totalbunyip"},
        {"Duke", "Fe_999_Gunyip"},
        {"Karlos", "fe_999_totalstar"},
        {"Crabmersible", "Fe_999_Crab"},
        {"Southern Rivers Gate", "fe_999_bus"},

        {"Level - Cinder Canyon",     "fe_999_totalstar"},
        {"Level - Dead Dingo Marsh",  "fe_999_totalstar"},
        {"Level - Gooboo Gully",      "fe_999_totalstar"},
        {"Level - Kaka Boom Island",  "fe_999_totalstar"},
        {"Level - Mount Boom Basin",  "fe_999_totalstar"},

        {"Kromium Orb", "fe_999_totalorb"},
        {"Gooboo Berry", "fe_999_totalberry"},
        {"Bilby", "fe_999_totalbilby"},

        {"Shadow Chassis", "fe_999_shadowring"},

        {"Bunyip Gauntlet", "fe_700_K_Melee"},
    };

    static const char* GetImageName(const std::string& itemname, int flags)
    {
        if (auto it = itemNameToImg.find(itemname); it != itemNameToImg.end())
            return it->second;
        if (flags & 1) return "ap_color";
        if (flags & 2) return "ap_white";
        if (flags & 4) return "ap_white";
        return "ap_white";
    }

    static int GetCost(int flags) 
    {
        if (flags & 1) return 1500;
        if (flags & 2) return 1000;
        return 500;
    }
};

