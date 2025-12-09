#include "pch.h"
#include "ItemHandler.h"

std::queue<APClient::NetworkItem> ItemHandler::storedItems;

void ItemHandler::HandleItem(APClient::NetworkItem item)
{
	if (!IsInGame()) {
		storedItems.push(item);
		return;
	}

	API::LogPluginMessage("lastindex: " + std::to_string(ArchipelagoHandler::customSaveData->pLastReceivedIndex) + " index: " + std::to_string(item.index));
	if (item.index <= ArchipelagoHandler::customSaveData->pLastReceivedIndex) {
		return;
	}

	ArchipelagoHandler::customSaveData->pLastReceivedIndex++;

	std::string filePath = "./Saves/" + ArchipelagoHandler::GetSaveIdentifier();

	SaveDataHandler::write_json_file(filePath + ".json");
}

void ItemHandler::HandleStoredItems()
{
	while (!storedItems.empty() && GameHandler::IsInGame()) {
		HandleItem(storedItems.front());
		storedItems.pop();
	}
}