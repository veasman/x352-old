#include "../menu.hpp"
#include <filesystem>
#include "../config.hpp"

void Menu::drawMiscTab() {
    if (ImGui::BeginTabBar("##miscTabs")) {
        if (ImGui::BeginTabItem("Misc")) {
            ImGui::Columns(3, NULL, false);
            ImGui::SetColumnWidth(-1, ImGui::GetWindowContentRegionWidth() * 0.33);

            ImGui::BeginChild("Config", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.318, 0), true); {
                ImGui::Text("Config");
                ImGui::Separator();

                // TODO: Make these look better
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
                ImGui::ListBoxHeader("##configlist-lbox", ImVec2(0, 377));
                for (std::string file : Config::cfgFiles) {
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    if (ImGui::Button(file.c_str(), ImVec2(ImGui::GetWindowContentRegionWidth(), 20))) {
                        strcpy(Config::configFileName, file.c_str());
                    }
                }
                //ImGui::PopStyleVar();
                ImGui::ListBoxFooter();

                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::InputText("##configfile-tbox", Config::configFileName, IM_ARRAYSIZE(Config::configFileName));
                if (ImGui::Button("Save", ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
                    Config::save();
                };
                if (ImGui::Button("Load", ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
                    Config::load();
                    FULLUPDATE();
                };
                if (ImGui::Button("Remove", ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
                    Config::remove();
                };
                /*if (ImGui::Button("Reset", ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
                    Config::reset();
                };*/
                ImGui::EndChild();
            }

            ImGui::NextColumn();
            ImGui::SetColumnWidth(-1, ImGui::GetWindowContentRegionWidth() * 0.33);

            ImGui::BeginChild("Misc", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.318, ImGui::GetWindowHeight() * 0.60f), true); {
                ImGui::Text("Misc");
                ImGui::Separator();

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(100, 5));
                ImGui::TextIndent("Menu Color"); ImGui::SameLine();
                ImGui::PopStyleVar();
                ImGui::ColorEdit4("##Menu Color", (float*)&CONFIGCOL("Misc>Misc>Misc>Menu Color"), ImGuiColorEditFlags_NoInputs);

                ImGui::Checkbox("Disable Watermark", &CONFIGBOOL("Misc>Misc>Misc>Disable Watermark"));
                ImGui::Checkbox("Square Radar", &CONFIGBOOL("Misc>Misc>Misc>Force square radar"));
                ImGui::Checkbox("Rank Revealer", &CONFIGBOOL("Misc>Misc>Misc>Rank Revealer"));

                ImGui::Checkbox("Spectators", &CONFIGBOOL("Misc>Misc>Misc>Spectators"));
                ImGui::Checkbox("Player List", &CONFIGBOOL("Misc>Misc>Misc>Player List"));
                if (CONFIGBOOL("Misc>Misc>Misc>Player List")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Only When Menu Open", &CONFIGBOOL("Misc>Misc>Misc>Player List Only When Menu Open"));
                }
                ImGui::Checkbox("Flappy Birb", &CONFIGBOOL("Misc>Misc>Misc>Flappy Birb"));
                ImGui::Checkbox("Auto Accept", &CONFIGBOOL("Misc>Misc>Misc>Auto Accept"));
                ImGui::Checkbox("Auto Defuse", &CONFIGBOOL("Misc>Misc>Misc>Auto Defuse"));
                if (CONFIGBOOL("Misc>Misc>Misc>Auto Defuse")) {
                    ImGui::SameLine();
                    ImGui::Checkbox("Latest Defuse", &CONFIGBOOL("Misc>Misc>Misc>Latest Defuse"));
                }
                ImGui::Checkbox("Chat Filter Bypass", &CONFIGBOOL("Misc>Misc>Misc>Chat Filter Bypass"));
                if (CONFIGBOOL("Misc>Misc>Misc>Use Spam")) {
                    static bool toggled = false;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Misc>Misc>Misc>Use Spam Key"), &toggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Use Spam", &CONFIGBOOL("Misc>Misc>Misc>Use Spam"));
                ImGui::Checkbox("Disable Setting Cvars", &CONFIGBOOL("Misc>Misc>Misc>Disable Setting Cvars"));

                ImGui::EndChild();
            }

            ImGui::BeginChild("Hitmarkers", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.318, 0), true); {
                ImGui::Text("Hitmarkers");
                ImGui::Separator();
                ImGui::Checkbox("Hitlogs", &CONFIGBOOL("Misc>Misc>Hitmarkers>Hitlogs"));
                ImGui::Checkbox("Hitmarkers", &CONFIGBOOL("Misc>Misc>Hitmarkers>Hitmarkers"));
                ImGui::Checkbox("Hitsound", &CONFIGBOOL("Misc>Misc>Hitmarkers>Hitsound"));
                ImGui::Checkbox("Damage Markers", &CONFIGBOOL("Misc>Misc>Hitmarkers>Damage Markers"));
                ImGui::EndChild();
            }

            ImGui::NextColumn();

            ImGui::BeginChild("Clantag", ImVec2(0, ImGui::GetWindowHeight() * 0.28f), true); {
                ImGui::Text("Clantag");
                ImGui::Separator();
                //ImGui::TextIndent("Clantag");
                ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                ImGui::InputTextIndent("##clantag-tbox", clantag, IM_ARRAYSIZE(clantag));
                ImGui::Checkbox("Clantag", &CONFIGBOOL("Misc>Misc>Clantag>Clantag"));
                ImGui::Checkbox("Marquee", &CONFIGBOOL("Misc>Misc>Clantag>Clantag Marquee"));
                //ImGui::Checkbox("Bee Movie Clantag", &CONFIGBOOL("Misc>Misc>Clantag>Bee Movie Clantag"));
                ImGui::EndChild();
            }

            ImGui::BeginChild("Movement", ImVec2(0, 0), true); {
                ImGui::Text("Movement");
                ImGui::Separator();
                ImGui::Checkbox("Auto Hop", &CONFIGBOOL("Misc>Misc>Movement>Auto Hop"));
                ImGui::Checkbox("Humanised Bhop", &CONFIGBOOL("Misc>Misc>Movement>Humanised Bhop"));
                if (CONFIGBOOL("Misc>Misc>Movement>Humanised Bhop")) {
                    ImGui::TextIndent("Bhop Hitchance");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##Bhop Hitchance", &CONFIGINT("Misc>Misc>Movement>Bhop Hitchance"), 0, 100);
                    ImGui::TextIndent("Bhop Max Misses");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##Bhop Max Misses", &CONFIGINT("Misc>Misc>Movement>Bhop Max Misses"), 0, 16);
                    ImGui::TextIndent("Bhop Max Hops Hit");
                    ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
                    ImGui::SliderInt("##Bhop Max Hops Hit", &CONFIGINT("Misc>Misc>Movement>Bhop Max Hops Hit"), 0, 16);
                }
                ImGui::Checkbox("Auto Strafe", &CONFIGBOOL("Misc>Misc>Movement>Auto Strafe"));
                if (CONFIGBOOL("Misc>Misc>Movement>Edge Jump")) {
                    static bool toggled = false;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Misc>Misc>Movement>Edge Jump Key"), &toggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Edge Jump", &CONFIGBOOL("Misc>Misc>Movement>Edge Jump"));
                if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug")) {
                    static bool toggled = false;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Misc>Misc>Movement>Jump Bug Key"), &toggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Jump Bug", &CONFIGBOOL("Misc>Misc>Movement>Jump Bug"));
                if (CONFIGBOOL("Misc>Misc>Movement>Edge Bug")) {
                    static bool toggled = false;
                    Menu::CustomWidgets::drawKeyBinder("Key", &CONFIGINT("Misc>Misc>Movement>Edge Bug Key"), &toggled);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Edge Bug", &CONFIGBOOL("Misc>Misc>Movement>Edge Bug"));
                ImGui::Checkbox("Fast Duck", &CONFIGBOOL("Misc>Misc>Movement>Fast Duck"));
                ImGui::SameLine();
                ImGui::TextDisabled("?");
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("May cause untrusted, use at own risk!");
                ImGui::EndChild();
            }
            ImGui::Columns(1);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Skins")) {
            static ItemIndex curWeaponSelected = ItemIndex::WEAPON_AK47;
            if (ImGui::BeginCombo("Weapon", itemIndexMap.at(curWeaponSelected))) {
                for (auto item : itemIndexMap) {
                    if (item.first != ItemIndex::INVALID) {
                        ImGui::PushID(item.second);
                        const bool is_selected = (itemIndexMap.at(curWeaponSelected) == item.second);
                        if (ImGui::Selectable(item.second, is_selected)) {
                            curWeaponSelected = item.first;
                            FULLUPDATE();
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::EndCombo();
            }
            if (curWeaponSelected != ItemIndex::INVALID) {
                char* buf = new char[256];
                snprintf(buf, 256, "Misc>Skins>Skins>%s>PaintKit", itemIndexMap.at(curWeaponSelected));
                if (ImGui::DragInt("PaintKit", &CONFIGINT(buf))) {
                    FULLUPDATE();
                }

                char* buf2 = new char[256];
                snprintf(buf2, 256, "Misc>Skins>Skins>%s>Wear", itemIndexMap.at(curWeaponSelected));
                if (ImGui::SliderInt("Wear", &CONFIGINT(buf2), 0, 100)) {
                    FULLUPDATE();
                }

                char* buf3 = new char[256];
                snprintf(buf3, 256, "Misc>Skins>Skins>%s>StatTrack", itemIndexMap.at(curWeaponSelected));
                if (ImGui::DragInt("StatTrack", &CONFIGINT(buf3))) {
                    FULLUPDATE();
                }
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}
