#include "pch.h"
#include "LoginHandler.h"

void LoginHandler::EnableLoadButtons()
{
	while (GameState::IsInGame()) {
		
	}
	if (SaveDataHandler::doesSaveExist()) {
		auto loadGame = MKUI::FindElementByPath("MainMenu/MainMenuButtons/LoadGame");
		if (loadGame != nullptr) {
			loadGame->interactable = true;
			loadGame->enabled = true;
			loadGame->Red = 0.63f;
			loadGame->Blue = 0.63f;
			loadGame->Green = 0.63f;
		}
	}
	else {
		auto newGame = MKUI::FindElementByPath("MainMenu/MainMenuButtons/NewGame");
		if (newGame != nullptr) {
			newGame->interactable = true;
			newGame->enabled = true;
			newGame->Red = 0.63f;
			newGame->Blue = 0.63f;
			newGame->Green = 0.63f;
		}
	}
}

 
void LoginHandler::DisableLoadButtons()
{
	while (GameState::IsInGame()) {

	}
	if (!ArchipelagoHandler::ap_connected) {
		auto loadGame = MKUI::FindElementByPath("MainMenu/MainMenuButtons/LoadGame");
		if (loadGame != nullptr) {
			loadGame->interactable = false;
			loadGame->enabled = false;
			loadGame->currentlySelected = false;
			loadGame->Red = 0.4f;
			loadGame->Blue = 0.4f;
			loadGame->Green = 0.4f;
			API::LogPluginMessage("Disable load game");
		}
	}
	auto newGame = MKUI::FindElementByPath("MainMenu/MainMenuButtons/NewGame");
	if (newGame != nullptr) {
		newGame->interactable = false;
		newGame->enabled = false;
		newGame->currentlySelected = false;
		newGame->Red = 0.4f;
		newGame->Blue = 0.4f;
		newGame->Green = 0.4f;
	}
}