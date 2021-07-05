#include "../menu.hpp"

const char* chamsMaterials[] = { "Default", "Flat", "Metallic", "Multicolor", "Glow" };

void Menu::drawVisualsTab() {
    if (ImGui::BeginTabBar("##visTabs")) {
        if (ImGui::BeginTabItem("Players")) {
            ImGui::Columns(2, NULL, false);
            ImGui::SetColumnWidth(-1, (ImGui::GetWindowContentRegionWidth() * 0.50) + 5);

            ImGui::BeginChild("Enemies", ImVec2((ImGui::GetWindowContentRegionWidth() / 2) - 4, ImGui::GetWindowHeight() * 0.48f), true); {
                ImGui::Text("Enemies");
                ImGui::Separator();

                //ImGui::Checkbox("Teammates", &CONFIGBOOL("Visuals>Players>Teammates"));

                ImGui::Checkbox("Box", &CONFIGBOOL("Visuals>Players>Box"));
                COLOR("##Box Color", CONFIGCOL("Visuals>Players>Box Color"), false);

                ImGui::Checkbox("Skeleton", &CONFIGBOOL("Visuals>Players>Skeleton"));
                COLOR("##Skeleton Color", CONFIGCOL("Visuals>Players>Skeleton Color"), false);

                ImGui::Checkbox("Name", &CONFIGBOOL("Visuals>Players>Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Visuals>Players>Health"));

                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Visuals>Players>Health Bar"));
                COLOR("##Health Bar Color", CONFIGCOL("Visuals>Players>Health Bar Color"), false);

                if(CONFIGBOOL("Visuals>Players>Health Bar")) {
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

            ImGui::BeginChild("Chams", ImVec2((ImGui::GetWindowContentRegionWidth() / 2) - 4, 0), true); {
                ImGui::Checkbox("Enemies", &CONFIGBOOL("Visuals>Players>Chams>Enemies>Enabled"));
                COLOR("##Enemy Visible Color", CONFIGCOL("Visuals>Players>Chams>Enemies>Visible Color"), true);

                ImGui::Checkbox("Enemies Occluded", &CONFIGBOOL("Visuals>Players>Chams>Enemies>Occluded Enabled"));
                COLOR("##Enemy Occluded Color", CONFIGCOL("Visuals>Players>Chams>Enemies>Occluded Color"), true);

                if (CONFIGBOOL("Visuals>Players>Chams>Enemies>Enabled") || CONFIGBOOL("Visuals>Players>Chams>Enemies>Occluded Enabled")) {
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::Combo("##Enemy Material", &CONFIGINT("Visuals>Players>Chams>Enemies>Material"), chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
                    if (CONFIGINT("Visuals>Players>Chams>Enemies>Material") == 4) {
                        COLOR("##Enemy Overlay Color", CONFIGCOL("Visuals>Players>Chams>Enemies>Overlay Color"), true);
                    }
                }

                ImGui::Checkbox("Teammates", &CONFIGBOOL("Visuals>Players>Chams>Teammates>Enabled"));
                COLOR("##Teammate Visible Color", CONFIGCOL("Visuals>Players>Chams>Teammates>Visible Color"), true);

                ImGui::Checkbox("Teammates Occluded", &CONFIGBOOL("Visuals>Players>Chams>Teammates>Occluded Enabled"));
                COLOR("##Teammate Occluded Color", CONFIGCOL("Visuals>Players>Chams>Teammates>Occluded Color"), true);

                if (CONFIGBOOL("Visuals>Players>Chams>Teammates>Enabled") || CONFIGBOOL("Visuals>Players>Chams>Teammates>Occluded Enabled")) {
                    COMBO("##Teammate Material", CONFIGINT("Visuals>Players>Chams>Teammates>Material"), chamsMaterials);
                    if (CONFIGINT("Visuals>Players>Chams>Teammates>Material") == 4) {
                        COLOR("##Teammate Overlay Color", CONFIGCOL("Visuals>Players>Chams>Teammates>Overlay Color"), true);
                    }
                }

                ImGui::Checkbox("History", &CONFIGBOOL("Visuals>Players>Chams>Enemies>Backtrack Enabled"));
                COLOR("##History Color", CONFIGCOL("Visuals>Players>Chams>Enemies>Backtrack Color"), true);

                if (CONFIGBOOL("Visuals>Players>Chams>Enemies>Backtrack Enabled")) {
                    COMBO("##History Material", CONFIGINT("Visuals>Players>Chams>Enemies>Backtrack Material"), chamsMaterials);
                    if (CONFIGINT("Visuals>Players>Chams>Enemies>Backtrack Material") == 4) {
                        COLOR("##History Overlay Color", CONFIGCOL("Visuals>Players>Chams>Enemies>Backtrack Overlay Color"), true);
                    }
                }

                ImGui::Checkbox("Weapon", &CONFIGBOOL("Visuals>Players>Chams>Weapon Enabled"));
                COLOR("##Weapon Color", CONFIGCOL("Visuals>Players>Chams>Weapon Color"), true);

                if (CONFIGBOOL("Visuals>Players>Chams>Weapon Enabled")) {
                    COMBO("##Weapon Material", CONFIGINT("Visuals>Players>Chams>Weapon Material"), chamsMaterials);
                    if (CONFIGINT("Visuals>Players>Chams>Weapon Material") == 4) {
                        COLOR("##Weapon Overlay Color", CONFIGCOL("Visuals>Players>Chams>Weapon Overlay Color"), true);
                    }
                }

                ImGui::Checkbox("Arms", &CONFIGBOOL("Visuals>Players>Chams>Arms Enabled"));
                COLOR("##Arms Color", CONFIGCOL("Visuals>Players>Chams>Arms Color"), true);

                if (CONFIGBOOL("Visuals>Players>Chams>Arms Enabled")) {
                    COMBO("##Arms Material", CONFIGINT("Visuals>Players>Chams>Arms Material"), chamsMaterials);
                    if (CONFIGINT("Visuals>Players>Chams>Arms Material") == 4) {
                        COLOR("##Arms Overlay Color", CONFIGCOL("Visuals>Players>Chams>Arms Overlay Color"), true);
                    }
                }

                ImGui::Checkbox("Sleeves", &CONFIGBOOL("Visuals>Players>Chams>Sleeve Enabled"));
                COLOR("##Sleeve Color", CONFIGCOL("Visuals>Players>Chams>Sleeve Color"), true);

                if (CONFIGBOOL("Visuals>Players>Chams>Sleeve Enabled")) {
                    COMBO("##Sleeves Material", CONFIGINT("Visuals>Players>Chams>Sleeve Material"), chamsMaterials);
                    if (CONFIGINT("Visuals>Players>Chams>Sleeve Material") == 4) {
                        COLOR("##Sleeves Overlay Color", CONFIGCOL("Visuals>Players>Chams>Sleeve Overlay Color"), true);
                    }
                }

                ImGui::EndChild();
            }

            ImGui::NextColumn();

            ImGui::BeginChild("LocalPlayer", ImVec2(0, 0), true); {
                ImGui::Text("LocalPlayer");
                ImGui::Separator();

                ImGui::Checkbox("Spread Crosshair", &CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair"));
                COLOR("##Crosshair Color", CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Color"), true);
                //COLOR("##Crosshair Border Color", CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Border Color"), true);

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

                ImGui::Checkbox("Bullet Tracers", &CONFIGBOOL("Visuals>World>World>Bullet Tracers"));
                if (CONFIGBOOL("Visuals>World>World>Bullet Tracers")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Laser", &CONFIGBOOL("Visuals>World>World>Bullet Tracers Laser"));
                }
                COLOR("##Bullet Tracers Color", CONFIGCOL("Visuals>World>World>Bullet Tracers Color"), false);

                if (CONFIGBOOL("Visuals>World>World>Head Height")) {
                    static bool keybindToggled;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Visuals>World>World>Head Height Key"), &keybindToggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Head Height", &CONFIGBOOL("Visuals>World>World>Head Height"));
                COLOR("####Height Height Color",CONFIGCOL("Visuals>World>World>Head Height Color"), false);

                ImGui::EndChild();
            }

            ImGui::BeginChild("World Modulation", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.548f, 0), true); {
                ImGui::Text("World Modulation");
                ImGui::Separator();

                ImGui::TextIndent("World Color");

                COLORBOOL("##World Color Modulation", CONFIGCOL("Visuals>World>World>World Color Modulation"), false) {
                    Features::ColorModulation::updateColorModulation();
                }

                ImGui::TextIndent("SkyBox Color");

                COLORBOOL("##SkyBox Color Modulation", CONFIGCOL("Visuals>World>World>SkyBox Color Modulation"), false) {
                    Features::ColorModulation::updateColorModulation();
                }

                if (ImGui::ButtonSpecial("Update Color Modulation"))
                    Features::ColorModulation::updateColorModulation();

                /*ImGui::TextIndent("NightMode");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::SliderInt("##NightMode", &CONFIGINT("Visuals>World>World>Nightmode"), 0, 100);*/

                ImGui::TextIndent("Skybox");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::Combo("##Skybox", &CONFIGINT("Visuals>World>World>Skybox"), skyboxes, IM_ARRAYSIZE(skyboxes));

                ImGui::Checkbox("Override Fog", &CONFIGBOOL("Visuals>World>World>Override Fog"));
                COLOR("##Fog Color", CONFIGCOL("Visuals>World>World>Fog Color"), false);

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

                ImGui::Checkbox("Weapon Box", &CONFIGBOOL("Visuals>World>Items>Weapon Box"));
                COLOR("##Weapon Box Color", CONFIGCOL("Visuals>World>Items>Weapon Box Color"), false);

                ImGui::Checkbox("Weapon Label", &CONFIGBOOL("Visuals>World>Items>Weapon Label"));

                ImGui::Checkbox("Grenade Box", &CONFIGBOOL("Visuals>World>Items>Grenade Box"));
                COLOR("##Grenade Box Color", CONFIGCOL("Visuals>World>Items>Grenade Box Color"), false);

                if (CONFIGBOOL("Visuals>World>Items>Grenade Box")) {
                    ImGui::Checkbox("Dynamic Color", &CONFIGBOOL("Visuals>World>Items>Grenade Box Dynamic Color"));
                }

                ImGui::Checkbox("Grenade Label", &CONFIGBOOL("Visuals>World>Items>Grenade Label"));
                ImGui::Checkbox("Grenade Owners", &CONFIGBOOL("Visuals>World>Items>Grenade Owners"));

                ImGui::Checkbox("Planted C4 Box", &CONFIGBOOL("Visuals>World>Items>Planted C4 Box"));
                COLOR("##Planted C4 Box Color", CONFIGCOL("Visuals>World>Items>Planted C4 Box Color"), false);

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
