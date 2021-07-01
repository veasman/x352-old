#include "features.hpp"
#include "../../includes.hpp"
#include <array>
#include <sstream>

static bool getBox(Entity* entity, int& x, int& y, int& x2, int& y2) {
	Vector vOrigin, min, max;
	Vector flb, brt, blb, frt, frb, brb, blt, flt; // think of these as Front-Left-Bottom/Front-Left-Top... Etc.

	vOrigin = entity->origin();
	min = entity->collideable().OBBMins() + vOrigin;
	max = entity->collideable().OBBMaxs() + vOrigin;

	Vector points[] = { Vector( min.x, min.y, min.z ),
						Vector( min.x, max.y, min.z ),
						Vector( max.x, max.y, min.z ),
						Vector( max.x, min.y, min.z ),
						Vector( max.x, max.y, max.z ),
						Vector( min.x, max.y, max.z ),
						Vector( min.x, min.y, max.z ),
						Vector( max.x, min.y, max.z ) };

	// Get screen positions
	if ( !worldToScreen( points[3], flb ) || !worldToScreen( points[5], brt )
		 || !worldToScreen( points[0], blb ) || !worldToScreen( points[4], frt )
		 || !worldToScreen( points[2], frb ) || !worldToScreen( points[1], brb )
		 || !worldToScreen( points[6], blt ) || !worldToScreen( points[7], flt ) )
		return false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for ( int i = 1; i < 8; i++ ) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	x = (int)left;
	y = (int)top;
	x2 = (int)right;
	y2 = (int)bottom;

	return true;
}

void outlinedText(ImVec2 pos, ImColor color, char* text) {
    Globals::drawList->AddText(ImVec2(pos.x-1, pos.y), ImColor(0, 0, 0, 255), text);
    Globals::drawList->AddText(ImVec2(pos.x+1, pos.y), ImColor(0, 0, 0, 255), text);
    Globals::drawList->AddText(ImVec2(pos.x, pos.y-1), ImColor(0, 0, 0, 255), text);
    Globals::drawList->AddText(ImVec2(pos.x, pos.y+1), ImColor(0, 0, 0, 255), text);
    Globals::drawList->AddText(ImVec2(pos.x, pos.y), color, text);

}

void drawBox(int x, int y, int x2, int y2, bool drawBox, ImColor color, char* topText, char* rightText, int health = -1, bool dynamicHealthColor = false, ImColor defaultHealthBarColor = ImColor(0, 240, 0, 255)) {
    if (drawBox) {
        Globals::drawList->AddRect(ImVec2(x, y), ImVec2(x2, y2), color);
        Globals::drawList->AddRect(ImVec2(x-1, y-1), ImVec2(x2+1, y2+1), ImColor(0, 0, 0, 255));
        Globals::drawList->AddRect(ImVec2(x+1, y+1), ImVec2(x2-1, y2-1), ImColor(0, 0, 0, 255));
    }

    if (health != -1) {
        //border color
        Globals::drawList->AddRectFilled(ImVec2(x - 6, y2 - (((float) health / 100.f) * (y2 - y)) - 1),
                                         ImVec2(x - 2, y2 + 1), ImColor(0, 0, 0, 255));
        //bar color
        ImColor healthBarColor = defaultHealthBarColor;
        if (dynamicHealthColor) {
            ImGui::ColorConvertHSVtoRGB(((float)health-20.f)/255.f, 1.f, 1.f, healthBarColor.Value.x, healthBarColor.Value.y, healthBarColor.Value.z);
        }
        Globals::drawList->AddRectFilled(ImVec2(x - 5, y2 - (((float) health / 100.f) * (y2 - y))),ImVec2(x - 3, y2), healthBarColor);
    }
    outlinedText(ImVec2(x2+1, y), ImColor(255, 255, 255, 255), rightText);
    outlinedText(ImVec2(x+((x2-x)/2)-(ImGui::CalcTextSize(topText).x/2), y-(ImGui::CalcTextSize(topText).y)), ImColor(255, 255, 255, 255), topText);
}

void drawSkeleton(Player* p, ImColor color) {
    studiohdr_t* model = Interfaces::modelInfo->GetStudioModel(p->model());
    if (model) {
        matrix3x4_t boneMatrix[128];
        if (p->getHitboxBones(boneMatrix)) {
            for (int i = 0; i < model->numbones; i++) {
                mstudiobone_t* bone = model->pBone(i);
                if (bone && (bone->flags & BONE_USED_BY_HITBOX) && bone->parent != -1) {
                    Vector screenBonePos, screenParentBonePos;
                    if (worldToScreen(Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]), screenBonePos) &&
                        worldToScreen(Vector(boneMatrix[bone->parent][0][3], boneMatrix[bone->parent][1][3], boneMatrix[bone->parent][2][3]), screenParentBonePos)) {
                        Globals::drawList->AddLine(ImVec2{screenBonePos.x, screenBonePos.y}, ImVec2{screenParentBonePos.x, screenParentBonePos.y}, color);
                    }
                }
            }
        }
    }
}

void drawForwardTrack(Player* p) {
    matrix3x4_t boneMatrix[128];
    if (p->getAnythingBones(boneMatrix)) {
        Vector targetEyePos = Vector(boneMatrix[8][0][3], boneMatrix[8][1][3], boneMatrix[8][2][3]); // 8 is headbone in bonematrix
        targetEyePos+=(p->velocity()/64)*3;
        Vector screenFtrackPos;
        if (worldToScreen(targetEyePos, screenFtrackPos)) {
            Globals::drawList->AddCircleFilled(ImVec2(screenFtrackPos.x, screenFtrackPos.y), 3, ImColor(0, 0, 0, 100));
            Globals::drawList->AddCircleFilled(ImVec2(screenFtrackPos.x, screenFtrackPos.y), 3, ImColor(200, 200, 200, 100));
        }
    }
}

void drawPlayer(Player* p) {
    if (!p->dormant()) {
        if (p->health() > 0) {
            int x, y, x2, y2;
            if (getBox(p, x, y, x2, y2)) {
                player_info_t info;
                Interfaces::engine->GetPlayerInfo(p->index(), &info);

                if (p->isEnemy()) {

                    if (CONFIGBOOL("Visuals>Players>Enemies>Vis Check") ? (Globals::localPlayer->health() > 0 ? p->visible() : true) : true) {
                        if (CONFIGBOOL("Visuals>Players>Enemies>Only When Dead") ? (Globals::localPlayer->health() == 0) : true) {
                            std::stringstream rightText;
                            if (CONFIGBOOL("Visuals>Players>Enemies>Health"))
                                rightText << p->health() << "hp\n";
                            if (CONFIGBOOL("Visuals>Players>Enemies>Money"))
                                rightText << "$" << p->money() << "\n";

                            if (CONFIGBOOL("Visuals>Players>Enemies>Armor"))
                                rightText << (p->helmet() ? "H" : "") << (p->armor() ? "K" : "") << "\n";
                            if (CONFIGBOOL("Visuals>Players>Enemies>Flashed") && p->flashDuration() > 3) //This value is quite strange
                                rightText << "Flashed\n"; // TODO: Fully refactor

                            if (CONFIGBOOL("Visuals>Players>Enemies>Weapon")) {
                                Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)p->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
                                if (weapon) {
                                    try {
                                        rightText << itemIndexMap.at(weapon->itemIndex()) << "\n";
                                    }
                                    catch(const std::exception & e) {
                                        //Log::log(WARN, "itemDefinitionIndex %d not found!", ((Weapon*)ent)->itemIndex());
                                    }
                                }
                            }

                            drawBox(x, y, x2, y2, CONFIGBOOL("Visuals>Players>Enemies>Box"),
                                        CONFIGCOL("Visuals>Players>Enemies>Box Color"), CONFIGBOOL("Visuals>Players>Enemies>Name") ? info.name : (char*)"",
                                        (char*)rightText.str().c_str(), CONFIGBOOL("Visuals>Players>Enemies>Health Bar") ? p->health() : -1, CONFIGBOOL("Visuals>Players>Enemies>Dynamic Color"),
                                        CONFIGCOL("Visuals>Players>Enemies>Health Bar Color"));

                            if (CONFIGBOOL("Visuals>Players>Enemies>Skeleton"))
                                drawSkeleton(p, CONFIGCOL("Visuals>Players>Enemies>Skeleton Color"));

                            if (CONFIGBOOL("Visuals>Players>Enemies>Forwardtrack Dots"))
                                drawForwardTrack(p);
                        }
                    }
                }
                else if (!p->isEnemy() &&
                        ((Globals::localPlayer->health() == 0 && CONFIGBOOL("Visuals>Players>Teammates>Only When Dead")) || !CONFIGBOOL("Visuals>Players>Teammates>Only When Dead"))) {
                    std::stringstream rightText;
                    if (CONFIGBOOL("Visuals>Players>Teammates>Health"))
                        rightText << p->health() << "hp\n";
                    if (CONFIGBOOL("Visuals>Players>Teammates>Money"))
                        rightText << "$" << p->money() << "\n";

                    if (CONFIGBOOL("Visuals>Players>Teammates>Armor"))
                        rightText << (p->helmet() ? "H" : "") << (p->armor() ? "K" : "") << "\n";

                    if (CONFIGBOOL("Visuals>Players>Teammates>Weapon")) {
                        Weapon *weapon = (Weapon *) Interfaces::entityList->GetClientEntity((uintptr_t)p->activeWeapon() & 0xFFF); // GetClientEntityFromHandle is being gay
                        if (weapon) {
                            try {
                                rightText << itemIndexMap.at(weapon->itemIndex()) << "\n";
                            }
                            catch(const std::exception & e) {
                                //Log::log(WARN, "itemDefinitionIndex %d not found!", ((Weapon*)ent)->itemIndex());
                            }
                        }
                    }

                    drawBox(x, y, x2, y2, CONFIGBOOL("Visuals>Players>Teammates>Box"),
                                CONFIGCOL("Visuals>Players>Teammates>Box Color"), CONFIGBOOL("Visuals>Players>Teammates>Name") ? info.name : (char*)"",
                                (char*)rightText.str().c_str(), CONFIGBOOL("Visuals>Players>Teammates>Health Bar") ? p->health() : -1, CONFIGBOOL("Visuals>Players>Teammates>Dynamic Color"),
                                CONFIGCOL("Visuals>Players>Teammates>Health Bar Color"));

                    if (CONFIGBOOL("Visuals>Players>Teammates>Skeleton"))
                        drawSkeleton(p, CONFIGCOL("Visuals>Players>Teammates>Skeleton Color"));
                }
            }
        }
    }
}

void drawGenericEnt(Entity* ent, bool box, ImColor color, const char* label) {
    int x, y, x2, y2;
    if (getBox(ent, x, y, x2, y2)) {
        drawBox(x, y, x2, y2, box, color, (char*)label, (char*)"", -1);
    }
}

// TODO: Clean this shit up after you're done
void drawHeadHeight(ImColor color) {
    if (!Globals::localPlayer)
        return;

    if (!CONFIGBOOL("Visuals>World>World>Head Height"))
        return;

    Vector floor;
    Vector headPos;
    Vector headLeft, headRight;
    Vector chestLeft, chestRight;
    if (Menu::CustomWidgets::isKeyDown(CONFIGINT("Visuals>World>World>Head Height Key"))) {
        Trace trace;
        Ray ray;
        TraceFilterWorldAndPropsOnly filter;

        Vector startPos, endPos, forward;
        angleVectors(Globals::viewAngles, forward);

        startPos = Globals::localPlayer->eyePos();
        endPos = startPos + (forward * 8192);

        ray.Init(startPos, endPos);
        Interfaces::trace->TraceRay(ray, MASK_ALL, &filter, &trace);

        Trace tr;
        Ray r;
        Vector start, end;

        start = trace.endpos;
        end = start - Vector(0, 0, 8192);

        r.Init(start, end);
        Interfaces::trace->TraceRay(r, MASK_ALL, &filter, &tr);


        floor = tr.endpos;
        headPos = floor + Vector(0, 0, 64);
        headLeft = headPos - Vector(0, 20, 0);
        headRight = headPos + Vector(0, 20, 0);
        chestLeft = headLeft + Vector(0, 10, -24);
        chestRight = headRight + Vector(0, -10, -24);
    }

    // TODO: What the hell is this.
    Vector scrFloor, scrHead;
    Vector scrHeadLeft, scrHeadRight;
    Vector scrChestLeft, scrChestRight;
    if (worldToScreen(floor, scrFloor) &&
        worldToScreen(headPos, scrHead) &&
        worldToScreen(headLeft, scrHeadLeft) &&
        worldToScreen(headRight, scrHeadRight) &&
        worldToScreen(chestLeft, scrChestLeft) &&
        worldToScreen(chestRight, scrChestRight)) {
        Globals::drawList->AddLine(ImVec2(scrFloor.x, scrFloor.y), ImVec2(scrHead.x, scrHead.y), color);
        Globals::drawList->AddLine(ImVec2(scrHeadLeft.x, scrHeadLeft.y), ImVec2(scrHeadRight.x, scrHeadRight.y), color);
        Globals::drawList->AddLine(ImVec2(scrChestLeft.x, scrChestLeft.y), ImVec2(scrChestRight.x, scrChestRight.y), color);
    }
}

void Features::ESP::draw() {
    if (Interfaces::engine->IsInGame()) {
        drawHeadHeight(CONFIGCOL("Visuals>World>World>Head Height Color"));
        if (Globals::localPlayer) {
            // EB TESTING SHIT
            //AnimState* animState = Globals::localPlayer->animState();

            std::string toDraw;

            // WHAT I KNOW:
            //      - When we hit an EB we are still "in air"
            //      - Our vertical velocity decreases
            //      - Our horizontal velocity changes based on a few factors
            //          - Fall speed before EB
            //          - Horizontal speed before EB
            //      - Since we are still "in air" some anim state stuff doesn't change
            //          - landingAnimationTimeLeftUntilDone
            //          - heightBeforeJump
            //          - onGround (duh)
            //
            // WHAT I CAN DO WITH THIS INFO:
            //      - Detect EB
            //
            // WHAT I CAN'T FIGURE OUT FOR THE LIFE OF ME:
            //      - How do we detect an edge that we might hit
            //
            // WHAT I HAVE CONSIDERED:
            //      - Tracing a circle around the player
            //          - Every edge has a different surrounding area, so no
            //            consistent way of checking if a trace hit and one
            //            didn't to detect a nearby edge

            /*toDraw += "lastAnimUpdateTime: " + std::to_string(animState->lastAnimUpdateTime) + "\n";
            toDraw += "lastAnimUpdateFrame: " + std::to_string(animState->lastAnimUpdateFrame) + "\n";
            toDraw += "eyePitch: " + std::to_string(animState->eyePitch) + "\n";
            toDraw += "yaw: " + std::to_string(animState->yaw) + "\n";
            toDraw += "pitch: " + std::to_string(animState->pitch) + "\n";
            toDraw += "goalFeetYaw: " + std::to_string(animState->goalFeetYaw) + "\n";
            toDraw += "currentFeetYaw: " + std::to_string(animState->currentFeetYaw) + "\n";
            toDraw += "absMovementDirection: " + std::to_string(animState->absMovementDirection) + "\n";
            toDraw += "lastAbsMovementDirection: " + std::to_string(animState->lastAbsMovementDirection) + "\n";
            toDraw += "leanAmount: " + std::to_string(animState->leanAmount) + "\n";
            toDraw += "feetCycle: " + std::to_string(animState->feetCycle) + "\n";
            toDraw += "feetYawRate: " + std::to_string(animState->feetYawRate) + "\n";
            toDraw += "duckProgress: " + std::to_string(animState->duckProgress) + "\n";
            toDraw += "landingAnimationTimeLeftUntilDone: " + std::to_string(animState->landingAnimationTimeLeftUntilDone) + "\n";
            toDraw += "origin.x: " + std::to_string(animState->origin.x) + "\n";
            toDraw += "origin.y: " + std::to_string(animState->origin.y) + "\n";
            toDraw += "origin.z: " + std::to_string(animState->origin.z) + "\n";
            toDraw += "lastOrigin.x: " + std::to_string(animState->lastOrigin.x) + "\n";
            toDraw += "lastOrigin.y: " + std::to_string(animState->lastOrigin.y) + "\n";
            toDraw += "lastOrigin.z: " + std::to_string(animState->lastOrigin.z) + "\n";
            toDraw += "velocityX: " + std::to_string(animState->velocityX) + "\n";
            toDraw += "velocityY: " + std::to_string(animState->velocityY) + "\n";
            toDraw += "currentDirectionX: " + std::to_string(animState->currentDirectionX) + "\n";
            toDraw += "currentDirectionY: " + std::to_string(animState->currentDirectionY) + "\n";
            toDraw += "lastKnownDirectionX: " + std::to_string(animState->lastKnownDirectionX) + "\n";
            toDraw += "lastKnownDirectionY: " + std::to_string(animState->lastKnownDirectionY) + "\n";
            toDraw += "horizontalVelocity: " + std::to_string(animState->horizontalVelocity) + "\n";
            toDraw += "verticalVelocity: " + std::to_string(animState->verticalVelocity) + "\n";
            toDraw += "speed: " + std::to_string(animState->speed) + "\n";
            toDraw += "feetShuffleSpeed: " + std::to_string(animState->feetShuffleSpeed) + "\n";
            toDraw += "feetShuffleSpeed2: " + std::to_string(animState->feetShuffleSpeed2) + "\n";
            toDraw += "timeSinceStartedMoving: " + std::to_string(animState->timeSinceStartedMoving) + "\n";
            toDraw += "timeSinceStoppedMoving: " + std::to_string(animState->timeSinceStoppedMoving) + "\n";
            toDraw += "onGround: " + std::to_string(animState->onGround) + "\n";
            toDraw += "inJumpRecoveryAnim: " + std::to_string(animState->inJumpRecoveryAnim) + "\n";
            toDraw += "heightBeforeJump: " + std::to_string(animState->heightBeforeJump) + "\n";
            toDraw += "runningAccelProgress: " + std::to_string(animState->runningAccelProgress) + "\n";

            Globals::drawList->AddText(ImVec2(330 + 1, 150), ImColor(0, 0, 0), toDraw.c_str());
            Globals::drawList->AddText(ImVec2(330, 150 + 1), ImColor(0, 0, 0), toDraw.c_str());
            Globals::drawList->AddText(ImVec2(330, 150), ImColor(255, 255, 55), toDraw.c_str());*/

            // TRACE TESTING SHIT
            /*Vector origin = Globals::localPlayer->origin();
            Trace trace;
            Ray ray;
            TraceFilter filter;
            filter.pSkip = Globals::localPlayer;

            Vector startpos = origin;
            Vector endpos = startpos;
            endpos.z -= 80;
            Vector mins = Globals::localPlayer->collideable().OBBMins();
            Vector maxs = Globals::localPlayer->collideable().OBBMaxs();

            ray.Init(origin, endpos, mins, maxs);
            Interfaces::trace->TraceRay(ray, MASK_SOLID_BRUSHONLY, &filter, &trace);

            // EDGEBUG IDEA:
            //               - Trace in a circle around the player
            //               - If a trace hits in the back, but not the front
            std::string toPrint;
            toPrint += "plane->dist: " + std::to_string(trace.plane.dist) + "\n";
            toPrint += "fraction: " + std::to_string((trace.fraction)) + "\n";
            toPrint += "contents: " + std::to_string(trace.contents) + "\n";
            toPrint += "dispFlags: " + std::to_string(trace.dispFlags) + "\n";
            toPrint += "allsolid: " + std::to_string(trace.allsolid) + "\n";
            toPrint += "startsolid: " + std::to_string(trace.startsolid) + "\n";
            toPrint += "fractionLeftSolid: " + std::to_string(trace.fractionleftsolid) + "\n";
            //toPrint += "surface->name: " + trace.surface.name + "\n";
            toPrint += "surface->surfaceProps: " + std::to_string(trace.surface.surfaceProps) + "\n";
            toPrint += "surface->flags: " + std::to_string(trace.surface.flags) + "\n";
            toPrint += "hitgroup: " + std::to_string(trace.hitgroup) + "\n";
            toPrint += "physicsBone: "  + std::to_string(trace.physicsbone) + "\n";
            toPrint += "worldSurfaceIndex: " + std::to_string(trace.worldSurfaceIndex) + "\n";
            //toPrint += "hitbox: " + std::to_string(trace.hitbox) + "\n";

            Globals::drawList->AddText(ImVec2(400 + 1, 200 + 1), ImColor(0, 0, 0, 255), toPrint.c_str());
            Globals::drawList->AddText(ImVec2(400, 200), ImColor(255, 255, 255, 255), toPrint.c_str());
            Vector drawPos = trace.endpos;
            Vector screenPos;
            if (worldToScreen(drawPos, screenPos)) {
                Globals::drawList->AddCircleFilled(ImVec2(screenPos.x, screenPos.y), 8, ImColor(255, 55, 255));
                Globals::drawList->AddLine(ImVec2(screenPos.x + 8, screenPos.y), ImVec2(screenPos.x + 28, screenPos.y), ImColor(255, 55, 255));
                Globals::drawList->AddLine(ImVec2(screenPos.x + 28, screenPos.y), ImVec2(screenPos.x + 48, screenPos.y - 20), ImColor(255, 55, 255));
                Globals::drawList->AddText(ImVec2(screenPos.x + 53, screenPos.y - 29), ImColor(0, 0, 0, 255), "trEndPos");
                Globals::drawList->AddText(ImVec2(screenPos.x + 52, screenPos.y - 30), ImColor(255, 255, 255), "trEndPos");
            }*/
        }
        for (auto i : entityDistanceMap) {
            if (Globals::localPlayer) {
                if (i.second != Interfaces::engine->GetLocalPlayer()) {
                    Entity* ent = (Entity*)Interfaces::entityList->GetClientEntity(i.second);
                    if (ent) {
                        ClientClass* clientClass = ent->clientClass();

                        /* Player ESP */
                        if (clientClass->m_ClassID == EClassIds::CCSPlayer) {
                            drawPlayer((Player*)ent);
                            Features::Radar::espPlayerLoop((Player*)ent);
                        }

                        /* Weapon ESP */
                        else if ((clientClass->m_ClassID != EClassIds::CBaseWeaponWorldModel && strstr(clientClass->m_pNetworkName, "Weapon")) || clientClass->m_ClassID == EClassIds::CDEagle || clientClass->m_ClassID == EClassIds::CC4 || clientClass->m_ClassID == EClassIds::CAK47) {
                            if (((Weapon*)ent)->owner() == -1) {
                                try {
                                    drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Weapon Box"), CONFIGCOL("Visuals>World>Items>Weapon Box Color"), CONFIGBOOL("Visuals>World>Items>Weapon Label") ? itemIndexMap.at(((Weapon*)ent)->itemIndex()) : "");
                                }
                                catch(const std::exception & e) {
                                    //Log::log(WARN, "itemDefinitionIndex %d not found!", ((Weapon*)ent)->itemIndex());
                                }
                            }
                        }

                        /* Nade ESP*/
                        else if (clientClass->m_ClassID == EClassIds::CBaseCSGrenadeProjectile || clientClass->m_ClassID == EClassIds::CSmokeGrenadeProjectile || clientClass->m_ClassID == EClassIds::CMolotovProjectile || clientClass->m_ClassID == CDecoyProjectile) {
                            const char* modelName = Interfaces::modelInfo->GetModelName(ent->model());
                            if (modelName) {
                                player_info_t info;
                                Interfaces::engine->GetPlayerInfo((*(int*)((uintptr_t)ent+GETNETVAROFFSET("DT_BaseCombatWeapon", "m_hOwnerEntity"))) & 0xFFF, &info);

                                char label[128] = "";
                                ImColor col(255, 255, 255, 255);

                                if (strstr(modelName, "fraggrenade")) {
                                    snprintf(label, 128, "%s\n%s", CONFIGBOOL("Visuals>World>Items>Grenade Label") ? "HE Grenade" : "", CONFIGBOOL("Visuals>World>Items>Grenade Owners") ? info.name : "");
                                    col = ImColor(0, 86, 0, 255);
                                }
                                else if (strstr(modelName, "flashbang")) {
                                    snprintf(label, 128, "%s\n%s", CONFIGBOOL("Visuals>World>Items>Grenade Label") ? "Flashbang" : "", CONFIGBOOL("Visuals>World>Items>Grenade Owners") ? info.name : "");
                                    col = ImColor(255, 255, 0, 255);
                                }
                                else if (strstr(modelName, "molotov")) {
                                    snprintf(label, 128, "%s\n%s", CONFIGBOOL("Visuals>World>Items>Grenade Label") ? "Molotov" : "", CONFIGBOOL("Visuals>World>Items>Grenade Owners") ? info.name : "");
                                    col = ImColor(255, 0, 0, 255);
                                }
                                else if (strstr(modelName, "incendiarygrenade")) {
                                    snprintf(label, 128, "%s\n%s", CONFIGBOOL("Visuals>World>Items>Grenade Label") ? "Incendiary" : "", CONFIGBOOL("Visuals>World>Items>Grenade Owners") ? info.name : "");
                                    col = ImColor(255, 0, 0, 255);
                                }
                                else if (strstr(modelName, "decoy")) {
                                    snprintf(label, 128, "%s\n%s", CONFIGBOOL("Visuals>World>Items>Grenade Label") ? "Decoy" : "", CONFIGBOOL("Visuals>World>Items>Grenade Owners") ? info.name : "");
                                    col = ImColor(157, 157, 157, 255);
                                }
                                else if (strstr(modelName, "smokegrenade")) {
                                    snprintf(label, 128, "%s\n%s", CONFIGBOOL("Visuals>World>Items>Grenade Label") ? "Smoke" : "", CONFIGBOOL("Visuals>World>Items>Grenade Owners") ? info.name : "");
                                    col = ImColor(157, 157, 157, 255);
                                }
                                drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Grenade Box"), CONFIGBOOL("Visuals>World>Items>Grenade Box Dynamic Color") ? col : CONFIGCOL("Visuals>World>Items>Grenade Box Color"), label);
                            }
                        }


                        /* Planted C4 ESP */
                        else if (clientClass->m_ClassID == EClassIds::CPlantedC4) {
                            float bombTime = ((PlantedC4*)ent)->time() - Interfaces::globals->curtime;
                            if (bombTime >= 0.f) {
                                char label[32] = "";
                                snprintf(label, 32, "Planted C4\n%.1f", bombTime);
                                drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Planted C4 Box"), CONFIGCOL("Visuals>World>Items>Planted C4 Box Color"), CONFIGBOOL("Visuals>World>Items>Planted C4 Label") ? label : "");
                                AutoDefuse::onBombRender((PlantedC4*)ent);
                            }
                        }

                        else if (clientClass->m_ClassID == EClassIds::CEnvTonemapController) {
                            Nightmode::onTonemapController((TonemapController*)ent);
                        }

                        /* Chicken ESP */
                        else if (clientClass->m_ClassID == EClassIds::CChicken) {
                            drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Chicken Box"), CONFIGCOL("Visuals>World>Items>Chicken Box Color"), CONFIGBOOL("Visuals>World>Items>Chicken Label") ? "Chicken" : "");
                        }

                        /* Fish ESP */
                        else if (clientClass->m_ClassID == EClassIds::CFish) {
                            drawGenericEnt(ent, CONFIGBOOL("Visuals>World>Items>Fish Box"), CONFIGCOL("Visuals>World>Items>Fish Box Color"), CONFIGBOOL("Visuals>World>Items>Fish Label") ? "Fish" : "");
                        }

                        else if (clientClass->m_ClassID == EClassIds::CFogController && CONFIGBOOL("Visuals>World>World>Override Fog")) {
                            *((FogController*)ent)->enable_ptr() = true;
                            *((FogController*)ent)->start_ptr() = (float)CONFIGINT("Visuals>World>World>Fog Start");
                            *((FogController*)ent)->end_ptr() = (float)CONFIGINT("Visuals>World>World>Fog End");
                            *((FogController*)ent)->maxDensity_ptr() = ((float)CONFIGINT("Visuals>World>World>Fog Density"))/1000;
                            *((FogController*)ent)->colorPrimary_ptr() = ImGui::ColorConvertFloat4ToU32(CONFIGCOL("Visuals>World>World>Fog Color").Value);
                        }

                        /* Debug ESP Everything*/
                        else if (CONFIGBOOL("Visuals>World>Items>ESP Quite literally everything")) {
                            char label[128] = "";
                            snprintf(label, 128, "%d\n%s", clientClass->m_ClassID, clientClass->m_pNetworkName);
                            drawGenericEnt(ent, true, ImColor(255, 255, 255, 255), label);
                        }
                    }
                }
            }
        }
    }
}

void Features::ESP::frameStageNotify(FrameStage frame) {
    if (frame == FRAME_RENDER_START || frame == FRAME_RENDER_END) {

    static auto blur = Interfaces::convar->FindVar("@panorama_disable_blur");
    blur->SetValue(CONFIGBOOL("Visuals>World>Removals>No Panorama Blur"));

        if (frame == FRAME_RENDER_END) {
            constexpr std::array smokeMaterials {
                "particle/vistasmokev1/vistasmokev1_emods",
                "particle/vistasmokev1/vistasmokev1_emods_impactdust",
                "particle/vistasmokev1/vistasmokev1_fire",
                "particle/vistasmokev1/vistasmokev1_smokegrenade"
            };

            for (const auto mat : smokeMaterials) {
                const auto material = Interfaces::materialSystem->FindMaterial(mat, nullptr);
                material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, CONFIGINT("Visuals>World>Removals>Smoke") == 1);
                material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, CONFIGINT("Visuals>World>Removals>Smoke") == 2);
            }
        }
    }
}
