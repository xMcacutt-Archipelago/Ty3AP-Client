#include "pch.h"
#include "APSaveData.h"

APSaveData::APSaveData() {
}

void APSaveData::CheckGoal()
{
	int completedStoryMissions  = ArchipelagoHandler::CountLocationsChecked(storyMissionLocations);
	int completedRaceMissions   = ArchipelagoHandler::CountLocationsChecked(storyMissionLocations);
	int completedBunyipMissions = ArchipelagoHandler::CountLocationsChecked(storyMissionLocations);
	int completedGunyipMissions = ArchipelagoHandler::CountLocationsChecked(storyMissionLocations);

	if (completedStoryMissions  < ArchipelagoHandler::slotdata->storyMissionsToGoal)  return;
	if (completedRaceMissions   < ArchipelagoHandler::slotdata->raceMissionsToGoal)   return;
	if (completedBunyipMissions < ArchipelagoHandler::slotdata->bunyipMissionsToGoal) return;
	if (completedGunyipMissions < ArchipelagoHandler::slotdata->gunyipMissionsToGoal) return;

	if (!this->hasShadowChassis || !this->hasGauntlet || this->shadowStoneCount < 3)  return;

	LoggerWindow::Log("The Quinking awaits...");
	SaveData::FindMissionById(Mission::QUINKING)->missionState = MissionState::AVAILABLE;
	SaveData::FindMissionById(Mission::QUINKING - 1)->missionState = MissionState::AVAILABLE;
}
