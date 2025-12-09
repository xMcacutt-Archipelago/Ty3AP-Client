#include "pch.h"
#include "ShopHandler.h"

uintptr_t ShopHandler::bobsCogRequirementArrays[9];
uintptr_t ShopHandler::OrbRequirementArrays[3];
static std::string apLogo = "Fe_999_rita";

static std::map<int, std::string> strIDtoTitleText = {};
static std::mutex strIDtoTitleTextMutex;

static std::map<int, std::string> strIDtoDescText = {};
static std::mutex strIDtoDescTextMutex;

static std::map<int, std::string> strIDtoImgText = {};
static std::mutex strIDtoImgTextMutex;

struct itemStrings {
	int titleId;
	int descId;
};

std::list<int64_t> scouteditems;
static const char* unknown = "Unknown AP Item";

static const std::map <int, itemStrings> shop1Ids =
{ { 1, {550,551} }, { 2, {552,553} }, { 59, {666,667} },{77, {702,703} },{78, {704,705} },{79, {1117,1118} },{80, {1119,1120} },{81, {1121,1122} },
	{82, {1123,1124} },{83, {1125,1126} },{84, {1127,1128} },{85, {1129,1130} },{86, {1131,1132} }, { 87, {1133,1134} }, { 88, {1135,1136} } };
static const std::map <int, itemStrings> shop2Ids =
{ {8, {564,212} },{9, {566,214} },{18, {196,216} },{11, {570,218} },{12, {572,220} },{13, {574,222} },{14, {576,224} },{26, {1190,1191} } };
static const std::map <int, itemStrings> shop3Ids =
{ {15, {191,211} },{16, {193,213} },{17, {195,215} },{10, {568,217} },{19, {199,219} },{20, {201,221} },{21, {203,223} },{22, {205,225} },
	{23, {206,226} },{24, {207,227} },{25, {1188,1189} } };
static const std::map <int, itemStrings> shop4Ids = { {5, {558,559} },{6, {560,561} },{7, {562,563} } };

bool ShopHandler::OnItemAvailable(void* itemPtr) {
	uint8_t* base = static_cast<uint8_t*>(itemPtr);
	short id = *reinterpret_cast<short*>(base + 0x4);
	//true means purchaseable
	return !ArchipelagoHandler::customSaveData->hasBoughtItem(id);
}

void ShopHandler::SetShopItems(SlotData* slotdata) {
	int index = 0;
	SaveData::GetShopItemList(1).forEach([&index, slotdata](ItemStruct& item) {
		if (item.currencyType == 0) {
			item.price = slotdata->traderBobPrices[index];
			if (item.itemId == 78) {
				API::LogPluginMessage("Changing locked for platinum paw " + std::to_string(item.itemId));
				item.locked = false;
				item.requirementsArrayLength = 0;
			}
			index++;
			ShopHandler::GetShopItemName(item.titleId, false);
		}
		});

	index = 0;
	uintptr_t lastitemptr;
	SaveData::GetShopItemList(1).forEach([&index, slotdata, &lastitemptr](ItemStruct& item) {
		if (item.currencyType == 2) {
			lastitemptr = (uintptr_t)&item;
			item.price = slotdata->cogPrices[index];
			if (item.itemId > 79) {
				API::LogPluginMessage("Changing locked for cog stuff " + std::to_string(item.itemId));
				ShopHandler::bobsCogRequirementArrays[item.itemId - 80] = lastitemptr;
				item.setItemRequirements((uintptr_t)&ShopHandler::bobsCogRequirementArrays[item.itemId - 80], 1);
				item.locked = !ArchipelagoHandler::customSaveData->hasBoughtItem(item.itemId - 1);
			}
			ShopHandler::GetShopItemName(item.titleId, false);
			index++;
		}
	});

	index = 0;
	SaveData::GetShopItemList(2).forEach([&index, slotdata](ItemStruct& item) {
		if (item.currencyType == 0) {
			item.price = slotdata->rangPrices[index];
			item.locked = false;
			index++;
			ShopHandler::GetShopItemName(item.titleId, false);
		}
	});

	index = 0;
	SaveData::GetShopItemList(3).forEach([&index, slotdata](ItemStruct& item) {
		if (item.currencyType == 0) {
			item.price = slotdata->slyPrices[index];

			item.locked = false;
			index++;
			ShopHandler::GetShopItemName(item.titleId, false);
		}
	});

	index = 0;
	SaveData::GetShopItemList(4).forEach([&index, slotdata, &lastitemptr](ItemStruct& item) {
		if (item.currencyType == 1) {
			item.price = slotdata->orbPrices[index];
			lastitemptr = (uintptr_t)&item;
			if (item.itemId > 5) {
				ShopHandler::OrbRequirementArrays[item.itemId - 6] = lastitemptr;
				item.setItemRequirements((uintptr_t)&ShopHandler::OrbRequirementArrays[item.itemId - 6], 1);
				item.locked = !ArchipelagoHandler::customSaveData->hasBoughtItem(item.itemId - 1);
			}
			ShopHandler::GetShopItemName(item.titleId, false);
			index++;
		}
	});
}

const char* ShopHandler::GetShopItemName(int strId, bool hint) {
	auto itemIdOpt = getItemIdFromString(strId);
	if (itemIdOpt.has_value()) {
		int64_t itemId = static_cast<int64_t>(itemIdOpt.value());
		if (std::find(scouteditems.begin(), scouteditems.end(), itemId) == scouteditems.end()) {
			std::list<int64_t> newList;
			newList.push_back(itemId);
			ArchipelagoHandler::ScoutLocations(newList, hint);

			if (hint) {
				scouteditems.push_back(itemId);
			}
		}
	}
	{
		std::lock_guard<std::mutex> lock(strIDtoTitleTextMutex);
		auto it = strIDtoTitleText.find(strId);
		if (it != strIDtoTitleText.end()) {
			return it->second.c_str();
		}
	}
	{
		std::lock_guard<std::mutex> lock(strIDtoDescTextMutex);
		auto it = strIDtoDescText.find(strId);
		if (it != strIDtoDescText.end()) {
			return it->second.c_str();
		}
	}

	return nullptr;
}

const char* ShopHandler::getImagePtr(const std::string& itemname, int flags)
{
	API::LogPluginMessage("Lookup");
	// lookup by item name
	if (auto it = itemNameToImg.find(itemname); it != itemNameToImg.end())
		return it->second;
	API::LogPluginMessage("Check flags");
	// check flags (priority order)
	if (flags & 1) return "ap_color"; //progressive
	if (flags & 2) return "ap_color"; //useful ap_white
	if (flags & 4) return "ap_color"; //junk ap_black

	// default
	API::LogPluginMessage("Returning default");
	return "ap_color";
}

std::optional<int> getItemIdFromString(int stringId) {
	const std::map<int, itemStrings>* shops[] = { &shop1Ids, &shop2Ids, &shop3Ids, &shop4Ids };

	for (auto shop : shops) {
		for (const auto& pair : *shop) {
			if (pair.second.titleId == stringId || pair.second.descId == stringId) {
				return pair.first; // return the item ID
			}
		}
	}

	return std::nullopt; // not found
}

void ShopHandler::FillShopItemNames(const std::list<APClient::NetworkItem>& items) {
	for (const APClient::NetworkItem& item : items) {
		itemStrings* strs = nullptr;

		auto findStrings = [&](const std::map<int, itemStrings>& shopMap) -> itemStrings* {
			auto it = shopMap.find(item.location);
			return (it != shopMap.end()) ? const_cast<itemStrings*>(&it->second) : nullptr;
			};

		if (!(strs = findStrings(shop1Ids)) &&
			!(strs = findStrings(shop2Ids)) &&
			!(strs = findStrings(shop3Ids)) &&
			!(strs = findStrings(shop4Ids))) {
			continue; // Skip if not a known AP shop item
		}

		{
			std::lock_guard<std::mutex> lock(strIDtoTitleTextMutex);
			strIDtoTitleText[strs->titleId] = ArchipelagoHandler::GetItemName(item.item, item.player);
		}
		{
			std::lock_guard<std::mutex> lock(strIDtoDescTextMutex);
			strIDtoDescText[strs->descId] = ArchipelagoHandler::GetItemDesc(item.player);
		}
		API::LogPluginMessage("Find Item");
		ItemStruct* shopItem = SaveData::findItemByID((int)item.location);
		API::LogPluginMessage("Check item");
		if (shopItem) {
			API::LogPluginMessage("Set Item");
			shopItem->ShopIconNameString = const_cast<char*>(ShopHandler::getImagePtr(ArchipelagoHandler::GetItemName(item.item, item.player), item.flags));
			API::LogPluginMessage("Set Item Image");
		}
	}
}

void ShopHandler::CollectItem(int shopId, int itemId)
{
	LinkedList<ItemStruct> items = SaveData::GetShopItemList(shopId);
	auto item = SaveData::findItemByID(items, itemId);
	if (item) {
		API::LogPluginMessage("item has value: " + std::to_string(itemId));
		item->purchased = true;
	}
	else {
		API::LogPluginMessage("No Item with id " + std::to_string(itemId));
	}
}