#include "../menu.hpp"

const char* antiAimTypes[] = {"None", "Static", "Jitter", "Fake Jitter", "Real Jitter", "SpingBot (p100)"};

void Menu::drawRageTab() {
    ImGui::BeginChild("Rage", ImVec2((ImGui::GetWindowContentRegionWidth()/2) - 4, 0), true); {
        ImGui::Text("RageBot");
        ImGui::Separator();
        ImGui::Checkbox("Enabled", &CONFIGBOOL("Rage>RageBot>Enabled"));
        // NOTE: This will only be needed *if* I built out the ragebot.
        //       Commenting it out for now, so the menu looks nicer.
        //if (ImGui::BeginTabBar("Weapons Tabbar")) {
            //if (ImGui::BeginTabItem("Default")) {
                ImGui::Checkbox("Resolver", &CONFIGBOOL("Rage>RageBot>Default>Resolver"));
                ImGui::Checkbox("Force Baim if health < X", &CONFIGBOOL("Rage>RageBot>Default>ForceBaim"));
                if(CONFIGBOOL("Rage>RageBot>Default>ForceBaim")) {
                    ImGui::TextIndent("Health");
                    ImGui::SliderInt("##HEALTH", &CONFIGINT("Rage>RageBot>Default>ForceBaimValue"), 1, 100);
                }
                ImGui::TextIndent("FOV (x10)");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##FOV", &CONFIGINT("Rage>RageBot>Default>FOV"), 0, 1800);
                //ImGui::EndTabItem();
            //}
            //ImGui::EndTabBar();
        //}
        ImGui::EndChild();
    }
    ImGui::SameLine();
    ImGui::BeginChild("Anti-Aim", ImVec2(0, 0), true); {
        ImGui::Text("Anti-Aim");
        ImGui::Separator();

        ImGui::Checkbox("Enabled", &CONFIGBOOL("Rage>AntiAim>Enabled"));

        ImGui::TextIndent("Type");
        ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
        ImGui::Combo("##Type", &CONFIGINT("Rage>AntiAim>Type"), antiAimTypes, IM_ARRAYSIZE(antiAimTypes));

        if (CONFIGINT("Rage>AntiAim>Type")) {
            ImGui::TextIndent("Pitch");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Pitch", &CONFIGINT("Rage>AntiAim>Pitch"), -89, 89);

            ImGui::TextIndent("Yaw Offset");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Offset", &CONFIGINT("Rage>AntiAim>Offset"), 0, 360);

            ImGui::TextIndent("FakeLag");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##FakeLag", &CONFIGINT("Rage>AntiAim>FakeLag"), 0, 16);
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 1) { // Static
            ImGui::TextIndent("Desync");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Desync", &CONFIGINT("Rage>AntiAim>Static>Desync"), -60, 60);
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 2) { // Jitter
            ImGui::TextIndent("Desync");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Desync", &CONFIGINT("Rage>AntiAim>Jitter>Desync"), -60, 60);

            ImGui::TextIndent("Jitter Amount");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Amount", &CONFIGINT("Rage>AntiAim>Jitter>Jitter Amount"), 0, 180);

            ImGui::TextIndent("Jitter Delay");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Delay", &CONFIGINT("Rage>AntiAim>Jitter>Jitter Delay"), 1, 256);

            ImGui::Checkbox("Random", &CONFIGBOOL("Rage>AntiAim>Jitter>Random"));
            if (CONFIGBOOL("Rage>AntiAim>Jitter>Random")) {
                ImGui::TextIndent("Random Min");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Min", &CONFIGINT("Rage>AntiAim>Jitter>Random Min"), 0, 180);

                ImGui::TextIndent("Random Max");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Max", &CONFIGINT("Rage>AntiAim>Jitter>Random Max"), 0, 180);
            }
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 3) { // Fake Jitter
            ImGui::TextIndent("Jitter Amount");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Amount", &CONFIGINT("Rage>AntiAim>Fake Jitter>Jitter Amount"), 0, 60);

            ImGui::TextIndent("Jitter Delay");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Delay", &CONFIGINT("Rage>AntiAim>Fake Jitter>Jitter Delay"), 1, 256);

            ImGui::Checkbox("Random", &CONFIGBOOL("Rage>AntiAim>Fake Jitter>Random"));
            if (CONFIGBOOL("Rage>AntiAim>Fake Jitter>Random")) {
                ImGui::TextIndent("Random Min");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Min", &CONFIGINT("Rage>AntiAim>Fake Jitter>Random Min"), 0, 60);

                ImGui::TextIndent("Random Max");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Max", &CONFIGINT("Rage>AntiAim>Fake Jitter>Random Max"), 0, 60);
            }
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 4) { // Real Jitter
            ImGui::TextIndent("Jitter Amount");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Amount", &CONFIGINT("Rage>AntiAim>Real Jitter>Jitter Amount"), 0, 60);

            ImGui::TextIndent("Jitter Delay");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Jitter Delay", &CONFIGINT("Rage>AntiAim>Real Jitter>Jitter Delay"), 1, 256);

            ImGui::Checkbox("Random", &CONFIGBOOL("Rage>AntiAim>Fake Jitter>Random"));
            if (CONFIGBOOL("Rage>AntiAim>Real Jitter>Random")) {
                ImGui::TextIndent("Random Min");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Min", &CONFIGINT("Rage>AntiAim>Real Jitter>Random Min"), 0, 60);

                ImGui::TextIndent("Random Max");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Random Max", &CONFIGINT("Rage>AntiAim>Real Jitter>Random Max"), 0, 60);
            }
        }

        if (CONFIGINT("Rage>AntiAim>Type") == 5) { // Sping
            ImGui::TextIndent("Desync");
            ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::SliderInt("##Desync", &CONFIGINT("Rage>AntiAim>Spin>Desync"), -60, 60);
        }
        ImGui::Checkbox("Slow Walk",&CONFIGBOOL("Rage>AntiAim>Slow Walk"));
        ImGui::SliderInt("Slow Walk Speed (%)", &CONFIGINT("Rage>AntiAim>Slow Walk Speed"), 0, 255);
        ImGui::EndChild();
    }
}
