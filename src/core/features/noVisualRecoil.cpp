#include "features.hpp"
#include "../../sdk/sdk.hpp"

 void Features::NoVisualRecoil::frameStageNotify(FrameStage frame) {
    if (frame == FRAME_RENDER_START && Globals::localPlayer &&
            (CONFIGBOOL("Visuals>World>Removals>No Aim Punch") || CONFIGBOOL("Visuals>World>Removals>No View Punch"))) {
        Globals::localPlayer->aimPunch() = CONFIGBOOL("Visuals>World>Removals>No Aim Punch") ? QAngle(0, 0, 0) : Globals::localPlayer->aimPunch();
        Globals::localPlayer->viewPunch() = CONFIGBOOL("Visuals>World>Removals>No View Punch") ? QAngle(0, 0, 0) : Globals::localPlayer->viewPunch();
    }
}
