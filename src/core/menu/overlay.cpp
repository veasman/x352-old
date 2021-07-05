#include "../../includes.hpp"
#include <cstring>
#include <unistd.h>
#include <pwd.h>
#include <vector>

// p100 flex ur distro
char distro[32];
void getDistro() {
    static bool gotDistro = false;
    if (!gotDistro) {
        std::ifstream osRelease("/etc/os-release");
        if (osRelease.is_open()) {
            std::string line;
            while (getline(osRelease, line)) {
                if (strstr(line.c_str(), "ID=") == line.c_str()) {
                    if (line.substr(3) == "ubuntu") {
                        memcpy(distro, "shitbuntu", sizeof("shitbuntu")); // pMeme
                    }
                    else {
                        memcpy(distro, line.substr(3).c_str(), 32);
                    }
                }
            }
            osRelease.close();
        }
        gotDistro = true;
    }
}

void Menu::drawOverlay(ImDrawList* drawList) {
    getDistro();
    char hostname[64];
    gethostname(hostname, 64);
    Globals::drawList = drawList;
    int w, h;
    Interfaces::engine->GetScreenSize(w, h);

    if(!CONFIGBOOL("Misc>Misc>Misc>Disable Watermark")) {
        int ping = (Interfaces::engine->IsInGame() && playerResource) ? playerResource->GetPing(Interfaces::engine->GetLocalPlayer()) : 0;
        int framePadding = 20;
        int textPadding = 5;

        char watermarkText[64];
        sprintf(watermarkText, "x352cheats (%s - %s@%s) | %.0f fps | %i ms", distro, getpwuid(getuid())->pw_name, hostname, ImGui::GetIO().Framerate, ping);

        int width = 285;
        int height = 22;

        if (ImGui::GetIO().Framerate >= 100.f)
            width += 6;
        if (ping >= 10.f)
            width += 6;
        if (ping >= 100.f)
            width += 6;

        Globals::drawList->AddRectFilled(ImVec2(w - width - framePadding, framePadding), ImVec2(w - framePadding, framePadding + height), ImColor(25, 25, 25, 255));

        // Border thing
        std::vector<ImColor> colors = {
            ImColor(0, 0, 0),
            ImColor(55, 55, 55),
            ImColor(40, 40, 40),
            ImColor(40, 40, 40),
            ImColor(40, 40, 40),
            ImColor(55, 55, 55),
            ImColor(0, 0, 0),
        };

        for (int i = 0; i < (int)colors.size(); i++) {
            Globals::drawList->AddRect(ImVec2(w - width - framePadding - i, framePadding - i),
                                       ImVec2(w - framePadding + i, framePadding + height + i), colors[i]);
        }

        // Color bar
        ImColor l, m, r, l2, m2, r2;
        l = ImColor(50, 160, 200, 255);
        m = ImColor(180, 80, 180, 255);
        r = ImColor(190, 210, 50, 255);
        l2 = ImColor(30, 90, 110, 255);
        m2 = ImColor(100, 40, 100, 255);
        r2 = ImColor(70, 80, 20, 255);

        Globals::drawList->AddRectFilledMultiColor(ImVec2(w - width - framePadding + 1, framePadding + 1), ImVec2(w - framePadding - (width / 2) , framePadding + 2), l, m, m, l);
        Globals::drawList->AddRectFilledMultiColor(ImVec2(w - framePadding - (width / 2), framePadding + 1), ImVec2(w - framePadding - 1, framePadding + 2), m, r, r, m);

        Globals::drawList->AddRectFilledMultiColor(ImVec2(w - width - framePadding + 1, framePadding + 2), ImVec2(w - framePadding - (width / 2) , framePadding + 3), l2, m2, m2, l2);
        Globals::drawList->AddRectFilledMultiColor(ImVec2(w - framePadding - (width / 2), framePadding + 2), ImVec2(w - framePadding - 1, framePadding + 3), m2, r2, r2, m2);

        Globals::drawList->AddText(ImVec2(w - width - framePadding + textPadding + 1, height + 1 + (textPadding / 2) + 1), ImColor(0, 0, 0, 255), watermarkText);
        Globals::drawList->AddText(ImVec2(w - width - framePadding + textPadding, height + 1 + (textPadding / 2)), ImColor(255, 255, 255, 255), watermarkText);
    }
    /*if (Globals::didEb) {
        Globals::drawList->AddText(ImVec2((w / 2) + 1, (h / 2) + 1), ImColor(0, 0, 0), "EB");
        Globals::drawList->AddText(ImVec2(w / 2 , h / 2), ImColor(255, 255, 255), "EB");
    }*/

    Features::ESP::draw();
    Features::RecoilCrosshair::draw();
    Features::Spectators::draw();
    Features::PlayerList::draw();
    Features::FlappyBird::draw();
    Features::Notifications::draw();
    Features::Hitmarkers::draw();
}
