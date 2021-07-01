#include "features.hpp"
#include "../../includes.hpp"

// TODO: Clean the functions up

// TODO: Make autostrafe
void Features::Movement::autoStrafe(CUserCmd* cmd) {}

void Features::Movement::storeFlags(CUserCmd* cmd) {
    if (Globals::localPlayer) {
        storedFlags = Globals::localPlayer->flags();
        AnimState* anim = Globals::localPlayer->animState();
        storedVel = anim->verticalVelocity;
    }
}

// TODO: Do proper edge detection, and speed adjustment
void Features::Movement::edgeBug(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Edge Bug") &&
        Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Edge Bug Key")) &&
        Globals::localPlayer->moveType() != MOVETYPE_LADDER &&
        Globals::localPlayer->moveType() != MOVETYPE_NOCLIP &&
        !(storedFlags & FL_ONGROUND) && // Predicting we are going to hit the ground
        Globals::localPlayer->flags() & FL_ONGROUND) {
        cmd->buttons |= IN_DUCK;
        /*int stage = 0;
        float oldVel = 0.f;
        float cooldown = 0.f;
        int numEB = 0;
        int numConsecEB = 0;
        Vector vel = Globals::localPlayer->velocity();
        AnimState* anim = Globals::localPlayer->animState();

        if (!anim->onGround) {
            stage = 1;
            if (vel.z < 1.f && oldVel < vel.z) {
                stage = 2;
                if (anim->horizontalVelocity > 10.f) {
                    stage = 3;
                    if (Interfaces::globals->curtime > cooldown) {
                        stage = 4;
                        cooldown = Interfaces::globals->curtime + 0.5f;
                        numEB += 1;
                        Globals::didEb = true;
                    }
                }
            }
        } else {
            // Reset counter for consecutive EB
            numConsecEB = 0;
        }

        oldVel = vel.z;*/
    }
}

void Features::Movement::edgeJump(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Edge Jump") &&
            Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Edge Jump Key")) &&
            Globals::localPlayer &&
            Globals::localPlayer->moveType() != MOVETYPE_LADDER &&
            Globals::localPlayer->moveType() != MOVETYPE_NOCLIP &&
            storedFlags & FL_ONGROUND && // Predicting we are going to be in the air
            !(Globals::localPlayer->flags() & FL_ONGROUND))
        cmd->buttons |= IN_JUMP;
}

void Features::Movement::jumpBug(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Jump Bug") &&
        Interfaces::inputSystem->IsButtonDown(KEY_SPACE) &&
        Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Jump Bug Key")) &&
        Globals::localPlayer->moveType() != MOVETYPE_LADDER &&
        Globals::localPlayer->moveType() != MOVETYPE_NOCLIP &&
        (Globals::localPlayer->flags() & FL_ONGROUND || Globals::localPlayer->flags() & FL_PARTIALGROUND) && // Predicting we are going to hit the ground
        !(storedFlags & FL_ONGROUND || storedFlags & FL_PARTIALGROUND)) {
        cmd->buttons |= IN_DUCK;
        cmd->buttons &= ~IN_JUMP;
    }
}
