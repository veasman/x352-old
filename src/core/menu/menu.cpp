#include "menu.hpp"
#include "imgui/imgui.h"
#include "roboto.hpp"

void style() {
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.12f, 0.80f, 0.06f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.12f, 0.50f, 0.04f, 0.62f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.24f, 0.81f, 0.19f, 0.40f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.05f, 0.95f, 0.04f, 0.40f);
    colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    /*colors[ImGuiCol_TabHovered]             = ImVec4(0.32f, 0.81f, 0.19f, 0.62f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.11f, 0.50f, 0.04f, 0.62f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.75f, 0.15f, 0.62f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);*/
    colors[ImGuiCol_TabHovered]             = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    colors[ImGuiCol_Header]                 = ImVec4(0.05f, 0.41f, 0.06f, 0.62f);
    colors[ImGuiCol_MenuCol]                = CONFIGCOL("Misc>Misc>Misc>Menu Color");


    ImGui::GetStyle().ScrollbarSize = 7;
    ImGui::GetStyle().FrameBorderSize = 1.f;
    ImGui::GetStyle().WindowPadding = ImVec2(20, 20);
    ImGui::GetStyle().DisplayWindowPadding = ImVec2(20, 20);
    ImGui::GetStyle().ScrollbarRounding = 0;
    ImGui::GetStyle().WindowRounding = 0;
    ImGui::GetStyle().ChildRounding = 0;
    ImGui::GetStyle().FrameRounding = 0;
    ImGui::GetStyle().TabRounding = 0;
}

void Menu::onPollEvent(SDL_Event* event, const int result) {
    if (result && ImGui_ImplSDL2_ProcessEvent(event) && Menu::open) {
        event->type = 0;
    }
}

void Menu::onSwapWindow(SDL_Window* window) {
    if (!initialised) {
        gl3wInit();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 100");
        ImGui_ImplSDL2_InitForOpenGL(window, nullptr);
        style();
        ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 13.f);
        initialised = true;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);

    ImGuiIO& io = ImGui::GetIO();
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    Globals::screenSizeX = w;
    Globals::screenSizeY = h;
    io.DisplaySize = ImVec2((float)w, (float)h);

    ImGui::NewFrame();

    Menu::drawOverlay(ImGui::GetBackgroundDrawList());
    if (Menu::open) {
        io.MouseDrawCursor = true; // TODO: find workaround at some point because ugly
        Menu::drawMenu();
    }
    else {
        io.MouseDrawCursor = false;
    }


    if (ImGui::IsKeyPressed(SDL_SCANCODE_INSERT, false)) {
        Config::reloadCfgList();
        Menu::open = !Menu::open;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void Menu::drawMenu() {
    ImGui::SetNextWindowSize(ImVec2{700, 627});
    ImGui::Begin("x352 cheats", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 4));
    ImGui::Text("x352"); ImGui::SameLine(); ImGui::PopStyleVar();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(272, 5));
    ImGui::TextColored(ImGui::GetStyle().Colors[ImGuiCol_MenuCol], "cheats");

    ImGui::SameLine();
    ImGui::PopStyleVar();

    auto bWidth = ImVec2(80, 20);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 5));

    ImGui::GetStyle().Colors[ImGuiCol_Button] = (Menu::tabSelected == 0) ? ImVec4(0.05f, 0.41f, 0.06f, 0.62f) : ImVec4(0.03f, 0.23f, 0.04f, 0.62f);
    if (ImGui::Button("Legit", bWidth)) {
        Menu::tabSelected = 0;
    } ImGui::SameLine();

    ImGui::GetStyle().Colors[ImGuiCol_Button] = (Menu::tabSelected == 1) ? ImVec4(0.05f, 0.41f, 0.06f, 0.62f) : ImVec4(0.03f, 0.23f, 0.04f, 0.62f);
    if (ImGui::Button("Rage", bWidth)) {
        Menu::tabSelected = 1;
    } ImGui::SameLine();

    ImGui::GetStyle().Colors[ImGuiCol_Button] = (Menu::tabSelected == 2) ? ImVec4(0.05f, 0.41f, 0.06f, 0.62f) : ImVec4(0.03f, 0.23f, 0.04f, 0.62f);
    if (ImGui::Button("Visuals", bWidth)) {
        Menu::tabSelected = 2;
    } ImGui::SameLine();

    ImGui::GetStyle().Colors[ImGuiCol_Button] = (Menu::tabSelected == 3) ? ImVec4(0.05f, 0.41f, 0.06f, 0.62f) : ImVec4(0.03f, 0.23f, 0.04f, 0.62f);
    if (ImGui::Button("Misc", bWidth)) {
        Menu::tabSelected = 3;
    }
    ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.05f, 0.41f, 0.06f, 0.62f);
    ImGui::PopStyleVar();

    ImGui::Separator();
    ImGui::Separator();

    switch(tabSelected) {
        case 0: {
            Menu::drawLegitTab(); break;
        }
        case 1: {
            Menu::drawRageTab(); break;
        }
        case 2: {
            Menu::drawVisualsTab(); break;
        }
        case 3: {
            Menu::drawMiscTab();break;
        }
    }

    ImGui::End();
}
