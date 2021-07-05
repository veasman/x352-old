#include "features.hpp"

void Features::AutoAccept::emitSound(const char* pSoundEntry) {
    /* TODO: move to panorama event dispatching in future */
    if (CONFIGBOOL("Misc>Misc>Misc>Auto Accept") && Offsets::setPlayerReady && strcmp(pSoundEntry, "UIPanorama.popup_accept_match_beep") == 0) {
        Features::Notifications::addNotification(ImColor(0, 255, 0), "[x352] Found game, Accepting...");
        system("notify-send \"x352\" \"Found game!\""); //p
        Offsets::setPlayerReady("");
    }
}
