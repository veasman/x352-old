#include "features.hpp"
#include "../../includes.hpp"
#include <sstream>

void Features::VelocityText::draw() {
    char velText[64];
    float jumpVel = 0;
    float lastVel = 0;
    ImColor textColor;
    int screenX, screenY;
    Interfaces::engine->GetScreenSize(screenX, screenY);
    if (CONFIGBOOL("Visuals>Players>LocalPlayer>Velocity Text") && Globals::localPlayer && Globals::localPlayer->health() > 0) {
        int vel = Globals::localPlayer->velocity().Length2D();
        if (lastVel != vel) {
            // Green if increase in speed, red if decrease in speed
            textColor = vel > lastVel ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255);
        } else if (lastVel == vel) {
            // Yellow is speed has not changed
            textColor = ImColor(255, 255, 0, 255);
        }
        static bool drawJumpVel = true;
        std::stringstream velStream;
        static float time = Interfaces::globals->curtime;
        if (!(Globals::localPlayer->flags() & FL_ONGROUND)) {
            drawJumpVel = true;
        }
        if (Globals::localPlayer->flags() & FL_ONGROUND) {
            jumpVel = vel;
            time += 0.5f;
            drawJumpVel = Interfaces::globals->curtime >= time;
        }
        velStream << ceilf(vel);
        if (drawJumpVel)
            velStream << " (" << ceilf(jumpVel) << ")";

        sprintf(velText, "%s", velStream.str().c_str());
        Globals::drawList->AddText(ImVec2(screenX / 2, screenY * 0.9), textColor, velText);
    }
}
