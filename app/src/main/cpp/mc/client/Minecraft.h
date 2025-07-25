//
// Created by TheChuan1503 on 2025/7/16.
//

#ifndef CIRCLORALPHA_MINECRAFT_H
#define CIRCLORALPHA_MINECRAFT_H


#include "../gamemode/GameType.h"
#include "Timer.h"

class Minecraft {
public:
    typedef Timer* (*getTimer_t) (Minecraft*);
    typedef void (*setGameModeReal_t)(void* minecraft, GameType);
    typedef void (*update_t)(void* minecraft);

    void setGameModeReal(GameType);
};


#endif //CIRCLORALPHA_MINECRAFT_H
