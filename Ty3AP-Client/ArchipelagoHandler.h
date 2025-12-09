#pragma once
#include "nlohmann/json.hpp"
#include "LoginWindow.h"
#include "LoggerWindow.h"
#include "APSaveData.h"
#include "SlotData.h"
#include "ItemHandler.h"
#include "GameState.h"
#include "Version.h"

#define CERT_STORE "cacert.pem"
class LoginWindow;

#define UUID_FILE "uuid"

class ArchipelagoHandler
{
public:
	static void ConnectAP(LoginWindow* login);
	static void DisconnectAP();
	static void Release();
	static void Poll();
	static void SendDeath();
	static std::string GetSaveIdentifier();
	static std::string GetItemDesc(int player);
	static std::string GetItemName(int64_t id, int player);
	static std::string GetPlayerName(int player);
	static std::string GetLocationName(int64_t id, int player);
	static bool ScoutLocations(std::list<int64_t> locations, int create_as_hint = 0);
	static void SendLocation(int64_t locationId);
	static void SetAPStatus(std::string status, char important);
	static bool LoadSaveData();
	static std::string uuid;
	static bool ap_connected;
	static bool polling;
	static bool wrongVersion;
	static std::string seed;
	static std::string slotName;
	static SlotData* slotdata;
	static APSaveData* customSaveData;
private:
	static std::unique_ptr<APClient> ap;
	static bool ap_sync_queued;
};
