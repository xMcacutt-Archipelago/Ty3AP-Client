#include "pch.h"
#include "ItemHandler.h"


std::queue<APClient::NetworkItem> ItemHandler::storedItems;

void ItemHandler::HandleItem(APClient::NetworkItem item)
{
	if (!GameHandler::IsSaveSelected()) {
        storedItems.push(item);
		return;
	}

	if (item.index <= ArchipelagoHandler::customSaveData->pLastReceivedIndex) {
		return;
	}

	ArchipelagoHandler::customSaveData->pLastReceivedIndex++;

    switch (item.item) {
    case Ty3Item::Sly:
		ArchipelagoHandler::customSaveData->hasUnlockedSly = true;
        SaveData::FindMissionById(Mission::SLY_MISSION)->missionState = MissionState::COMPLETE;
        SaveData::FindMissionById(Mission::QUINKAN_ARMADA)->missionState = MissionState::AVAILABLE;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::QUINKAN_ARMADA] = MissionState::AVAILABLE;
        SaveData::FindMissionById(Mission::EGG_HUNT)->missionState = MissionState::AVAILABLE;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::EGG_HUNT] = MissionState::AVAILABLE;
        SaveData::FindMissionById(Mission::POWER_STRUGGLE)->missionState = MissionState::AVAILABLE;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::POWER_STRUGGLE] = MissionState::AVAILABLE;
        SaveData::FindMissionById(Mission::MELTDOWN)->missionState = MissionState::AVAILABLE;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::MELTDOWN] = MissionState::AVAILABLE;
        SaveData::FindMissionById(Mission::RANGER_ENDANGER)->missionState = MissionState::AVAILABLE;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::RANGER_ENDANGER] = MissionState::AVAILABLE;
        SaveData::FindMissionById(Mission::REDBACK_RUNDOWN)->missionState = MissionState::AVAILABLE;
		ArchipelagoHandler::customSaveData->savedBunyipStatuses[Mission::REDBACK_RUNDOWN] = MissionState::AVAILABLE;
        break;
    case Ty3Item::Duke:
		ArchipelagoHandler::customSaveData->hasUnlockedDuke = true;
        SaveData::FindMissionById(Mission::DUKE_MISSION)->missionState = MissionState::COMPLETE;
		SaveData::FindMissionById(Mission::WRATH_OF_THE_DRAGONQUIN)->missionState = MissionState::AVAILABLE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::WRATH_OF_THE_DRAGONQUIN);
        SaveData::FindMissionById(Mission::ALL_YOUR_BASE)->missionState = MissionState::AVAILABLE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::ALL_YOUR_BASE);
        SaveData::FindMissionById(Mission::AERO_COAST_GUARD)->missionState = MissionState::AVAILABLE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::AERO_COAST_GUARD);
        SaveData::FindMissionById(Mission::FOREST_FIREPOWER)->missionState = MissionState::AVAILABLE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::FOREST_FIREPOWER);
        if (ArchipelagoHandler::customSaveData->hasUnlockedBasin) {
			SaveData::FindMissionById(Mission::FIND_THE_SHADOWRING)->missionState = MissionState::ACTIVE;
            ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::FIND_THE_SHADOWRING);
        }
        if (ArchipelagoHandler::customSaveData->hasUnlockedKakaboom) {
            SaveData::FindMissionById(Mission::SEA_CHANGE)->missionState = MissionState::AVAILABLE;
            ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::SEA_CHANGE);
        }
        if (ArchipelagoHandler::customSaveData->hasUnlockedCinder) {
			SaveData::FindMissionById(Mission::BROWN_KIWI_DOWN)->missionState = MissionState::AVAILABLE;
            ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::BROWN_KIWI_DOWN);
        }
        break;
    case Ty3Item::Karlos:
		ArchipelagoHandler::customSaveData->hasUnlockedKarlos = true;
        SaveData::FindMissionById(Mission::KARLOS_MISSION)->missionState = MissionState::COMPLETE;
        SaveData::FindMissionById(Mission::BATTLE_ARENA_GAMMA)->missionState = MissionState::AVAILABLE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::BATTLE_ARENA_GAMMA);
        SaveData::FindMissionById(Mission::BATTLE_ARENA_ZETA)->missionState = MissionState::AVAILABLE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::BATTLE_ARENA_ZETA);
        SaveData::FindMissionById(Mission::RESCUE_JULIUS)->missionState = MissionState::AVAILABLE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::RESCUE_JULIUS);
        GameHandler::OnChunkLoaded();
        break;
    case Ty3Item::Crabmersible:
		ArchipelagoHandler::customSaveData->hasCrab = true;
        SaveData::FindMissionById(Mission::CRAB_MISSION)->missionState = MissionState::COMPLETE;
        SaveData::FindMissionById(Mission::CRAB_INTRO)->missionState = MissionState::COMPLETE;
        break;
    case Ty3Item::SouthernRiversGate:
		ArchipelagoHandler::customSaveData->hasSouthernRiversGate = true;
        SaveData::FindMissionById(Mission::SWAMP_MISSION)->missionState = MissionState::COMPLETE;
        break;
    case Ty3Item::CinderCanyon:
        ArchipelagoHandler::customSaveData->hasUnlockedCinder = true;
        if (ArchipelagoHandler::customSaveData->hasUnlockedDuke) {
            SaveData::FindMissionById(Mission::BROWN_KIWI_DOWN)->missionState = MissionState::AVAILABLE;
            ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::BROWN_KIWI_DOWN);
        }
        break;
    case Ty3Item::DeadDingoMarsh:
        ArchipelagoHandler::customSaveData->hasUnlockedMarsh = true;
        SaveData::FindMissionById(Mission::MEET_SHAZZA)->missionState = MissionState::ACTIVE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::MEET_SHAZZA);
        break;
    case Ty3Item::GoobooGully:
		ArchipelagoHandler::customSaveData->hasUnlockedGully = true;
        SaveData::FindMissionById(Mission::THE_SEARCH_FOR_STEVE)->missionState = MissionState::ACTIVE;
        ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::THE_SEARCH_FOR_STEVE);
        break;
    case Ty3Item::KakaBoomIsland:
        ArchipelagoHandler::customSaveData->hasUnlockedKakaboom = true;
        if (ArchipelagoHandler::customSaveData->hasUnlockedDuke) {
            SaveData::FindMissionById(Mission::SEA_CHANGE)->missionState = MissionState::AVAILABLE;
            ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::SEA_CHANGE);
        }
        break;
    case Ty3Item::MountBoomBasin:
        ArchipelagoHandler::customSaveData->hasUnlockedBasin = true;
        if (ArchipelagoHandler::customSaveData->hasUnlockedDuke) {
            SaveData::FindMissionById(Mission::FIND_THE_SHADOWRING)->missionState = MissionState::ACTIVE;
            ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::FIND_THE_SHADOWRING);
        }
        break;
    case Ty3Item::ShadowBeam:
		SaveData::FindItemById(Item::SHADOW_BEAM)->numOwned++;
        break;
    case Ty3Item::GravGrenade:
        SaveData::FindItemById(Item::GRAV_GRENADE)->numOwned++;
        break;
    case Ty3Item::SatelliteStrike:
        SaveData::FindItemById(Item::SATELLITE_STRIKE)->numOwned++;
        break;
    case Ty3Item::ThermoCannon:
        SaveData::FindItemById(Item::THERMO_CANNON)->numOwned++;
        break;
    case Ty3Item::NucleonShield:
        SaveData::FindItemById(Item::NUCLEON_SHIELD)->numOwned++;
        break;
    case Ty3Item::Orbidrills:
        SaveData::FindItemById(Item::ORBIDRILLS)->numOwned++;
        break;
    case Ty3Item::MissingPersonsMap:
        SaveData::FindItemById(Item::MISSING_PERSONS_MAP)->numOwned++;
        break;
    case Ty3Item::ShinyThingMap:
        SaveData::FindItemById(Item::SHINY_THING_MAP)->numOwned++;
        break;
    case Ty3Item::SekritMap:
        SaveData::FindItemById(Item::SEKRIT_MAP)->numOwned++;
        break;
    case Ty3Item::PricelessArtMap:
        SaveData::FindItemById(Item::PRICELESS_ART_MAP)->numOwned++;
        break;
    case Ty3Item::ForbiddenFruitMap:
        SaveData::FindItemById(Item::FORBIDDEN_FRUIT_MAP)->numOwned++;
        break;
    case Ty3Item::BunyipGauntlet:
        SaveData::FindItemById(Item::BUNYIP_GAUNTLET)->numOwned++;
        ArchipelagoHandler::customSaveData->hasGauntlet = true;
        ArchipelagoHandler::customSaveData->CheckGoal();
        break;
    case Ty3Item::ShadowStone1:
        SaveData::FindItemById(Item::SHADOW_STONE)->numOwned++;
        ArchipelagoHandler::customSaveData->shadowStoneCount++;
        ArchipelagoHandler::customSaveData->CheckGoal();
        break;
    case Ty3Item::ShadowStone2:
        SaveData::FindItemById(Item::SHADOW_STONE)->numOwned++;
        ArchipelagoHandler::customSaveData->shadowStoneCount++;
        ArchipelagoHandler::customSaveData->CheckGoal();
        break;
    case Ty3Item::ShadowStone3:
        SaveData::FindItemById(Item::SHADOW_STONE)->numOwned++;
        ArchipelagoHandler::customSaveData->shadowStoneCount++;
        ArchipelagoHandler::customSaveData->CheckGoal();
        break;
    case Ty3Item::DuoChassis:
        SaveData::FindItemById(Item::DUO_CHASSIS)->numOwned++;
        break;
    case Ty3Item::LashChassis:
        SaveData::FindItemById(Item::LASH_CHASSIS)->numOwned++;
        break;
    case Ty3Item::SmashChassis:
        SaveData::FindItemById(Item::SMASH_CHASSIS)->numOwned++;
        break;
    case Ty3Item::MegaChassis:
        SaveData::FindItemById(Item::MEGA_CHASSIS)->numOwned++;
        break;
    case Ty3Item::RingChassis:
        SaveData::FindItemById(Item::RING_CHASSIS)->numOwned++;
        break;
    case Ty3Item::ShadowChassis:
        SaveData::FindItemById(Item::SHADOW_CHASSIS)->numOwned++;
        ArchipelagoHandler::customSaveData->hasShadowChassis = true;
        ArchipelagoHandler::customSaveData->CheckGoal();
        break;
    case Ty3Item::DoomChassis:
        SaveData::FindItemById(Item::DOOM_CHASSIS)->numOwned++;
        break;
    case Ty3Item::FireStone:
		SaveData::FindItemById(Item::FIRE_STONE)->numOwned++;
        break;
    case Ty3Item::WaterStone:
		SaveData::FindItemById(Item::WATER_STONE)->numOwned++;
        break;
    case Ty3Item::AirStone:
		SaveData::FindItemById(Item::AIR_STONE)->numOwned++;
        break;
    case Ty3Item::EarthStone:
		SaveData::FindItemById(Item::EARTH_STONE)->numOwned++;
        break;
    case Ty3Item::ChronoStone:
		SaveData::FindItemById(Item::CHRONO_STONE)->numOwned++;
        break;
    case Ty3Item::WarpStone:
		SaveData::FindItemById(Item::WARP_STONE)->numOwned++;
        break;
    case Ty3Item::UltraStone:
		SaveData::FindItemById(Item::ULTRA_STONE)->numOwned++;
        break;
    case Ty3Item::MegaStone:
		SaveData::FindItemById(Item::MEGA_STONE)->numOwned++;
        break;
    case Ty3Item::MultiStone:
		SaveData::FindItemById(Item::MULTI_STONE)->numOwned++;
        break;
    case Ty3Item::ZoomStone:
		SaveData::FindItemById(Item::ZOOM_STONE)->numOwned++;
        break;
    case Ty3Item::MagnetStone:
		SaveData::FindItemById(Item::MAGNET_STONE)->numOwned++;
        break;

    case Ty3Item::KromiumOrb:
        ArchipelagoHandler::customSaveData->orbCount++;
        SaveData::GetData()->orbsCollected++;
        break;
    case Ty3Item::GoobooBerry:
        ArchipelagoHandler::customSaveData->berryCount++;
        SaveData::GetData()->berriesCollected++;
        break;
    case Ty3Item::Bilby:
        ArchipelagoHandler::customSaveData->bilbyCount++;
        SaveData::GetData()->bilbiesCollected++;
        break;

    case Ty3Item::Opals50:
        ItemHandler::AddOpals(50);
        break;
    case Ty3Item::Opals100:
        ItemHandler::AddOpals(100);
        break;
    case Ty3Item::Opals250:
        ItemHandler::AddOpals(250);
        break;
    case Ty3Item::Opals500:
        ItemHandler::AddOpals(500);
        break;
    case Ty3Item::Opals1k:
        ItemHandler::AddOpals(1000);
        break;
    case Ty3Item::FullHeal:
        *(int*)(Core::moduleBase + 0x48D3BC) = 4;
        break;
    }

	std::string filePath = "./Saves/" + ArchipelagoHandler::GetSaveIdentifier();
	SaveDataHandler::write_json_file(filePath + ".json");
    
    *(int*)(Core::moduleBase + 0x490400) = 0;
    void (*save)() = reinterpret_cast<void(*)()>(Core::moduleBase + 0x2527A0);
    save();
}

void ItemHandler::HandleStoredItems()
{
	if (!GameHandler::IsSaveSelected()) {
		API::LogPluginMessage("Cannot handle stored items, not in game\n", LogLevel::Info);
    }
	while (!storedItems.empty() && GameHandler::IsSaveSelected()) {
        
        HandleItem(storedItems.front());
		storedItems.pop();
	}
}