#include "../../includes.hpp"
#include "../../sdk/classes/keyvalues.hpp"
#include "features.hpp"
#include <cstring>

IMaterial* shadedMaterial;
IMaterial* flatMaterial;
IMaterial* glowMaterial;
IMaterial* plasticMaterial;
IMaterial* multicolorMaterial;

IMaterial* createMaterial(const char* materialName, const char* materialType, const char* material) {
	KeyValues* keyValues = new KeyValues(materialName);

	Offsets::initKeyValues(keyValues, materialType);
	Offsets::loadFromBuffer(keyValues, materialName, material, nullptr, nullptr, nullptr);

	return Interfaces::materialSystem->CreateMaterial(materialName, keyValues);
}

void createMaterials() {
    static bool init;
    if (!init) {
        shadedMaterial = Interfaces::materialSystem->FindMaterial("debug/debugambientcube", 0);
        flatMaterial = Interfaces::materialSystem->FindMaterial("debug/debugdrawflat", 0);
        plasticMaterial = Interfaces::materialSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", 0);

        multicolorMaterial = createMaterial("multicolor", "VertexLitGeneric",
        R"#("VertexLitGeneric" {
            "$envmap" "editor/cube_vertigo"
            "$envmapcontrast" "1"
            "$envmaptint" "[.7 .7 .7]"
            "$basetexture" "dev/zone_warning"
            proxies {
                texturescroll {
                    texturescrollvar
                    $basetexturetransform
                    texturescrollrate 0.6
                    texturescrollangle 90
                }
            }
        })#");

        glowMaterial = createMaterial("glow", "VertexLitGeneric",
        R"#("VertexLitGeneric" {
            "$additive" "1"
            "$envmap" "models/effects/cube_white"
            "$envmaptint" "[1 1 1]"
            "$envmapfresnel" "1"
            "$envmapfresnelminmaxexp" "[0 1 2]"
            "$alpha" "0.8"
        })#");

        init = true;
    }
}

void cham(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld, bool enabled, ImColor color, ImColor overlayColor, int mat, bool ignoreZ) {
    static IMaterial* material;
    switch(mat) {
        case 0: material = shadedMaterial;  break;
        case 1: material = flatMaterial;  break;
        case 2: material = plasticMaterial; break;
        case 3: material = multicolorMaterial; break;
        case 4: material = glowMaterial; break;
    }
    if (enabled) {
        if (material == plasticMaterial) {
            shadedMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);
            shadedMaterial->AlphaModulate(color.Value.w);
            shadedMaterial->ColorModulate(color.Value.x, color.Value.y, color.Value.z);
            bool found;
            IMaterialVar* var = shadedMaterial->FindVar("$envmaptint", &found);
            if (found) {
                var->SetVecValue(color.Value.x, color.Value.y, color.Value.z);
            }
            Interfaces::modelRender->ForcedMaterialOverride(shadedMaterial);
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

            material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);
            material->ColorModulate(255, 255, 255);
            bool overlayFound;
            IMaterialVar* overlayVar = material->FindVar("$envmaptint", &found);
            if (found) {
                overlayVar->SetVecValue(255, 255, 255);
            }
            Interfaces::modelRender->ForcedMaterialOverride(material);
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
            Interfaces::modelRender->ForcedMaterialOverride(0);
        } else if (material == glowMaterial) {
            shadedMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);
            shadedMaterial->AlphaModulate(color.Value.w);
            shadedMaterial->ColorModulate(color.Value.x, color.Value.y, color.Value.z);
            bool found;
            IMaterialVar* var = shadedMaterial->FindVar("$envmaptint", &found);
            if (found) {
                var->SetVecValue(color.Value.x, color.Value.y, color.Value.z);
            }
            Interfaces::modelRender->ForcedMaterialOverride(shadedMaterial);
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

            material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);
            shadedMaterial->AlphaModulate(overlayColor.Value.w);
            material->ColorModulate(overlayColor.Value.x, overlayColor.Value.y, overlayColor.Value.z);
            bool overlayFound;
            IMaterialVar* overlayVar = material->FindVar("$envmaptint", &found);
            if (found) {
                overlayVar->SetVecValue(overlayColor.Value.x, overlayColor.Value.y, overlayColor.Value.z);
            }
            Interfaces::modelRender->ForcedMaterialOverride(material);
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
            Interfaces::modelRender->ForcedMaterialOverride(0);
        } else {
            material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);
            material->AlphaModulate(color.Value.w);
            material->ColorModulate(color.Value.x, color.Value.y, color.Value.z);
            bool found;
            IMaterialVar* var = material->FindVar("$envmaptint", &found);
            if (found) {
                var->SetVecValue(color.Value.x, color.Value.y, color.Value.z);
            }
            Interfaces::modelRender->ForcedMaterialOverride(material);
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
            Interfaces::modelRender->ForcedMaterialOverride(0);
        }
    } else {
        Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
}

void chamPlayer(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    Player* p = (Player*)Interfaces::entityList->GetClientEntity(pInfo.entity_index);
    if (Globals::localPlayer) {
        if (p->health() > 0) {
            if (p->isEnemy()) {
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGBOOL("Visuals>Players>Chams>Enemies>Occluded Enabled"), CONFIGCOL("Visuals>Players>Chams>Enemies>Occluded Color"), CONFIGCOL("Visuals>Players>Chams>Enemies>Overlay Color"), CONFIGINT("Visuals>Players>Chams>Enemies>Material"), true);
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGBOOL("Visuals>Players>Chams>Enemies>Enabled"), CONFIGCOL("Visuals>Players>Chams>Enemies>Visible Color"), CONFIGCOL("Visuals>Players>Chams>Enemies>Overlay Color"), CONFIGINT("Visuals>Players>Chams>Enemies>Material"), false);

                if (CONFIGBOOL("Legit>Backtrack>Backtrack") && !CONFIGBOOL("Rage>Enabled")) {
                    if (CONFIGBOOL("Visuals>Players>Chams>Enemies>Backtrack Enabled")) {
                        if (Features::Backtrack::backtrackTicks.size() > 2) {
                            Features::Backtrack::BackTrackTick tick = Features::Backtrack::backtrackTicks.at(Features::Backtrack::backtrackTicks.size()-1);
                            if (tick.players.find(p->index()) != tick.players.end()) {
                                if (fabsf((tick.players.at(p->index()).playerHeadPos - p->getBonePos(8)).Length2D()) > 2) {
                                    cham(thisptr, ctx, state, pInfo, tick.players.at(p->index()).boneMatrix, true, CONFIGCOL("Visuals>Players>Chams>Enemies>Backtrack Color"), CONFIGCOL("Visuals>Players>Chams>Enemies>Backtrack Overlay Color"), CONFIGINT("Visuals>Players>Chams>Enemies>Backtrack Material"), false);
                                }
                            }
                        }
                    }
                }
            }
            else {
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGBOOL("Visuals>Playes>Chams>Teammates>Occluded Enabled"), CONFIGCOL("Visuals>Players>Chams>Teammates>Occluded Color"), CONFIGCOL("Visuals>Players>Chams>Teammates>Overlay Color"), CONFIGINT("Visuals>Players>Chams>Teammates>Material"), true);
                cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGBOOL("Visuals>Playes>Chams>Teammates>Enabled"), CONFIGCOL("Visuals>Players>Chams>Teammates>Visible Color"), CONFIGCOL("Visuals>Players>Chams>Teammates>Overlay Color"), CONFIGINT("Visuals>Players>Chams>Teammates>Material"), false);
            }
        }
        else {
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
    }
}

void chamArms(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGBOOL("Visuals>Players>Chams>Arms Enabled"), CONFIGCOL("Visuals>Players>Chams>Arms Color"), CONFIGCOL("Visuals>Players>Chams>Arms Overlay Color"), CONFIGINT("Visuals>Players>Chams>Arms Material"), false);
}

void chamSleeves(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGBOOL("Visuals>Players>Chams>Sleeve Enabled"), CONFIGCOL("Visuals>Players>Chams>Sleeve Color"), CONFIGCOL("Visuals>Players>Chams>Sleeve Overlay Color"), CONFIGINT("Visuals>Players>Chams>Sleeve Material"), false);
}

void chamWeapon(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    if (Globals::localPlayer) {
        if (!Globals::localPlayer->scoped()) {
            cham(thisptr, ctx, state, pInfo, pCustomBoneToWorld, CONFIGBOOL("Visuals>Players>Chams>Weapon Enabled"), CONFIGCOL("Visuals>Players>Chams>Weapon Color"), CONFIGCOL("Visuals>Players>Chams>Weapon Overlay Color"), CONFIGINT("Visuals>Players>Chams>Weapon Material"), false);
        }
        else {
            Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }

    }
}

void Features::Chams::drawModelExecute(void* thisptr, void* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
    createMaterials();

	const char* modelName = Interfaces::modelInfo->GetModelName(pInfo.pModel);

    // TODO: Why do the shadows go bye bye?
	if (strstr(modelName, "models/player") && !strstr(modelName, "shadow")) {
        chamPlayer(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
    else if (strstr(modelName, "models/weapons/v_")) {
        if (strstr(modelName, "sleeve")) {
            chamSleeves(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
        else if (strstr(modelName, "arms")) {
            chamArms(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
        else {
            chamWeapon(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
        }
    }
    else if (strstr(modelName, "models/weapons/v_")) {
        chamWeapon(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
    else {
        Hooks::DrawModelExecute::original(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
    }
}
