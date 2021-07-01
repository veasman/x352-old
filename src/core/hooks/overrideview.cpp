#include "../../includes.hpp"
#include "hooks.hpp"
#include "../features/features.hpp"


void Hooks::OverrideView::hook(void* thisptr, ViewSetup* setup) {
    if (Interfaces::engine->IsInGame() && Globals::localPlayer && Globals::localPlayer->health() > 0 && !Globals::localPlayer->scoped()) {

        bool doTP = true;

        if (Menu::CustomWidgets::isKeyDown(CONFIGINT("Visuals>World>World>Third Person Distance"))) {
            doTP = !doTP;
        }

        setup->fov = CONFIGINT("Visuals>World>World>FOV");

        if (doTP) {
            // Third Person from Fuzion
            QAngle viewAngles;
            Interfaces::engine->GetViewAngles(viewAngles);
            Trace tr;
            Ray traceRay;
            Vector eyePos = Globals::localPlayer->eyePos();

            int tpDist = CONFIGINT("Visuals>World>World>Third Person Distance");
            Vector camOff = Vector(cos(DEG2RAD(viewAngles.y)) * tpDist,sin(DEG2RAD(viewAngles.y)) * tpDist,sin(DEG2RAD(-viewAngles.x)) * tpDist);

            traceRay.Init(eyePos, (eyePos - camOff));
            TraceFilter traceFilter;
            traceFilter.pSkip = Globals::localPlayer;
            Interfaces::trace->TraceRay(traceRay, 0x1, &traceFilter, &tr);

            if (CONFIGBOOL("Visuals>World>World>Third Person"))
            Interfaces::input->m_vecCameraOffset = Vector(viewAngles.x, viewAngles.y, tpDist * ((tr.fraction < 1.0f) ? tr.fraction : 1.0f) );
            Interfaces::input->m_fCameraInThirdPerson = CONFIGBOOL("Visuals>World>World>Third Person");


            Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t) Globals::localPlayer->activeWeapon() & 0xFFF);
            if(weapon) {
                if (weapon->itemIndex() == ItemIndex::WEAPON_DECOY || weapon->itemIndex() == ItemIndex::WEAPON_HEGRENADE || weapon->itemIndex() == ItemIndex::WEAPON_FLASHBANG || weapon->itemIndex() == ItemIndex::WEAPON_SMOKEGRENADE || weapon->itemIndex() == ItemIndex::WEAPON_MOLOTOV || weapon->itemIndex() == ItemIndex::WEAPON_INCGRENADE) {
                    Interfaces::input->m_fCameraInThirdPerson = false;
                }
            }
        }
    }
    Globals::FOV = setup->fov;
    original(thisptr, setup);
}
