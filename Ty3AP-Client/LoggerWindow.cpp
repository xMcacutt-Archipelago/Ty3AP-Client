#include "pch.h"
#include "LoggerWindow.h"

void LoggerWindow::ToggleVisibility() {
    isVisible = !isVisible;
}

void LoggerWindow::Draw(int outerWidth, int outerHeight, float uiScale) {
    if (!isVisible)
        return;

    UpdateVisibleMessages();

    // Render the Logger window at the bottom-left
    ImGui::SetNextWindowPos(ImVec2(10, outerHeight - 500 - 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Always);
    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowFontScale(uiScale + 0.3f);

    // Get the window draw list for custom drawing
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 window_pos = ImGui::GetCursorScreenPos();
    ImVec2 window_size = ImGui::GetContentRegionAvail();

    float y_pos = window_pos.y + window_size.y;

    // Iterate messages in reverse order (newest at bottom)
    for (int i = visibleMessages.size() - 1; i >= 0; --i) {
        const LogMessage& log = visibleMessages[i];
        float x_pos = window_pos.x;
        float max_width = window_size.x;

        // Remove color tags and format the raw text for wrapping
        if (log.message.empty() or &log.message == nullptr)
            continue;
        std::string rawMessage = RemoveColorTags(log.message);

        std::vector<std::string> wrappedLines;
        std::string currentLine;
        float totalTextHeight = 0.0f;
        float maxLineWidth = 0.0f; // Track the longest line's width

        std::istringstream words(rawMessage);
        std::string word;

        // Wrap the plain raw text before applying colors
        while (words >> word) {
            std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
            ImVec2 textSize = ImGui::CalcTextSize(testLine.c_str());

            // If text exceeds max width, wrap to the next line
            if (textSize.x > max_width && !currentLine.empty()) {
                wrappedLines.push_back(currentLine);
                maxLineWidth = std::max(maxLineWidth, ImGui::CalcTextSize(currentLine.c_str()).x);
                totalTextHeight += ImGui::CalcTextSize(currentLine.c_str()).y;
                currentLine = word;  // Start new line with current word
            }
            else {
                currentLine = testLine;  // Keep adding words to the line
            }
        }

        // Add the last line if it exists
        if (!currentLine.empty()) {
            wrappedLines.push_back(currentLine);
            maxLineWidth = std::max(maxLineWidth, ImGui::CalcTextSize(currentLine.c_str()).x);
            totalTextHeight += ImGui::CalcTextSize(currentLine.c_str()).y;
        }

        maxLineWidth += 5.0f;

        // Draw the background box for the whole wrapped message
        float messageStartY = y_pos - totalTextHeight - (2.0f * wrappedLines.size());

        // Only add a background box if there's actual text
        if (!wrappedLines.empty()) {
            ImVec2 box_min = ImVec2(window_pos.x, messageStartY);
            ImVec2 box_max = ImVec2(window_pos.x + maxLineWidth, y_pos);
            draw_list->AddRectFilled(box_min, box_max, IM_COL32(0, 0, 0, 100));  // Background for the message
        }

        // Iterate over wrapped lines and render them
        for (auto lineIt = wrappedLines.rbegin(); lineIt != wrappedLines.rend(); ++lineIt) {
            ImVec2 text_size = ImGui::CalcTextSize(lineIt->c_str());
            y_pos -= text_size.y + 2.0f; // Move y-position down for next line

            // Render the formatted text with the current line
            RenderFormattedText(draw_list, lineIt->c_str(), ImVec2(x_pos, y_pos)); // Render the formatted text
        }

        // Add space between messages for separation
        y_pos -= 5.0f;  // Adjust this space for gap between messages
    }
    ImGui::End();
}

// Function to remove color tags from the text
std::string LoggerWindow::RemoveColorTags(const std::string& text) {
    static const std::regex colorTag(R"(\[color\s*=\s*[0-9a-fA-F]{8}\])");
    return std::regex_replace(text, colorTag, "");
}

void LoggerWindow::RenderFormattedText(ImDrawList* draw_list, const char* text, ImVec2 pos) {
    // Define keywords and associated colors
    const std::unordered_map<std::string, ImU32> keywordColors = {
        {"Fire Stone", IM_COL32(0xD6, 0x06, 0x06, 0xFF)},
        {"Water Stone", IM_COL32(0x1A, 0x2E, 0xDB, 0xFF)},
        {"Air Stone", IM_COL32(0x47, 0xFF, 0x4A, 0xFF)},
        {"Earth Stone", IM_COL32(0x63, 0x5D, 0x03, 0xFF)},
        {"Chrono Stone", IM_COL32(0xAF, 0x03, 0xFF, 0xFF)},
        {"Warp Stone", IM_COL32(0xAF, 0x7C, 0xEB, 0xFF)},
        {"Ultra Stone", IM_COL32(0xA6, 0xE9, 0xF5, 0xFF)},
        {"Mega Stone", IM_COL32(0xB1, 0xF5, 0xA6, 0xFF)},
        {"Multi Stone", IM_COL32(0xFF, 0x8C, 0x00, 0xFF)},
        {"Zoom Stone", IM_COL32(0x9B, 0x94, 0xD6, 0xFF)},
        {"Magnet Stone", IM_COL32(0xFC, 0xC1, 0x92, 0xFF)},
        {"Shadow Stone", IM_COL32(0x99, 0x66, 0xff, 0xFF)},
        {"Kromium Orb", IM_COL32(0xFF, 0x00, 0x00, 0xFF)},
        {"Gooboo Berry", IM_COL32(0xF2, 0x03, 0xFF, 0xFF)},
        {"Bilby", IM_COL32(0x73, 0x91, 0xFF, 0xFF)},
        {"Opals", IM_COL32(0xFF, 0x3D, 0x3B, 0xFF)},
        {"Duo Chassis", IM_COL32(0x85, 0x85, 0x85, 0xFF)},
        {"Lash Chassis", IM_COL32(0xE8, 0xE4, 0x43, 0xFF)},
        {"Smash Chassis", IM_COL32(0x66, 0x65, 0x26, 0xFF)},
        {"Mega Chassis", IM_COL32(0x5A, 0x77, 0x78, 0xFF)},
        {"Ring Chassis", IM_COL32(0xBA, 0xA8, 0xA8, 0xFF)},
        {"Shadow Chassis", IM_COL32(0x35, 0x00, 0x78, 0xFF)},
        {"Doom Chassis", IM_COL32(0xFF, 0xD5, 0x03, 0xFF)},
        {"Shadow Beam", IM_COL32(0x24, 0xD9, 0x1E, 0xFF)},
        {"Grav Grenade", IM_COL32(0x1E, 0x95, 0xD9, 0xFF)},
        {"Satellite Strike", IM_COL32(0x24, 0xD9, 0x1E, 0xFF)},
        {"Thermo Cannon", IM_COL32(0xD9, 0xCD, 0x1E, 0xFF)},
        {"Nucleon Shield", IM_COL32(0xD9, 0xCD, 0x1E, 0xFF)},
        {"Orbidrills", IM_COL32(0x1E, 0x95, 0xD9, 0xFF)},
        {"Missing Persons Map", IM_COL32(0x73, 0x91, 0xFF, 0xFF)},
        {"Shiny Thing Map", IM_COL32(0xFF, 0x00, 0x00, 0xFF)},
        {"Sekrit Map", IM_COL32(0x77, 0xB5, 0x2B, 0xFF)},
        {"Priceless Art Map", IM_COL32(0xF5, 0xC6, 0x1D, 0xFF)},
        {"Forbidden Fruit Map", IM_COL32(0xF2, 0x03, 0xFF, 0xFF)},
        {"Bunyip Gauntlet", IM_COL32(0x66, 0xEB, 0x5B, 0xFF)},
        {"Duke", IM_COL32(0x8C, 0x5D, 0x38, 0xFF)},
        {"Sly", IM_COL32(0xD6, 0x77, 0x2D, 0xFF)},
        {"Karlos", IM_COL32(0xBA, 0xB3, 0xC7, 0xFF)},
        {"Crabmersible", IM_COL32(0xFF, 0xA9, 0x00, 0xFF)},
        {"Southern Rivers Gate", IM_COL32(0xCC, 0x00, 0x00, 0xFF)},
        {"Cinder Canyon", IM_COL32(0xC2, 0xA8, 0x6B, 0xFF)},
        {"Dead Dingo Marsh", IM_COL32(0x4D, 0xA3, 0x60, 0xFF)},
        {"Gooboo Gully", IM_COL32(0x48, 0xAB, 0x00, 0xFF)},
        {"Kaka Boom Island", IM_COL32(0x26, 0xA9, 0xD1, 0xFF)},
        {"Mount Boom Basin", IM_COL32(0x26, 0xD1, 0x48, 0xFF)},
        {"Quinking", IM_COL32(0xA6, 0x00, 0xCF, 0xFF)},
        {"Rang", IM_COL32(0xCF, 0x87, 0x00, 0xFF)},
        {"Stone", IM_COL32(0xC2, 0x85, 0x65, 0xFF)},
        {"Steve", IM_COL32(0x77, 0xB5, 0x2B, 0xFF)},
        {"Picture Frame", IM_COL32(0xF5, 0xC6, 0x1D, 0xFF)},
        {"Mission", IM_COL32(0x1D, 0xF5, 0x21, 0xFF)},
        {"Shop", IM_COL32(0xF5, 0xE0, 0x1D, 0xFF)},
    };

    ImU32 current_color = IM_COL32(255, 255, 255, 255); // Default white
    const char* segment_start = text;
    const char* s = text;
    float x_pos = pos.x;
    std::cmatch match;

    static const std::regex colorTag(R"(\[color\s*=\s*([0-9a-fA-F]{8})\])");
    while (*s) {
        if (std::regex_search(s, match, colorTag)) {
            if (segment_start < s) {
                draw_list->AddText(ImVec2(x_pos, pos.y), current_color, segment_start, s);
                x_pos += ImGui::CalcTextSize(segment_start, s).x;
            }
        
            unsigned int rgba;
            sscanf_s(match[1].first, "%8x", &rgba);
            unsigned int r = (rgba >> 24) & 0xFF;
            unsigned int g = (rgba >> 16) & 0xFF;
            unsigned int b = (rgba >> 8) & 0xFF;
            unsigned int a = (rgba >> 0) & 0xFF;
            ImU32 color = IM_COL32(r, g, b, a);
            s = match[0].second;

            segment_start = s;
            continue;
        }

        bool keyword_hit = false;
        for (const auto& [keyword, color] : keywordColors) {
            size_t len = keyword.length();
            if (compareStrings(s, keyword.c_str(), len) && (s[len] == ' ' || s[len] == '\0')) {
                // Draw previous segment before keyword
                if (segment_start < s) {
                    draw_list->AddText(ImVec2(x_pos, pos.y), current_color, segment_start, s);
                    x_pos += ImGui::CalcTextSize(segment_start, s).x;
                }
                // Draw keyword in highlighted color
                draw_list->AddText(ImVec2(x_pos, pos.y), color, s, s + len);
                x_pos += ImGui::CalcTextSize(s, s + len).x;
                s += len;
                segment_start = s;
                keyword_hit = true;
                break; // Restart loop from new position
            }
		}
        if (keyword_hit)
            continue;
    
        s++;
    }
    if (segment_start < s) {
        draw_list->AddText(ImVec2(x_pos, pos.y), current_color, segment_start, s);
        x_pos += ImGui::CalcTextSize(segment_start, s).x;
    }
}

void LoggerWindow::AddLogMessage(const std::string& message) {
    LogMessage logMessage = { message, std::chrono::steady_clock::now() };
    cachedMessages.push(logMessage);
}

void LoggerWindow::UpdateVisibleMessages() {
    auto now = std::chrono::steady_clock::now();

    visibleMessages.erase(std::remove_if(visibleMessages.begin(), visibleMessages.end(),
        [now, this](const LogMessage& msg) {
            return std::chrono::duration_cast<std::chrono::seconds>(now - msg.timestamp).count() > TIMEOUT_SECONDS;
        }), visibleMessages.end());

    while (!cachedMessages.empty() && visibleMessages.size() < MAX_MESSAGES) {
        cachedMessages.front().timestamp = now;
        visibleMessages.push_back(cachedMessages.front());
        cachedMessages.pop();
    }
}

void LoggerWindow::Log(const std::string& message)
{
    for (auto& window : GUI::windows) {
        if (auto logger = dynamic_cast<LoggerWindow*>(window.get())) {
            logger->AddLogMessage(message);
            break;
        }
    }
}

