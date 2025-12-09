#include "pch.h"
#include "LoginHandler.h"

void LoginHandler::EnableLoadButtons()
{
	if (IsInGame()) {
		return;
	}
	auto buttongroup = MKUI::FindChildElementByName(MKUI::GetMainMenu(), "MainMenuButtons");
	if (buttongroup == nullptr) {
		API::LogPluginMessage("Button group does not exist here");
		return;
	}
	if (SaveDataHandler::doesSaveExist()) {
		UIElementStruct* loadgame = MKUI::FindChildElementByName(buttongroup, "LoadGame");
		if (loadgame != nullptr) {
			loadgame->interactable = true;
			loadgame->enabled = true;
			loadgame->Red = 0.63f;
			loadgame->Blue = 0.63f;
			loadgame->Green = 0.63f;
		}
	}
	else {
		UIElementStruct* newgame = MKUI::FindChildElementByName(buttongroup, "NewGame");
		if (newgame != nullptr) {
			newgame->interactable = true;
			newgame->enabled = true;
			newgame->Red = 0.63f;
			newgame->Blue = 0.63f;
			newgame->Green = 0.63f;
		}
	}
}

 
void LoginHandler::DisableLoadButtons()
{
	auto buttongroup = MKUI::FindChildElementByName(MKUI::GetMainMenu(), "MainMenuButtons");
	if (buttongroup == nullptr) {
		return;
	}
	UIElementStruct* loadgame = MKUI::FindChildElementByName(buttongroup, "LoadGame");
	if (loadgame != nullptr) {
		loadgame->interactable = false;
		loadgame->enabled = false;
		loadgame->currentlySelected = false;
		loadgame->Red = 0.4f;
		loadgame->Blue = 0.4f;
		loadgame->Green = 0.4f;
		API::LogPluginMessage("Disable load game");
	}
	UIElementStruct* newgame = MKUI::FindChildElementByName(buttongroup, "NewGame");
	if (newgame != nullptr) {
		newgame->interactable = false;
		newgame->enabled = false;
		newgame->currentlySelected = false;
		newgame->Red = 0.4f;
		newgame->Blue = 0.4f;
		newgame->Green = 0.4f;
	}
}