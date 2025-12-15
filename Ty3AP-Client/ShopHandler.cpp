#include "pch.h"
#include "ShopHandler.h"

int __cdecl ShopHandler::OnGetString(int param_1) {
	auto state = *(int*)(Core::moduleBase + 0x4C2D80);
	if (state == 2) {
        const char* itemname = ShopHandler::GetShopItemName(param_1, true);
		if (itemname)
			return (int)itemname;
	}
	return getStringFunc(param_1);
}

std::optional<int> GetItemIdFromStringId(int stringId) {
	auto data = SaveData::GetData();
	for (auto itemIndex = 0; itemIndex < data->itemCount; itemIndex++) {
		auto item = data->items[itemIndex];
		if (item->titleId == stringId || item->descId == stringId)
			return item->itemId & 0xFFFF;
	}
	return std::nullopt;
}

static std::map<int, std::string> strIDtoTitleText = {};
static std::mutex strIDtoTitleTextMutex;

static std::map<int, std::string> strIDtoDescText = {};
static std::mutex strIDtoDescTextMutex;

static std::map<int, std::string> strIDtoImgText = {};
static std::mutex strIDtoImgTextMutex;

static std::map<int, int> IDtoCost = {};
static std::mutex IDtoCostMutex;

std::list<int64_t> scouteditems;
const char* ShopHandler::GetShopItemName(int strId, bool hint) {
	auto itemIdOpt = GetItemIdFromStringId(strId);
	if (itemIdOpt.has_value()) {
		int64_t itemId = static_cast<int64_t>(itemIdOpt.value());
		if (std::find(validShopItems.begin(), validShopItems.end(), itemId) == validShopItems.end()) {
			return nullptr;
		}
		if (std::find(scouteditems.begin(), scouteditems.end(), itemId) == scouteditems.end()) {
			std::list<int64_t> newList;
			newList.push_back(0x6900 + itemId);
			ArchipelagoHandler::ScoutLocations(newList, hint);
			if (hint) 
				scouteditems.push_back(itemId);
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

void ShopHandler::SetShopItems() {
	auto rangShop = SaveData::FindShopById(Shop::RANG_SHOP);
	int indexCurrency1 = 0;
	for (auto itemIndex = 0; itemIndex < rangShop->itemCount; itemIndex++) {
		auto item = rangShop->items[itemIndex];
		switch (item->currencyType) {
		case 0:
		{
			std::lock_guard<std::mutex> lock(IDtoCostMutex);
			auto it = IDtoCost.find(item->itemId);
			if (it != IDtoCost.end()) {
				item->baseCost = it->second;
			}
			break;
		}
		case 1:
			item->baseCost = (indexCurrency1 + 1) * 3;
			indexCurrency1++;
			break;
		}
		ShopHandler::GetShopItemName(item->titleId, false);
	}

	auto cassopolisShop = SaveData::FindShopById(Shop::CASSOPOLIS);
	for (auto itemIndex = 0; itemIndex < cassopolisShop->itemCount; itemIndex++) {
		auto item = cassopolisShop->items[itemIndex];
		ShopHandler::GetShopItemName(item->titleId, false);
		if (item->currencyType == 0)
		{
			{
				std::lock_guard<std::mutex> lock(IDtoCostMutex);
				auto it = IDtoCost.find(item->itemId);
				if (it != IDtoCost.end()) {
					item->baseCost = it->second;
				}
				break;
			}
		}
	}

	auto mobileHQ = SaveData::FindShopById(Shop::MOBILE_HQ);
	int indexCurrency2 = 0, indexCurrency3 = 0;
	for (auto itemIndex = 0; itemIndex < mobileHQ->itemCount; itemIndex++) {
		auto item = mobileHQ->items[itemIndex];
		switch (item->currencyType) {
		case 0:
		{
			std::lock_guard<std::mutex> lock(IDtoCostMutex);
			auto it = IDtoCost.find(item->itemId);
			if (it != IDtoCost.end()) {
				item->baseCost = it->second;
			}
			break;
		}
		case 2:
			item->baseCost = (indexCurrency2 + 1) * 2;
			indexCurrency2++;
			break;
		case 3:
			item->baseCost = (indexCurrency3 + 1) * 7;
			indexCurrency3++;
			break;
		}
		ShopHandler::GetShopItemName(item->titleId, false);
	}

	auto secretShop = SaveData::FindShopById(Shop::SECRET_SHOP);
	for (auto itemIndex = 0; itemIndex < secretShop->itemCount; itemIndex++) {
		auto item = secretShop->items[itemIndex];
		ShopHandler::GetShopItemName(item->titleId, false);
		if (item->currencyType == 0)
		{
			{
				std::lock_guard<std::mutex> lock(IDtoCostMutex);
				auto it = IDtoCost.find(item->itemId);
				if (it != IDtoCost.end()) {
					item->baseCost = it->second;
				}
				break;
			}
		}
	}
}

void ShopHandler::FillShopItemNames(const std::list<APClient::NetworkItem>& items)
{
	for (const APClient::NetworkItem& netItem : items) {
		auto itemId = netItem.location & 0xFF;
		ItemStruct* shopItem = SaveData::FindItemById(itemId);

		if (!shopItem) {
			API::LogPluginMessage("Invalid id: " + std::to_string(itemId));
			continue;
		}

		{
			std::lock_guard<std::mutex> lock(strIDtoTitleTextMutex);
			strIDtoTitleText[shopItem->titleId] = ArchipelagoHandler::GetItemName(netItem.item, netItem.player);
		}

		{
			std::lock_guard<std::mutex> lock(strIDtoDescTextMutex);
			strIDtoDescText[shopItem->descId] = ArchipelagoHandler::GetItemDesc(netItem.player);
		}

		{
			std::lock_guard<std::mutex> lock(IDtoCostMutex);
			IDtoCost[shopItem->itemId] = ShopHandler::GetCost(netItem.flags);
		}

		auto itemName = ArchipelagoHandler::GetItemName(netItem.item, netItem.player);
		strcpy_s(
			reinterpret_cast<char*>(shopItem->shopIconNamePtr),
			0x20,
			ShopHandler::GetImageName(itemName, netItem.flags)
		);
		if (shopItem->currencyType == 0)
			shopItem->baseCost = ShopHandler::GetCost(netItem.flags);
	}
}

void ShopHandler::CollectItem(int shopId, int itemId)
{
	auto item = SaveData::FindItemById(itemId);
	if (item) {
		API::LogPluginMessage("item has value: " + std::to_string(itemId));
		item->maxNumPurchased = 0;
	}
	else {
		API::LogPluginMessage("No Item with id " + std::to_string(itemId));
	}
}