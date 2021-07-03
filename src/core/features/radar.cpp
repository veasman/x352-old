#include "features.hpp"

void Features::Radar::espPlayerLoop(Player* p) {
    if (!p->dormant() && CONFIGBOOL("Visuals>Players>Radar") && ((Globals::localPlayer->health() == 0 && CONFIGBOOL("Visuals>Players>Only When Dead")) || !CONFIGBOOL("Visuals>Players>Only When Dead"))) {
        *p->spotted_ptr() = true;
    }
}
