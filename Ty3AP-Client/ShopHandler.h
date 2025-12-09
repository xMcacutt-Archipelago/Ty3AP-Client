#pragma once
#include "ArchipelagoHandler.h"

class ShopHandler
{
public:
	static bool OnItemAvailable(void* itemPtr);
	static void SetShopItems(SlotData* slotdata);
	static const char* GetShopItemName(int strId, bool hint);
	static void CollectItem(int shopId, int itemId);
	static void FillShopItemNames(const std::list<APClient::NetworkItem>& items);
private:
    static const char* getImagePtr(const std::string& itemname, int flags);
	static uintptr_t bobsCogRequirementArrays[9];
	static uintptr_t OrbRequirementArrays[3];
    static inline std::unordered_map<std::string, const char*> itemNameToImg = {
        {"PowerStar", "AP_PowerStar"},
        {"Pagie", "AP_Pagie"},

        {"Fire Thunder Egg", "fe_999_icon_thunegg"},
        {"Ice Thunder Egg", "fe_999_icon_thunegg"},
        {"Air Thunder Egg", "fe_999_icon_thunegg"},
        {"Picture Frame", "AP_PictureFrame"},
        {"Golden Cog", "AP_GoldenCog"},


        {"100 Opals", "fe_000_opal"},
        {"200 Opals", "fe_000_opal"},
        {"500 Opals", "fe_000_opal"},
        {"1000 Opals", "fe_000_opal"},
        {"5000 Opals", "fe_000_opal"},
        {"Multirang", "Fe_900_Fe_900_Multirang"},
        {"Flamerang", "Fe_900_Flamerang"},
        {"Frostyrang", "Fe_900_Frostyrang"},
        {"Freezerang", "Fe_900_Freezerang"},
        {"Zappyrang", "Fe_900_Zappyrang"},
        {"Thunderang", "Fe_900_Thunderang"},
        {"Lasharang", "Fe_900_Lasharang"},
        {"Warperang", "Fe_900_Warperang"},
        {"Infrarang", "Fe_900_Infrarang"},
        {"X-Rang", "Fe_900_Xrang"},
        {"Smasharang", "Fe_900_Smasharang"},
        {"Kaboomarang", "Fe_900_Kaboomarang"},
        {"Megarang", "Fe_900_Megarang"},
        {"Omegarang", "Fe_900_Omegarang"},
        {"Deadlyrang", "Fe_900_Deadlyrang"},
        {"Doomerang", "Fe_900_Doomerang"},
        {"Craftyrang", "Fe_900_Craftyrang"},

        {"Progressive Boomerang", "Fe_900_Multirang"},
        {"Progressive Flamerang", "Fe_900_Flamerang"},
        {"Progressive Frostyrang", "Fe_900_Frostyrang"},
        {"Progressive Zappyrang", "Fe_900_Zappyrang"},
        {"Progressive Lasharang", "Fe_900_Lasharang"},
        {"Progressive Infrarang", "Fe_900_Infrarang"},
        {"Progressive Smasharang", "Fe_900_Smasharang"},

        {"Patchy Barriers", "fe_999_tyre"},
        {"Buster Barriers", "fe_999_tyre"},
        {"Fluffy Barriers", "fe_999_tyre"},

        {"Lifter Bunyip Key", "fe_999_lifterbunyip"},
        {"Thermo Bunyip Key", "fe_999_thermobunyip"},
        {"Sub Bunyip Key", "fe_999_sub"},
        {"Progressive Health Paw", "fe_900_GoldPaw"},
    };
};

