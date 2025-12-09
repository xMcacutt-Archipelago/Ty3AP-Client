#pragma once
#include "ArchipelagoHandler.h"
#include "CheckHandler.h"
#include "APSaveData.h"
#include "nlohmann/json.hpp"
#include "ShopHandler.h"

class SaveDataHandler
{
public:
	struct SaveCallbackInfo {
		std::function<void()> callback;
		DWORD esi;
		int framesRemaining;
		bool active;
	};
	static inline char* saveFileBuffer = nullptr;
	static inline int saveFileLength = 0;
	static inline SaveCallbackInfo g_SaveCallback = { nullptr,0, 0, false };
	static void LoadAPSaveFile();
	static int RecalcSaveDataSize();
	static int SaveFile(const char* filename, void* data, int size);
	static void write_json_file(const std::string& filename);
	static void read_json_file(const std::string& filename);
	static void RunLoadSetup(SlotData* slotdata);
	static bool doesSaveExist();
	static bool hasRunSetup;
};

