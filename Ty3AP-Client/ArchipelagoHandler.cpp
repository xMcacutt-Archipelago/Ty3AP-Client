#include "pch.h"
#include "ArchipelagoHandler.h"
#include "LoginWindow.h"
#include <apuuid.hpp>

#define UUID_FILE "uuid"

using nlohmann::json;
bool ap_connect_sent = false;
bool is_https = false;
bool is_wss = false;
bool is_ws = false;
std::string ArchipelagoHandler::uuid = "";
bool ArchipelagoHandler::ap_connected = false;
std::string ArchipelagoHandler::seed;
std::string ArchipelagoHandler::slotName = "";
bool ArchipelagoHandler::ap_sync_queued = false;
bool ArchipelagoHandler::polling = false;
bool ArchipelagoHandler::wrongVersion = false;

SlotData* ArchipelagoHandler::slotdata = new SlotData();
APSaveData* ArchipelagoHandler::customSaveData = new APSaveData();
std::unique_ptr<APClient> ArchipelagoHandler::ap;

void ArchipelagoHandler::DisconnectAP() {
	LoggerWindow::Log("Disconnected");
	SetAPStatus("Disconnected", 1);
	polling = false;
	ap_connect_sent = false;
	ap_connected = false;
	if (GameHandler::IsSaveSelected())
		GameState::ForceMainMenu();
	else
		LoginHandler::DisableLoadButtons();
}

void ArchipelagoHandler::ConnectAP(LoginWindow* login)
{
	polling = true;
	std::string uri = login->server;
	std::string uuid = ap_get_uuid(UUID_FILE,
		uri.empty() ? APClient::DEFAULT_URI :
		is_ws ? uri.substr(5) :
		is_wss ? uri.substr(6) :
		uri);

	if (ap != nullptr) {
		ap->reset();
	}

	ap.reset(new APClient(uuid, GAME_NAME, uri.empty() ? APClient::DEFAULT_URI : uri, CERT_STORE));
	polling = true;
	API::LogPluginMessage("Connecting to AP, server " + uri + "\n", LogLevel::Info);
	SetAPStatus("Connecting", 1);

	ap->set_slot_connected_handler([login](const json& data) {
		ap_connected = true;

		if (data.find("ModVersion") != data.end() || data["ModVersion"] != COMPAT_VERSION_STRING)
			LoggerWindow::Log("Your client and apworld versions do not match. This might be fine but please check for updates.");

		LoggerWindow::Log("Connected");
		login->SetMessage("Connected");

		std::list<std::string> tags = {};
		API::LogPluginMessage(data.dump());

		if (data.find("DeathLink") != data.end()){
			slotdata->deathlink = data["DeathLink"].get<int>() == 1;
			if (slotdata->deathlink) {
				tags.push_back("DeathLink");
			}
		}

		if (data.find("StoryMissionsToGoal") != data.end()) {
			slotdata->storyMissionsToGoal = data["StoryMissionsToGoal"].get<int>();
		}

		if (data.find("BunyipMissionsToGoal") != data.end()) {
			slotdata->bunyipMissionsToGoal = data["BunyipMissionsToGoal"].get<int>();
		}

		if (data.find("GunyipMissionsToGoal") != data.end()) {
			slotdata->gunyipMissionsToGoal = data["GunyipMissionsToGoal"].get<int>();
		}

		if (data.find("RaceMissionsToGoal") != data.end()) {
			slotdata->raceMissionsToGoal = data["RaceMissionsToGoal"].get<int>();
		}

		ap->ConnectUpdate(false, 0b111, true, tags);
		ap->StatusUpdate(APClient::ClientStatus::PLAYING);
		seed = ap->get_seed();
		slotName = ap->get_slot();
		LoginHandler::EnableLoadButtons();
	});
	ap->set_slot_disconnected_handler([login]() { 
		LoggerWindow::Log("Slot disconnected");
		LoggerWindow::Log("Disconnected");
		SetAPStatus("Disconnected", 1);
		ap_connect_sent = false;
		ap_connected = false;
		if (GameHandler::IsSaveSelected())
			GameState::ForceMainMenu();
		else
			LoginHandler::DisableLoadButtons();
	});
	ap->set_slot_refused_handler([login](const std::list<std::string>& errors) {
		for (const auto& error : errors) {
			LoggerWindow::Log("Connection refused : " + error);
			login->SetMessage("Connection refused");
		}
	});
	ap->set_print_json_handler([](const std::list<APClient::TextNode>& msg) {
		if (GUI::filterToSelf)
		{
			bool hasSelf = false;
			for (const auto& node : msg)
				if (node.player == ap->get_player_number())
					hasSelf = true;
			if (!hasSelf)
				return;
		}
		LoggerWindow::Log(ap->render_json(msg, APClient::RenderFormat::TEXT));
	});
	ap->set_print_handler([](const std::string& msg) {
		LoggerWindow::Log(msg);
	});
	ap->set_room_info_handler([login]() {
        login->SetMessage("Room info received");
        ap->ConnectSlot(login->slot, login->password, 0b111, {}, { 0,6,0 });
        ap_connect_sent = true;
	});
	ap->set_items_received_handler([](const std::list<APClient::NetworkItem>& items) {
		if (!ap->is_data_package_valid()) {
			if (!ap_sync_queued) {
				ap_sync_queued = true;
				ap->Sync();
			}
			return;
		}
		for (const auto& item : items) {
			ItemHandler::HandleItem(item);
		}
	});
	ap->set_location_info_handler([](const std::list<APClient::NetworkItem>& items) {
		for (auto& item : items)
			API::LogPluginMessage(std::to_string(item.location));
		ShopHandler::FillShopItemNames(items);
	});
	ap->set_bounced_handler([](const json& cmd) {
		auto tagsIt = cmd.find("tags");
		auto dataIt = cmd.find("data");
		if (slotdata->deathlink) {
			if (tagsIt != cmd.end() && tagsIt->is_array()
				&& std::find(tagsIt->begin(), tagsIt->end(), "DeathLink") != tagsIt->end())
			{
				if (dataIt != cmd.end() && dataIt->is_object()) {
					json data = *dataIt;
					if (data["source"].get<std::string>() != slotName) {
						std::string source = data["source"].is_string() ? data["source"].get<std::string>().c_str() : "???";
						std::string cause = data["cause"].is_string() ? data["cause"].get<std::string>().c_str() : "???";
						LoggerWindow::Log("[color = FFFFFFFF]" + cause);
						GameHandler::KillTy(); 
					}
				}
				else {
					LoggerWindow::Log("Bad Deathlink");
				}
			}
		}
	});
}

void ArchipelagoHandler::SendLocation(int64_t locationId) {
	std::list<int64_t> check;
	check.push_back(locationId);
	ap->LocationChecks(check);
}

bool ArchipelagoHandler::IsLocationChecked(int64_t locationId) {
	const auto& checked = ap->get_checked_locations();
	return std::find(checked.begin(), checked.end(), locationId) != checked.end();
}

int ArchipelagoHandler::CountLocationsChecked(const std::list<int64_t>& locationIds)
{
	const auto& checked = ap->get_checked_locations();
	std::size_t count = 0;

	for (int64_t id : locationIds) {
		if (std::find(checked.begin(), checked.end(), id) != checked.end()) {
			++count;
		}
	}

	return count;
}

void ArchipelagoHandler::Release() {
	ap->StatusUpdate(APClient::ClientStatus::GOAL);
}

void ArchipelagoHandler::Poll() {
	while (true) {
		if (ap && polling) {
			ap->poll();
		}
	}
}
const std::vector<std::string> deathCauses{
	"didn\'t catch the boomerang",
	"bit off more than they could chew",
	"turned into a tasmanian fossil",
	"forgot to wear gloves",
	"had trouble in the outhouse",
	"couldn\'t hold their breath",
	"listened to Lenny",
	"got crushed by an icicle",
	"forgot how to glide",
	"bit the ground too hard",
	"fell over",
	"got a little too Australian",
	"didn\'t wear sunblock",
	"didn\'t listen to Lenny",
	"ate too much pie",
	"hugged a crocodile",
	"got lost in the outback",
	"died",
	"forgot eels were electric",
	"got too confident with the didgeridoo",
	"tried to ride a stingray",
	"told a dingo it wasn\'t that scary",
	"got dropkicked by a kangaroo",
	"said it wasn't their fault",
	"blames Boonie",
	"miscounted the multirangs",
	"licked a toad for science",
	"ran out of \'she\'ll be right\' energy mid-jump",
	"tried to code an AP game"
};

void ArchipelagoHandler::SetAPStatus(std::string status, char important) {
	API::LogPluginMessage("AP status: " + status);
}

std::string GetRandomCause() {
	if (deathCauses.empty()) return "";
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, deathCauses.size() - 1);
	return deathCauses[dist(gen)];
}

void ArchipelagoHandler::SendDeath() {
	std::string cause = GetRandomCause();
	LoggerWindow::Log("Death Sent:  " + slotName + " " + cause);
	json data{
		{"time", ap->get_server_time()},
		{"cause", slotName + " " + GetRandomCause()},
		{"source", slotName},
	};
	ap->Bounce(data, {}, {}, { "DeathLink" });
}

std::string ArchipelagoHandler::GetItemName(int64_t id, int player) {
	if (ap) {
		return ap->get_item_name(id, ap->get_player_game(player));
	}
	return "item id: " + id;
}

std::string ArchipelagoHandler::GetLocationName(int64_t id, int player) {
	if (ap) {
		return ap->get_location_name(id, ap->get_player_game(player));
	}
	return "loc id: " + id;
}

std::string ArchipelagoHandler::GetPlayerName(int player){
	if (ap) {
		return ap->get_player_alias(player);
	}
	return "player slot: " + player;
}

std::string ArchipelagoHandler::GetItemDesc(int player) {
	if (ap) {
		return "Item for "+ ap->get_player_alias(player) + " playing " + ap->get_player_game(player);
	}
	return "";
}

std::string ArchipelagoHandler::GetSaveIdentifier() {
	if (ap) {
		return ap->get_slot() + "_" + ap->get_seed();
	}
	return "";
}


bool ArchipelagoHandler::ScoutLocations(std::list<int64_t> locations, int create_as_hint) {
	if (ap) {
		return ap->LocationScouts(locations, create_as_hint);
	}
	return false;
}