#include "pch.h"
#include "TrackerWindow.h"

void TrackerWindow::ToggleVisibility() {
    isVisible = !isVisible;
    if (!isVisible)
        LoggerWindow::Log("When the tracker is toggled off, you can view it while holding T.");
}

void TrackerWindow::Draw(int outerWidth, int outerHeight, float uiScale) {
    if (!isVisible && !visibleOverride)
        return;

    if (!GameHandler::IsSaveSelected())
        return;

    auto windowWidth = 690 * uiScale;
    auto windowHeight = 340 * uiScale;
    auto iconSize = 48 * uiScale;
    auto padding = 10 * uiScale;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6.0f * uiScale, 4.5 * uiScale));
    ImGui::Begin(
        name.c_str(),
        nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_AlwaysAutoResize
    );
    ImGui::SetWindowFontScale(uiScale + 0.3f);

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    bool b = false;
    float brightness = 0.0f;
    ImVec4 tintColor;
    const float lowBright = 0.4f;
    const float semiBright = 0.7f;
    const float fullBright = 1.0f;

    if (ArchipelagoHandler::slotdata->storyMissionsToGoal > 0) {
        auto cursorPos = ImGui::GetCursorScreenPos();
        tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["story"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
        ImGui::SameLine();

        auto storyLocsChecked = ArchipelagoHandler::CountLocationsChecked(APSaveData::storyMissionLocations);
        for (int missionIndex = 0; missionIndex < ArchipelagoHandler::slotdata->storyMissionsToGoal; missionIndex++) {
            cursorPos = ImGui::GetCursorScreenPos();
            b = storyLocsChecked > missionIndex;
            brightness = b ? fullBright : lowBright;
            tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
            ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["mission"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

    if (ArchipelagoHandler::slotdata->bunyipMissionsToGoal > 0) {
        auto cursorPos = ImGui::GetCursorScreenPos();
        tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["bunyip"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
        ImGui::SameLine();
        auto bunyipLocsChecked = ArchipelagoHandler::CountLocationsChecked(APSaveData::bunyipMissionLocations);
        for (int missionIndex = 0; missionIndex < ArchipelagoHandler::slotdata->bunyipMissionsToGoal; missionIndex++) {
            cursorPos = ImGui::GetCursorScreenPos();
            b = bunyipLocsChecked > missionIndex;
            brightness = b ? fullBright : lowBright;
            tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
            ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["mission"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

    if (ArchipelagoHandler::slotdata->gunyipMissionsToGoal > 0) {
        auto cursorPos = ImGui::GetCursorScreenPos();
        tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["gunyip"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
        ImGui::SameLine();

        auto gunyipLocsChecked = ArchipelagoHandler::CountLocationsChecked(APSaveData::gunyipMissionLocations);
        for (int missionIndex = 0; missionIndex < ArchipelagoHandler::slotdata->gunyipMissionsToGoal; missionIndex++) {
            cursorPos = ImGui::GetCursorScreenPos();
            b = gunyipLocsChecked > missionIndex;
            brightness = b ? fullBright : lowBright;
            tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
            ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["mission"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

    if (ArchipelagoHandler::slotdata->raceMissionsToGoal > 0) {
        auto cursorPos = ImGui::GetCursorScreenPos();
        tintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["race"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
        ImGui::SameLine();
        auto raceLocsChecked = ArchipelagoHandler::CountLocationsChecked(APSaveData::raceMissionLocations);
        for (int missionIndex = 0; missionIndex < ArchipelagoHandler::slotdata->raceMissionsToGoal; missionIndex++) {
            cursorPos = ImGui::GetCursorScreenPos();
            b = raceLocsChecked > missionIndex;
            brightness = b ? fullBright : lowBright;
            tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
            ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["mission"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

    b = ArchipelagoHandler::customSaveData->hasGauntlet;
    brightness = b ? fullBright : lowBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["gauntlet"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    ImGui::SameLine();

    b = ArchipelagoHandler::customSaveData->hasCrab;
    brightness = b ? fullBright : lowBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["crabmersible"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    ImGui::SameLine();

    b = ArchipelagoHandler::customSaveData->hasSouthernRiversGate;
    brightness = b ? fullBright : lowBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["gate"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    ImGui::SameLine();

    b = ArchipelagoHandler::customSaveData->hasUnlockedSly;
    brightness = b ? fullBright : lowBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["sly"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    ImGui::SameLine();

    b = ArchipelagoHandler::customSaveData->hasUnlockedDuke;
    brightness = b ? fullBright : lowBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["duke"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    ImGui::SameLine();

    b = ArchipelagoHandler::customSaveData->hasUnlockedKarlos;
    brightness = b ? fullBright : lowBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["karlos"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    ImGui::SameLine();

    auto cursorPos = ImGui::GetCursorScreenPos();
    int count = ArchipelagoHandler::customSaveData->shadowStoneCount;
    brightness = semiBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["shadow_stone"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    auto textSize = ImGui::CalcTextSize(std::to_string(count).c_str());
    auto textPos = ImVec2(cursorPos.x + (iconSize - textSize.x) * 0.5f,
        cursorPos.y + (iconSize - textSize.y) * 0.5f);
    drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), std::to_string(count).c_str());    
    ImGui::SameLine();

    b = ArchipelagoHandler::customSaveData->hasShadowChassis;
    brightness = b ? fullBright : lowBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["shadow_chassis"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);

    cursorPos = ImGui::GetCursorScreenPos();
    b = ArchipelagoHandler::customSaveData->hasUnlockedCinder && ArchipelagoHandler::customSaveData->hasUnlockedDuke;
    brightness = semiBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["level"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    textSize = ImGui::CalcTextSize("C");
    textPos = ImVec2(cursorPos.x + (iconSize - textSize.x) * 0.5f,
        cursorPos.y + (iconSize - textSize.y) * 0.5f);
    drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), "C");
    ImGui::SameLine();

    cursorPos = ImGui::GetCursorScreenPos();
    b = ArchipelagoHandler::customSaveData->hasUnlockedMarsh;
    brightness = semiBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["level"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    textSize = ImGui::CalcTextSize("D");
    textPos = ImVec2(cursorPos.x + (iconSize - textSize.x) * 0.5f,
        cursorPos.y + (iconSize - textSize.y) * 0.5f);
    drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), "D");
    ImGui::SameLine();

    cursorPos = ImGui::GetCursorScreenPos();
    b = ArchipelagoHandler::customSaveData->hasUnlockedDuke && ArchipelagoHandler::customSaveData->hasUnlockedKakaboom;
    brightness = semiBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["level"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    textSize = ImGui::CalcTextSize("K");
    textPos = ImVec2(cursorPos.x + (iconSize - textSize.x) * 0.5f,
        cursorPos.y + (iconSize - textSize.y) * 0.5f);
    drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), "K");
    ImGui::SameLine();

    cursorPos = ImGui::GetCursorScreenPos();
    b = ArchipelagoHandler::customSaveData->hasUnlockedGully;
    brightness = semiBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["level"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    textSize = ImGui::CalcTextSize("G");
    textPos = ImVec2(cursorPos.x + (iconSize - textSize.x) * 0.5f,
        cursorPos.y + (iconSize - textSize.y) * 0.5f);
    drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), "G");
    ImGui::SameLine();

    cursorPos = ImGui::GetCursorScreenPos();
    b = ArchipelagoHandler::customSaveData->hasUnlockedBasin && ArchipelagoHandler::customSaveData->hasUnlockedDuke;
    brightness = semiBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["level"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);
    textSize = ImGui::CalcTextSize("M");
    textPos = ImVec2(cursorPos.x + (iconSize - textSize.x) * 0.5f,
        cursorPos.y + (iconSize - textSize.y) * 0.5f);
    drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), "M");
    ImGui::SameLine();

    b = ArchipelagoHandler::customSaveData->hasUnlockedFinal;
    brightness = b ? fullBright : lowBright;
    tintColor = ImVec4(brightness, brightness, brightness, 1.0f);
    ImGui::ImageWithBg((ImTextureID)(intptr_t)GUI::icons["quinking"], ImVec2(iconSize, iconSize), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), tintColor);

    ImVec2 windowSize = ImGui::GetWindowSize();
    ImGui::SetWindowPos(
        ImVec2(
            (outerWidth - windowSize.x) * 0.5f,
            padding
        ),
        ImGuiCond_Always
    );

    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}