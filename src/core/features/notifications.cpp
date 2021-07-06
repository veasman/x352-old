#include "features.hpp"
#include "../../includes.hpp"
#include <cstdio>
#include <vector>

struct Notification {
    float openTime;
    ImColor color;
    char text[128];
};
std::vector<Notification> notifications = {};

void Features::Notifications::draw() {
    int yOffset = 0;
    int padding = 8;
    for (Notification &notif : notifications) {
        float slideValue = Interfaces::globals->realtime - (notif.openTime + 8.f);
        float colorSlideValue = Interfaces::globals->realtime - (notif.openTime + 8.2f);

        ImColor menuColor = ImGui::GetStyle().Colors[ImGuiCol_MenuCol];

        notif.color.Value.w = 1.f - (colorSlideValue * 3.f);

        ImVec2 textSize = ImGui::CalcTextSize(notif.text);
        ImVec2 notifPos = ImVec2(slideValue > 0.f ? 0 - slideValue * 800 : 0, yOffset);
        ImVec2 colorPos = ImVec2(colorSlideValue > 0.f ? 0 - colorSlideValue * 820 : 0, yOffset);
        ImVec2 textPos = ImVec2(notifPos.x + padding, notifPos.y + padding);
        ImVec2 boxSize = ImVec2(textSize.x + (padding * 2), textSize.y + (padding * 2));

        Globals::drawList->AddRectFilled(notifPos, ImVec2(colorPos.x + boxSize.x + padding, colorPos.y + boxSize.y), menuColor);
        Globals::drawList->AddRectFilled(notifPos, ImVec2(notifPos.x + boxSize.x, notifPos.y + boxSize.y), ImColor(17, 17, 17));

        Globals::drawList->AddText(textPos, notif.color, notif.text);

        yOffset+=boxSize.y;

        if (notif.color.Value.w < 0.f) {
            notifications.erase(notifications.begin());
        }
    }
    while(notifications.size() > 8) {
        notifications.erase(notifications.begin());
    }
}

void Features::Notifications::addNotification(ImColor color, const char* fmt, ...) {
    Notification notif;
    notif.openTime = Interfaces::globals->realtime;
    notif.color = color;

    va_list args;
    va_start(args, fmt);
    vsnprintf(notif.text, sizeof(Notification::text), fmt, args);
    va_end(args);

    notifications.push_back(notif);
}
