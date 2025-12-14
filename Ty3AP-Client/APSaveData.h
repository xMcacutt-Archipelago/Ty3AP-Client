#pragma once
#include "Mission.h"
#include "SaveData.h"
#include "LoggerWindow.h"

class APSaveData
{
public:
	APSaveData();
	bool hasBoughtItem(int id) {
		return ItemMap[id];
	}
	void updateBoughtItem(int id, bool bought) {
		ItemMap[id] = bought;
	}
	void CheckGoal();
	int pLastReceivedIndex = -1;
	int berryCount = 0;
	int orbCount = 0;
	int bilbyCount = 0;
	bool hasUnlockedDuke = false;
	bool hasUnlockedKakaboom = false;
	bool hasUnlockedBasin = false;
	bool hasUnlockedCinder = false;
	int shadowStoneCount = 0;
	bool hasShadowChassis = false;
	bool hasGauntlet = false;
	std::map<int, bool> ItemMap = {
		
	};

	static inline std::list<int64_t> storyMissionLocations = {
		0x6d00 + Mission::SAVE_THE_DREAMING,
		0x6d00 + Mission::RESCUE_THE_GENERAL,
		0x6d00 + Mission::BROWN_KIWI_DOWN,
		0x6d00 + Mission::RESCUE_JULIUS,
		0x6d00 + Mission::HEINOUS_HEXAQUIN,
		0x6d00 + Mission::MEET_SHAZZA,
		0x6d00 + Mission::SEA_CHANGE,
		0x6d00 + Mission::BATTLE_ARENA_GAMMA,
		0x6d00 + Mission::THE_SEARCH_FOR_STEVE,
		0x6d00 + Mission::FIND_THE_SHADOWRING,
		0x6d00 + Mission::BATTLE_ARENA_ZETA,
		0x6d00 + Mission::GO_FIND_BOSS_CASS
	};

	static inline std::list<int64_t> raceMissionLocations = {
		0x6d00 + Mission::THE_BIG_RACE,
		0x6d00 + Mission::EXPERI_MENTAL_CART,
		0x6d00 + Mission::DENNIS_DILEMMA,
		0x6d00 + Mission::DEMOLITION_DERBY,
		0x6d00 + Mission::RESPECT_EFFECT,
		0x6d00 + Mission::REDBACK_STASH,
	};

	static inline std::list<int64_t> bunyipMissionLocations = {
		0x6d00 + Mission::QUINKAN_ARMADA,
		0x6d00 + Mission::EGG_HUNT,
		0x6d00 + Mission::POWER_STRUGGLE,
		0x6d00 + Mission::MELTDOWN,
		0x6d00 + Mission::RANGER_ENDANGER,
		0x6d00 + Mission::REDBACK_RUNDOWN
	};

	static inline std::list<int64_t> gunyipMissionLocations = {
		0x6d00 + Mission::ALL_YOUR_BASE,
		0x6d00 + Mission::AERO_COAST_GUARD,
		0x6d00 + Mission::WRATH_OF_THE_DRAGONQUIN,
		0x6d00 + Mission::FOREST_FIREPOWER,
	};
};