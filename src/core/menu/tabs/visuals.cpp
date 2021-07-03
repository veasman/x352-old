#include "../menu.hpp"

const char* chamsMaterials[] = { "Default", "Flat", "Metalllic", "Multicolor", "Glow" };

void Menu::drawVisualsTab() {
    if (ImGui::BeginTabBar("##visTabs")) {
        if (ImGui::BeginTabItem("Players")) {
            ImGui::Columns(2, NULL, false);
            ImGui::SetColumnWidth(-1, ImGui::GetWindowContentRegionWidth() * 0.52);

            ImGui::BeginChild("Enemies", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.488f, ImGui::GetWindowHeight() * 0.48f), true); {
                ImGui::Text("Enemies");
                ImGui::Separator();

                if (CONFIGBOOL("Visuals>Players>Box")) {
                    ImGui::ColorEdit4("##Box Color", (float*)&CONFIGCOL("Visuals>Players>Box Color"), ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Visuals>Players>Box"));

                if (CONFIGBOOL("Visuals>Players>Skeleton")) {
                    ImGui::ColorEdit4("##Skeleton Color", (float*)&CONFIGCOL("Visuals>Players>Skeleton Color"), ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Skeleton", &CONFIGBOOL("Visuals>Players>Skeleton"));

                ImGui::Checkbox("Name", &CONFIGBOOL("Visuals>Players>Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Visuals>Players>Health"));
                if(CONFIGBOOL("Visuals>Players>Health Bar")) {
                    ImGui::ColorEdit4("##Health Bar Color", (float*)&CONFIGCOL("Visuals>Players>Health Bar Color"), ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Visuals>Players>Health Bar"));
                if(CONFIGBOOL("Visuals>Players>Health Bar")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Dynamic Color", &CONFIGBOOL("Visuals>Players>Dynamic Color"));
                }
                ImGui::Checkbox("Money", &CONFIGBOOL("Visuals>Players>Money"));
                ImGui::Checkbox("Armor", &CONFIGBOOL("Visuals>Players>Armor"));
                ImGui::Checkbox("Flashed", &CONFIGBOOL("Visuals>Players>Flashed"));
                ImGui::Checkbox("Weapon", &CONFIGBOOL("Visuals>Players>Weapon"));
                ImGui::Checkbox("Radar", &CONFIGBOOL("Visuals>Players>Radar"));
                ImGui::Checkbox("Vis Check", &CONFIGBOOL("Visuals>Players>Vis Check"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Visuals>Players>Only When Dead"));

                ImGui::EndChild();
            }

            ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.488f, 0), true); {

                ImGui::EndChild();
            }

            ImGui::NextColumn();

            ImGui::BeginChild("LocalPlayer", ImVec2(0, 0), true); {
                ImGui::Text("LocalPlayer");
                ImGui::Separator();

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(28, 5));
                ImGui::Checkbox("Spread Crosshair", &CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair"));
                ImGui::SameLine();
                ImGui::PopStyleVar();
                ImGui::ColorEdit4("##Crosshair Color", (float*)&CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Color"), ImGuiColorEditFlags_NoInputs);
                ImGui::SameLine();
                ImGui::ColorEdit4("##Crosshair Border Color", (float*)&CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Border Color"), ImGuiColorEditFlags_NoInputs);
                ImGui::Checkbox("Recoil Crosshair", &CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair"));
                // Make sure they can't both be on at the same time
                if (CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair") && !CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair")) {
                    ImGui::Checkbox("Only When Shooting", &CONFIGBOOL("Visuals>Players>LocalPlayer>Recoil Crosshair>Only When Shooting"));
                }
                ImGui::EndChild();
            }
            ImGui::Columns(1);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("World")) {
            ImGui::Columns(2, NULL, false);
            ImGui::SetColumnWidth(-1, ImGui::GetWindowContentRegionWidth() * 0.56);
            ImGui::BeginChild("World", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.548f, ImGui::GetWindowHeight() * 0.402f), true); {
                ImGui::Text("World");
                ImGui::Separator();

                ImGui::TextIndent("Camera FOV");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Camera FOV", &CONFIGINT("Visuals>World>World>FOV"), 70, 120);

                ImGui::TextIndent("Viewmodel FOV");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Viewmodel FOV", &CONFIGINT("Visuals>World>World>Viewmodel FOV"), 0, 130);

                /*if (CONFIGBOOL("Visuals>World>World>Third Person")) {
                    static bool keybindToggled;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Visuals>World>World>Third Person Key"), &keybindToggled);
                    ImGui::SameLine();
                }*/
                ImGui::Checkbox("Third Person", &CONFIGBOOL("Visuals>World>World>Third Person"));
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                if (CONFIGBOOL("Visuals>World>World>Third Person")) {
                    ImGui::SliderInt("##Third Person Distance", &CONFIGINT("Visuals>World>World>Third Person Distance"), 0, 200);
                }

                ImGui::Checkbox("Ragdoll Gravity", &CONFIGBOOL("Visuals>World>World>Ragdoll Gravity"));

                if (CONFIGBOOL("Visuals>World>World>Bullet Tracers")) {
                    ImGui::ColorEdit4("##Bullet Tracers Color", (float*)&CONFIGCOL("Visuals>World>World>Bullet Tracers Color"), ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                }

                ImGui::Checkbox("Bullet Tracers", &CONFIGBOOL("Visuals>World>World>Bullet Tracers"));
                if (CONFIGBOOL("Visuals>World>World>Bullet Tracers")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Laser", &CONFIGBOOL("Visuals>World>World>Bullet Tracers Laser"));
                }

                if (CONFIGBOOL("Visuals>World>World>Head Height")) {
                    ImGui::ColorEdit4("####Height Height Color",(float*)&CONFIGCOL("Visuals>World>World>Head Height Color"), ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                    static bool keybindToggled;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Visuals>World>World>Head Height Key"), &keybindToggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Head Height", &CONFIGBOOL("Visuals>World>World>Head Height"));

                ImGui::EndChild();
            }

            ImGui::BeginChild("World Modulation", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.548f, 0), true); {
                ImGui::Text("World Modulation");
                ImGui::Separator();

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(244, 5));
                ImGui::TextIndent("World Color"); ImGui::SameLine();
                ImGui::PopStyleVar();

                if (ImGui::ColorEdit4("##World Color Modulation", (float*)&CONFIGCOL("Visuals>World>World>World Color Modulation"), ImGuiColorEditFlags_NoInputs))
                    Features::ColorModulation::updateColorModulation();

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(236, 5));
                ImGui::TextIndent("SkyBox Color"); ImGui::SameLine();
                ImGui::PopStyleVar();

                if (ImGui::ColorEdit4("##SkyBox Color Modulation", (float*)&CONFIGCOL("Visuals>World>World>SkyBox Color Modulation"), ImGuiColorEditFlags_NoInputs))
                    Features::ColorModulation::updateColorModulation();

                if (ImGui::ButtonSpecial("Update Color Modulation"))
                    Features::ColorModulation::updateColorModulation();

                ImGui::TextIndent("NightMode");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##NightMode", &CONFIGINT("Visuals>World>World>Nightmode"), 0, 100);

                ImGui::TextIndent("Skybox");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::Combo("##Skybox", &CONFIGINT("Visuals>World>World>Skybox"), skyboxes, IM_ARRAYSIZE(skyboxes));

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(215, 5));
                ImGui::Checkbox("Override Fog", &CONFIGBOOL("Visuals>World>World>Override Fog"));
                ImGui::SameLine();
                ImGui::PopStyleVar();
                ImGui::ColorEdit4("##Fog Color", (float*)&CONFIGCOL("Visuals>World>World>Fog Color"), ImGuiColorEditFlags_NoInputs);
                ImGui::TextIndent("Fog Start");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Fog Start", &CONFIGINT("Visuals>World>World>Fog Start"), 0, 30000);
                ImGui::TextIndent("Fog End");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Fog End", &CONFIGINT("Visuals>World>World>Fog End"), 0, 30000);
                ImGui::TextIndent("Fog Density");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##Fog Density", &CONFIGINT("Visuals>World>World>Fog Density"), 0, 1000);

                ImGui::EndChild();
            }
            ImGui::SameLine();

            ImGui::NextColumn();

            ImGui::BeginChild("Items", ImVec2(0, ImGui::GetWindowHeight() * 0.46f), true); {
                ImGui::Text("Items");
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Weapon Box")) {
                    ImGui::ColorEdit4("##Weapon Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Weapon Box Color"), ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Weapon Box", &CONFIGBOOL("Visuals>World>Items>Weapon Box"));
                ImGui::Checkbox("Weapon Label", &CONFIGBOOL("Visuals>World>Items>Weapon Label"));
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Grenade Box")) {
                    ImGui::ColorEdit4("##Grenade Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Grenade Box Color"), ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Grenade Box", &CONFIGBOOL("Visuals>World>Items>Grenade Box"));
                if (CONFIGBOOL("Visuals>World>Items>Grenade Box")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Dynamic Color", &CONFIGBOOL("Visuals>World>Items>Grenade Box Dynamic Color"));
                }
                ImGui::Checkbox("Grenade Label", &CONFIGBOOL("Visuals>World>Items>Grenade Label"));
                ImGui::Checkbox("Grenade Owners", &CONFIGBOOL("Visuals>World>Items>Grenade Owners"));
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Planted C4 Box")) {
                    ImGui::ColorEdit4("##Planted C4 Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Planted C4 Box Color"), ImGuiColorEditFlags_NoInputs);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Planted C4 Box", &CONFIGBOOL("Visuals>World>Items>Planted C4 Box"));
                ImGui::Checkbox("Planted C4 Label", &CONFIGBOOL("Visuals>World>Items>Planted C4 Label"));

                ImGui::EndChild();
            }
            ImGui::BeginChild("Removals", ImVec2(0, ImGui::GetWindowHeight() * 0.38), true); {
                ImGui::Text("Removals");
                ImGui::Separator();

                ImGui::TextIndent("Smoke");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::Combo("##Smoke", &CONFIGINT("Visuals>World>Removals>Smoke"), smokeRemovals, IM_ARRAYSIZE(smokeRemovals));

                ImGui::Checkbox("No Flash", &CONFIGBOOL("Visuals>World>World>No Flash"));
                ImGui::Checkbox("No Aim Punch", &CONFIGBOOL("Visuals>World>Removals>No Aim Punch"));
                ImGui::Checkbox("No View Punch", &CONFIGBOOL("Visuals>World>Removals>No View Punch"));
                ImGui::Checkbox("No Panorama Blur", &CONFIGBOOL("Visuals>World>Removals>No Panorama Blur"));
                ImGui::Checkbox("Disable Post Processing", &CONFIGBOOL("Visuals>World>Removals>Disable Post Processing"));

                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}
