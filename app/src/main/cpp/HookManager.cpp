//
// Created by TheChuan1503 on 2025/7/16.
//

#include "HookManager.h"
#ifndef GLOBAL_H
#define TAG "Native/HookManager"
#include "../global.h"
#endif
#include "Circlor.h"
#include "Gloss.h"
#include "mc/client/Minecraft.h"
#include "mc/gamemode/GameMode.h"
#include "mc/level/Level.h"
#include "mc/entity/actor/player/PlayerSnapshot.h"
#include "mc/entity/actor/player/Abilities.h"
#include "mc/entity/actor/MobEffectInstance.h"
#include "mc/client/MinecraftGame.h"
#include "mc/client/Timer.h"
#include "mc/entity/actor/player/LevelRendererPlayer.h"



bool nuking = false;



Abilities::getBool_t O_Abilities_getBool = nullptr;
ClientInstance::requestLeaveGame_t O_ClientInstance_requestLeaveGame = nullptr;
ClientInstance::update_t O_ClientInstance_update = nullptr;
GameMode::destroyBlock_t O_GameMode_destroyBlock = nullptr;
GameMode::getMaxPickRange_t O_GameMode_getMaxPickRange = nullptr;
Level::tick_t O_Level_tick = nullptr;
LevelRendererPlayer::getFov_t O_LevelRendererPlayer_getFov = nullptr;
LocalPlayer::getPickRange_t O_LocalPlayer_getPickRange = nullptr;
Minecraft::getTimer_t O_Minecraft_getTimer = nullptr;
MinecraftGame::tickInput_t O_MinecraftGame_tickInput = nullptr;
Player::getCameraOffset_t O_Player_getCameraOffset = nullptr;
Player::getSpeed_t O_Player_getSpeed = nullptr;



bool H_Abilities_getBool(Abilities* a, AbilitiesIndex ai) {
    bool rez = O_Abilities_getBool(a, ai);
    if (ai == AbilitiesIndex::MayFly) {
        if (clientInstance->getLocalPlayer() && clientInstance->getLocalPlayer()->getPlayerGameType() == GameType::Creative) {
            rez = true;
        } else {
            rez = Circlor::getBool("fly/enabled");
        }
    }
    if (ai == AbilitiesIndex::Flying) {
        if (Circlor::getBool("fly/enabled") && Circlor::getBool("fly/force/enabled")){
            rez = true;
        }
    }
    if (ai == AbilitiesIndex::NoClip) {
        rez = Circlor::getBool("no_clip/enabled");
    }
    return rez;
}
void H_ClientInstance_update(ClientInstance *ci, bool b) {
    clientInstance = ci;
    O_ClientInstance_update(ci, b);
    Circlor::onClientInstanceUpdate();
}
void H_ClientInstance_requestLeaveGame(ClientInstance *ci, bool b1, bool b2) {
    LOGD("ClientInstance::requestLeaveGame(%d, %d)", b1, b2);
    Circlor::setIsFirstTick(true);
    O_ClientInstance_requestLeaveGame(ci, b1, b2);
}
void H_GameMode_destroyBlock(GameMode *gm, const BlockPos *pos, unsigned char flag) {
    O_GameMode_destroyBlock(gm, pos, flag);
    if (Circlor::getFunctionBoolValue("destroy_block/disabled")) {
        return;
    }
    if (Circlor::getFunctionBoolValue("nuker/enabled")) {
        int radius = (int) Circlor::getFunctionValue("nuker/radius");
        if (radius > 0) {
            for (int x = -radius; x <= radius; x++) {
                for (int y = -radius; y <= radius; y++) {
                    for (int z = -radius; z <= radius; z++) {
                        BlockPos pos2(pos->x + x, pos->y + y, pos->z + z);
                        O_GameMode_destroyBlock(gm, &pos2, flag);
                    }
                }
            }
        }
    }
}
float H_GameMode_getMaxPickRange(GameMode *gm) {
    if (Circlor::getBool("reach/enabled")) {
        return (float) Circlor::getValue("reach/range");
    }
    return O_GameMode_getMaxPickRange(gm);
}
void H_Level_tick(Level* l) {
    Circlor::onTick(l);
    O_Level_tick(l);
}
float H_LevelRendererPlayer_getFov(LevelRendererPlayer* lrp, float f, char c) {
    float rez = O_LevelRendererPlayer_getFov(lrp, f, c);
    if (Circlor::getBool("zoom/enabled")) {
        rez = rez - (float) Circlor::getValue("zoom/value");
        if (rez > 180) {
            rez = 180;
        } else if (rez < 0) {
            rez = 0;
        }
    }
    if (Circlor::getBool("screen_reversal/enabled")) {
        rez = -rez;
    }
    return rez;
}
float H_LocalPlayer_getPickRange(LocalPlayer *lp) {
    if (Circlor::getBool("reach/enabled")) {
        return (float) Circlor::getValue("reach/range");
    }
    return O_LocalPlayer_getPickRange(lp);
}
Timer* H_Minecraft_getTimer(Minecraft* mc) {
    Timer* t = O_Minecraft_getTimer(mc);
    if (Circlor::getBool("timer/enabled")) {
        t->mTicksPerSecond = (float) Circlor::getValue("timer/scale") * 20;
    } else {
        t->mTicksPerSecond = 20;
    }
    return t;
}
void H_MinecraftGame_tickInput(MinecraftGame* mg) {
    O_MinecraftGame_tickInput(mg);
}
float H_Player_getCameraOffset(Player* p) {
    float offset = O_Player_getCameraOffset(p);
    if (Circlor::getBool("camera_height_offset/enabled")) {
        offset = offset + (float) Circlor::getValue("camera_height_offset/value");
    }
    return offset;
}
float H_Player_getSpeed(Player* p) {
    float speed = O_Player_getSpeed(p);
    if (Circlor::getBool("speed/enabled")) {
        speed = speed + (float)(Circlor::getValue("speed/value") * 0.03);
    }
    return speed;
}



void HookManager::init() {
    hook("Abilities::getBool", (void*)&H_Abilities_getBool, (void**)&O_Abilities_getBool);
    hook("ClientInstance::requestLeaveGame", (void*)&H_ClientInstance_requestLeaveGame, (void**)&O_ClientInstance_requestLeaveGame);
    hook("ClientInstance::update", (void*)&H_ClientInstance_update, (void**)&O_ClientInstance_update);
    hook("GameMode::destroyBlock", (void*)&H_GameMode_destroyBlock, (void**)&O_GameMode_destroyBlock);
    hook("GameMode::getMaxPickRange", (void*)&H_GameMode_getMaxPickRange, (void**)&O_GameMode_getMaxPickRange);
    hook("Level::tick", (void*)&H_Level_tick, (void**)&O_Level_tick);
    hook("LevelRendererPlayer::getFov", (void*)&H_LevelRendererPlayer_getFov, (void**)&O_LevelRendererPlayer_getFov);
    hook("LocalPlayer::getPickRange", (void*)&H_LocalPlayer_getPickRange, (void**)&O_LocalPlayer_getPickRange);
//    hook("MinecraftGame::tickInput", (void*)&H_MinecraftGame_tickInput, (void**)&O_MinecraftGame_tickInput);
    hook("Minecraft::getTimer", (void*)&H_Minecraft_getTimer, (void**)&O_Minecraft_getTimer);
    hook("Player::getCameraOffset", (void*)&H_Player_getCameraOffset, (void**)&O_Player_getCameraOffset);
    hook("Player::getSpeed", (void*)&H_Player_getSpeed, (void**)&O_Player_getSpeed);
}



void HookManager::hook(const char *name, void *hook) {
    HookManager::hook(getOffset(name), hook);
}
void HookManager::hook(const char *name, void *hook, void **original) {
    HookManager::hook(getOffset(name), hook, original);
}
void HookManager::hook(long target, void *hook) {
    HookManager::hook(target, hook, nullptr);
}
void HookManager::hook(long target, void *hook, void **original) {
    void *targetAddr = (void *)((uintptr_t)getMinecraftBase() + target);
    GlossHook(targetAddr, hook, original);
    LOGD("Hooked %p", targetAddr);
}