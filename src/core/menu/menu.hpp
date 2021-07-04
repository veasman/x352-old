#pragma once
#include "../../includes.hpp"
#include "imgui/imgui.h"
#include <cstdint>
#include <filesystem>
#include <string>

//#define GROUP(name, width, height) ImGui::SameLine(); ImGui::BeginChild(name, ImVec2(ImGui::GetWindowContentRegionWidth() * width, ImGui::GetWindowHeight() * height), true);
//#define CHECKBOX(name, var) ImGui::Checkbox(name, &CONFIGBOOL(var));
#define COLOR(name, var, alpha) ImGui::SameLine(); ImGui::SetCursorPosX(ImGui::GetWindowContentRegionWidth() + 9); ImGui::ColorEdit4(name, (float*)&var, alpha ? ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoInputs)
#define COLORBOOL(name, var, alpha) ImGui::SameLine(); ImGui::SetCursorPosX(ImGui::GetWindowContentRegionWidth() + 9); if (ImGui::ColorEdit4(name, (float*)&var, alpha ? ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoInputs))
#define COMBO(name, var, items) ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth()); ImGui::Combo(name, &var, items, IM_ARRAYSIZE(items));

namespace Menu {
    inline ImFont* tahoma;
    inline bool open = true;
    inline bool initialised = false;
    inline int tabSelected = 0;

    inline char clantag[128] = "x352cheats ";
    void drawMenu();
    void drawLegitTab();
    void drawRageTab();
    void drawVisualsTab();
    void drawMiscTab();
    void drawOverlay(ImDrawList* drawList);
    void onPollEvent(SDL_Event* event, const int result);
    void onSwapWindow(SDL_Window* window);

    namespace CustomWidgets {
        void drawKeyBinder(const char* label, int* key, bool* toggled);
        bool isKeyDown(int key);
    }
}
