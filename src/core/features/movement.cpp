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
            Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Jump Bug Key")) &&
            Globals::localPlayer &&
            Globals::localPlayer->moveType() != MOVETYPE_LADDER &&
            Globals::localPlayer->moveType() != MOVETYPE_NOCLIP) {
        float max_radias = M_PI * 2;
		float step = max_radias / 128;
		float xThick = 23;
        if (Globals::localPlayer->flags() & FL_ONGROUND) {
            bool unduck = cmd->buttons &= ~IN_DUCK;
            if (unduck) {
                cmd->buttons &= ~IN_DUCK;
                cmd->buttons |= IN_JUMP;
                unduck = false;
            }
            Vector pos = Globals::localPlayer->origin();
            for (float a = 0.f; a < max_radias; a += step) {
                Vector pt;
                pt.x = (xThick * cos(a)) + pos.x;
                pt.y = (xThick * sin(a)) + pos.y;
                pt.z = pos.z;


                Vector pt2 = pt;
                pt2.z -= 8192;

                Trace trace;

                Ray ray;
                ray.Init(pt, pt2);

                TraceFilter flt;
                flt.pSkip = Globals::localPlayer;
                Interfaces::trace->TraceRay(ray, MASK_PLAYERSOLID, &flt, &trace);

                if (trace.fraction != 1.f && trace.fraction != 0.f) {
                    cmd->buttons |= IN_DUCK;
                    cmd->buttons &= ~IN_JUMP;
                    unduck = true;
                }
            }
            for (float a = 0.f; a < max_radias; a += step) {
                Vector pt;
                pt.x = ((xThick - 2.f) * cos(a)) + pos.x;
                pt.y = ((xThick - 2.f) * sin(a)) + pos.y;
                pt.z = pos.z;

                Vector pt2 = pt;
                pt2.z -= 8192;

                Trace trace;

                Ray ray;
                ray.Init(pt, pt2);

                TraceFilter flt;
                flt.pSkip = Globals::localPlayer;
                Interfaces::trace->TraceRay(ray, MASK_PLAYERSOLID, &flt, &trace);

                if (trace.fraction != 1.f && trace.fraction != 0.f) {
                    cmd->buttons |= IN_DUCK;
                    cmd->buttons &= ~IN_JUMP;
                    unduck = true;
                }
            }
            for (float a = 0.f; a < max_radias; a += step) {
                Vector pt;
                pt.x = ((xThick - 20.f) * cos(a)) + pos.x;
                pt.y = ((xThick - 20.f) * sin(a)) + pos.y;
                pt.z = pos.z;

                Vector pt2 = pt;
                pt2.z -= 8192;

                Trace trace;

                Ray ray;
                ray.Init(pt, pt2);

                TraceFilter flt;
                flt.pSkip = Globals::localPlayer;
                Interfaces::trace->TraceRay(ray, MASK_PLAYERSOLID, &flt, &trace);

                if (trace.fraction != 1.f && trace.fraction != 0.f) {
                    cmd->buttons |= IN_DUCK;
                    cmd->buttons &= ~IN_JUMP;
                    unduck = true;
                }
            }
        }
    }
}

void Features::Movement::jumpShot(CUserCmd* cmd) {
    if (CONFIGBOOL("Misc>Misc>Movement>Jump Shot") &&
        Menu::CustomWidgets::isKeyDown(CONFIGINT("Misc>Misc>Movement>Jump Shot Key")) &&
        Globals::localPlayer->moveType() != MOVETYPE_LADDER &&
        Globals::localPlayer->moveType() != MOVETYPE_NOCLIP) {
        AnimState* anim = Globals::localPlayer->animState();
        if (anim->verticalVelocity <= 0.f && !anim->onGround)
            cmd->buttons |= IN_ATTACK;
        }
}
