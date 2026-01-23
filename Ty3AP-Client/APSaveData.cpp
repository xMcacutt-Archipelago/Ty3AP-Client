#include "pch.h"
#include "APSaveData.h"

APSaveData::APSaveData() {
}

void APSaveData::CheckGoal()
{
	int completedStoryMissions  = ArchipelagoHandler::CountLocationsChecked(storyMissionLocations);
	int completedRaceMissions   = ArchipelagoHandler::CountLocationsChecked(raceMissionLocations);
	int completedBunyipMissions = ArchipelagoHandler::CountLocationsChecked(bunyipMissionLocations);
	int completedGunyipMissions = ArchipelagoHandler::CountLocationsChecked(gunyipMissionLocations);

	if (completedStoryMissions  < ArchipelagoHandler::slotdata->storyMissionsToGoal)  return;
	if (completedRaceMissions   < ArchipelagoHandler::slotdata->raceMissionsToGoal)   return;
	if (completedBunyipMissions < ArchipelagoHandler::slotdata->bunyipMissionsToGoal) return;
	if (completedGunyipMissions < ArchipelagoHandler::slotdata->gunyipMissionsToGoal) return;

	if (!this->hasShadowChassis || !this->hasGauntlet || this->shadowStoneCount < 3)  return;

	LoggerWindow::Log("The Quinking awaits...");
	SaveData::FindMissionById(Mission::QUINKING_PRE)->missionState = MissionState::AVAILABLE;
	ArchipelagoHandler::customSaveData->allowedActiveMissions.insert(Mission::QUINKING_PRE);
}
