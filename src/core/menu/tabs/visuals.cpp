#include "../menu.hpp"

const char* chamsMaterials[] = {"None", "Shaded", "Flat", "Screen Pulse", "Energy Ball", "Glow", "Plastic", "Darude", "Oil"};

void drawChamsWidget(const char* label,
                    int* material, ImColor* color,
                    int* overlayMaterial, ImColor* overlayColor,
                    bool occluded = false, int* occludedMaterial = nullptr, ImColor* occludedColor = nullptr,
                    bool backtrack = false, int* backtrackMaterial = nullptr, ImColor* backtrackColor = nullptr, bool* backtrackTrail = nullptr,
                    bool* wireframe = nullptr, bool* overlayWireframe = nullptr) {
    char btnLabel[64];
    snprintf(btnLabel, sizeof(btnLabel), "Chams##%s", label);
    int spacing = 30;
    /*if (ImGui::Button(btnLabel)) {
        ImGui::OpenPopup(btnLabel);
    }
    if (ImGui::BeginPopup(btnLabel)) {*/
        ImGui::TextIndent("%s Chams", label);

        //ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 5));

        ImGui::Combo("##Chams Material", material, chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
        ImGui::SameLine();
        ImGui::PopStyleVar();

        ImGui::ColorEdit4("##Chams Color", (float*)color, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        /*if (wireframe) {
            ImGui::Checkbox("Wireframe ##Visible Wireframe", wireframe);
        }*/

        ImGui::TextIndent("%s Chams Overlay", label);

        //ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 5));

        ImGui::Combo("##Chams Overlay Material", overlayMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
        ImGui::SameLine();
        ImGui::PopStyleVar();

        ImGui::ColorEdit4("##Chams Overlay Color", (float*)overlayColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        /*if (overlayWireframe) {
            ImGui::Checkbox("Wireframe ##Visible Overlay Wireframe", overlayWireframe);
        }*/

        if (occluded) {
            ImGui::TextIndent("%s Occluded Chams", label);

            //ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 5));

            ImGui::Combo("##Occluded Chams Material", occludedMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
            ImGui::SameLine();
            ImGui::PopStyleVar();

            ImGui::ColorEdit4("##Occluded Chams Color", (float*)occludedColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
        }
        if (backtrack) {
            ImGui::TextIndent("%s Backtrack Chams", label);

            //ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, 5));

            ImGui::Combo("##Backtrack Chams Material", backtrackMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials));
            ImGui::SameLine();
            ImGui::PopStyleVar();

            ImGui::ColorEdit4("##Backtrack Chams Color", (float*)backtrackColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
            ImGui::Checkbox("Trail", backtrackTrail);
        }
        //ImGui::EndPopup();
    //}
}

void Menu::drawVisualsTab() {
    if (ImGui::BeginTabBar("##visTabs")) {
        if (ImGui::BeginTabItem("Players")) {
            ImGui::Columns(3, NULL, false);
            ImGui::SetColumnWidth(-1, ImGui::GetWindowContentRegionWidth() * 0.33);

            ImGui::BeginChild("Teammates", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.318f, ImGui::GetWindowHeight() * 0.57f), true); {
                ImGui::Text("Teammates");
                ImGui::Separator();

                if (CONFIGBOOL("Visuals>Players>Teammates>Box")) {
                    ImGui::ColorEdit4("##Box Color", (float*)&CONFIGCOL("Visuals>Players>Teammates>Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Visuals>Players>Teammates>Box"));

                if (CONFIGBOOL("Visuals>Players>Teammates>Skeleton")) {
                    ImGui::ColorEdit4("##Skeleton Color", (float*)&CONFIGCOL("Visuals>Players>Teammates>Skeleton Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Skeleton", &CONFIGBOOL("Visuals>Players>Teammates>Skeleton"));

                ImGui::Checkbox("Name", &CONFIGBOOL("Visuals>Players>Teammates>Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Visuals>Players>Teammates>Health"));
                if(CONFIGBOOL("Visuals>Players>Teammates>Health Bar")) {
                    ImGui::ColorEdit4("##Health Bar Color", (float*)&CONFIGCOL("Visuals>Players>Teammates>Health Bar Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Visuals>Players>Teammates>Health Bar"));
                if(CONFIGBOOL("Visuals>Players>Teammates>Health Bar")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Dynamic Color", &CONFIGBOOL("Visuals>Players>Teammates>Dynamic Color"));
                }
                ImGui::Checkbox("Money", &CONFIGBOOL("Visuals>Players>Teammates>Money"));
                ImGui::Checkbox("Armor", &CONFIGBOOL("Visuals>Players>Teammates>Armor"));
                ImGui::Checkbox("Weapon", &CONFIGBOOL("Visuals>Players>Teammates>Weapon"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Visuals>Players>Teammates>Only When Dead"));

                ImGui::EndChild();
            }

            ImGui::BeginChild("Teammate Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.318f, 0), true); {
                drawChamsWidget("Teammates",
                    &CONFIGINT("Visuals>Players>Teammates>Chams>Visible Material"), &CONFIGCOL("Visuals>Players>Teammates>Chams>Visible Color"),
                    &CONFIGINT("Visuals>Players>Teammates>Chams>Visible Overlay Material"), &CONFIGCOL("Visuals>Players>Teammates>Chams>Visible Overlay Color"),
                    true, &CONFIGINT("Visuals>Players>Teammates>Chams>Occluded Material"), &CONFIGCOL("Visuals>Players>Teammates>Chams>Occluded Color"),
                    false, nullptr, nullptr, nullptr,
                    &CONFIGBOOL("Visuals>Players>Teammates>Chams>Visible Wireframe"), &CONFIGBOOL("Visuals>Players>Teammates>Chams>Visible Overlay Wireframe"));

                ImGui::EndChild();
            }

            ImGui::NextColumn();
            ImGui::SetColumnWidth(-1, ImGui::GetWindowContentRegionWidth() * 0.33);

            ImGui::BeginChild("Enemies", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.318f, ImGui::GetWindowHeight() * 0.46f), true); {
                ImGui::Text("Enemies");
                ImGui::Separator();

                if (CONFIGBOOL("Visuals>Players>Enemies>Box")) {
                    ImGui::ColorEdit4("##Box Color", (float*)&CONFIGCOL("Visuals>Players>Enemies>Box Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Box", &CONFIGBOOL("Visuals>Players>Enemies>Box"));

                if (CONFIGBOOL("Visuals>Players>Enemies>Skeleton")) {
                    ImGui::ColorEdit4("##Skeleton Color", (float*)&CONFIGCOL("Visuals>Players>Enemies>Skeleton Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Skeleton", &CONFIGBOOL("Visuals>Players>Enemies>Skeleton"));

                ImGui::Checkbox("Name", &CONFIGBOOL("Visuals>Players>Enemies>Name"));
                ImGui::Checkbox("Health", &CONFIGBOOL("Visuals>Players>Enemies>Health"));
                if(CONFIGBOOL("Visuals>Players>Enemies>Health Bar")) {
                    ImGui::ColorEdit4("##Health Bar Color", (float*)&CONFIGCOL("Visuals>Players>Enemies>Health Bar Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Health Bar", &CONFIGBOOL("Visuals>Players>Enemies>Health Bar"));
                if(CONFIGBOOL("Visuals>Players>Enemies>Health Bar")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Dynamic Color", &CONFIGBOOL("Visuals>Players>Enemies>Dynamic Color"));
                }
                ImGui::Checkbox("Money", &CONFIGBOOL("Visuals>Players>Enemies>Money"));
                ImGui::Checkbox("Armor", &CONFIGBOOL("Visuals>Players>Enemies>Armor"));
                ImGui::Checkbox("Flashed", &CONFIGBOOL("Visuals>Players>Enemies>Flashed"));
                ImGui::Checkbox("Weapon", &CONFIGBOOL("Visuals>Players>Enemies>Weapon"));
                ImGui::Checkbox("Radar", &CONFIGBOOL("Visuals>Players>Enemies>Radar"));
                //ImGui::Checkbox("Forwardtrack Dots", &CONFIGBOOL("Visuals>Players>Enemies>Forwardtrack Dots"));
                ImGui::Checkbox("Vis Check", &CONFIGBOOL("Visuals>Players>Enemies>Vis Check"));
                ImGui::Checkbox("Only When Dead", &CONFIGBOOL("Visuals>Players>Enemies>Only When Dead"));

                ImGui::EndChild();
            }

            ImGui::BeginChild("Enemy Chams", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.318f, 0), true); {
                drawChamsWidget("Enemies",
                    &CONFIGINT("Visuals>Players>Enemies>Chams>Visible Material"), &CONFIGCOL("Visuals>Players>Enemies>Chams>Visible Color"),
                    &CONFIGINT("Visuals>Players>Enemies>Chams>Visible Overlay Material"), &CONFIGCOL("Visuals>Players>Enemies>Chams>Visible Overlay Color"),
                    true, &CONFIGINT("Visuals>Players>Enemies>Chams>Occluded Material"), &CONFIGCOL("Visuals>Players>Enemies>Chams>Occluded Color"),
                    true, &CONFIGINT("Visuals>Players>Enemies>Chams>Backtrack Material"), &CONFIGCOL("Visuals>Players>Enemies>Chams>Backtrack Color"), &CONFIGBOOL("Visuals>Players>Enemies>Chams>Trail"),
                    &CONFIGBOOL("Visuals>Players>Enemies>Chams>Visible Wireframe"), &CONFIGBOOL("Visuals>Players>Enemies>Chams>Visible Overlay Wireframe"));

                ImGui::EndChild();
            }

            ImGui::NextColumn();

            ImGui::BeginChild("LocalPlayer", ImVec2(0, 0), true); {
                ImGui::Text("LocalPlayer");
                ImGui::Separator();

                //ImGui::Checkbox("Velocity Text", &CONFIGBOOL("Visuals>Players>LocalPlayer>Velocity Text"));
                ImGui::Text("Arms");
                drawChamsWidget("Arm",
                    &CONFIGINT("Visuals>Players>LocalPlayer>Arms Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Arms Color"),
                    &CONFIGINT("Visuals>Players>LocalPlayer>Arms Overlay Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Arms Overlay Color"),
                    false, nullptr, nullptr,
                    false, nullptr, nullptr, nullptr,
                    &CONFIGBOOL("Visuals>Players>LocalPlayer>Arms Wireframe"), &CONFIGBOOL("Visuals>Players>LocalPlayer>Arms Overlay Wireframe"));
                ImGui::Separator();

                ImGui::Text("Sleeve");
                drawChamsWidget("Sleeve",
                    &CONFIGINT("Visuals>Players>LocalPlayer>Sleeve Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Sleeve Color"),
                    &CONFIGINT("Visuals>Players>LocalPlayer>Sleeve Overlay Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Sleeve Overlay Color"),
                    false, nullptr, nullptr,
                    false, nullptr, nullptr, nullptr,
                    &CONFIGBOOL("Visuals>Players>LocalPlayer>Sleeve Wireframe"), &CONFIGBOOL("Visuals>Players>LocalPlayer>Sleeve Overlay Wireframe"));
                ImGui::Separator();

                ImGui::Text("Weapons");
                drawChamsWidget("Weapon",
                    &CONFIGINT("Visuals>Players>LocalPlayer>Weapon Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Weapon Color"),
                    &CONFIGINT("Visuals>Players>LocalPlayer>Weapon Overlay Material"), &CONFIGCOL("Visuals>Players>LocalPlayer>Weapon Overlay Color"),
                    false, nullptr, nullptr,
                    false, nullptr, nullptr, nullptr,
                    &CONFIGBOOL("Visuals>Players>LocalPlayer>Weapon Wireframe"), &CONFIGBOOL("Visuals>Players>LocalPlayer>Weapon Overlay Wireframe"));

                ImGui::Separator();
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(28, 5));
                ImGui::Checkbox("Spread Crosshair", &CONFIGBOOL("Visuals>Players>LocalPlayer>Spread Crosshair"));
                ImGui::SameLine();
                ImGui::PopStyleVar();
                ImGui::ColorEdit4("##Crosshair Color", (float*)&CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                ImGui::SameLine();
                ImGui::ColorEdit4("##Crosshair Border Color", (float*)&CONFIGCOL("Visuals>Players>LocalPlayer>Crosshair Border Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
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
                    ImGui::ColorEdit4("##Bullet Tracers Color", (float*)&CONFIGCOL("Visuals>World>World>Bullet Tracers Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }

                ImGui::Checkbox("Bullet Tracers", &CONFIGBOOL("Visuals>World>World>Bullet Tracers"));
                if (CONFIGBOOL("Visuals>World>World>Bullet Tracers")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Laser", &CONFIGBOOL("Visuals>World>World>Bullet Tracers Laser"));
                }

                if (CONFIGBOOL("Visuals>World>World>Head Height")) {
                    ImGui::ColorEdit4("####Height Height Color",(float*)&CONFIGCOL("Visuals>World>World>Head Height Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
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

                if (ImGui::ColorEdit4("##World Color Modulation", (float*)&CONFIGCOL("Visuals>World>World>World Color Modulation"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel))
                    Features::ColorModulation::updateColorModulation();

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(236, 5));
                ImGui::TextIndent("SkyBox Color"); ImGui::SameLine();
                ImGui::PopStyleVar();

                if (ImGui::ColorEdit4("##SkyBox Color Modulation", (float*)&CONFIGCOL("Visuals>World>World>SkyBox Color Modulation"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel))
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
                ImGui::ColorEdit4("##Fog Color", (float*)&CONFIGCOL("Visuals>World>World>Fog Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
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
                    ImGui::ColorEdit4("##Weapon Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Weapon Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Weapon Box", &CONFIGBOOL("Visuals>World>Items>Weapon Box"));
                ImGui::Checkbox("Weapon Label", &CONFIGBOOL("Visuals>World>Items>Weapon Label"));
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Grenade Box")) {
                    ImGui::ColorEdit4("##Grenade Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Grenade Box Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
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
                    ImGui::ColorEdit4("##Planted C4 Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Planted C4 Box Color"), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Planted C4 Box", &CONFIGBOOL("Visuals>World>Items>Planted C4 Box"));
                ImGui::Checkbox("Planted C4 Label", &CONFIGBOOL("Visuals>World>Items>Planted C4 Label"));
                /*ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Chicken Box")) {
                    ImGui::ColorEdit4("##Chicken Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Chicken Box Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Chicken Box", &CONFIGBOOL("Visuals>World>Items>Chicken Box"));
                ImGui::Checkbox("Chicken Label", &CONFIGBOOL("Visuals>World>Items>Chicken Label"));
                ImGui::Separator();
                if (CONFIGBOOL("Visuals>World>Items>Fish Box")) {
                    ImGui::ColorEdit4("##Fish Box Color", (float*)&CONFIGCOL("Visuals>World>Items>Fish Box Color"), ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Fish Box", &CONFIGBOOL("Visuals>World>Items>Fish Box"));
                ImGui::Checkbox("Fish Label", &CONFIGBOOL("Visuals>World>Items>Fish Label"));*/

                //ImGui::Separator();
                //ImGui::Checkbox("ESP Quite literally everything", &CONFIGBOOL("Visuals>World>Items>ESP Quite literally everything"));

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
