//
// Created by TheChuan1503 on 2025/4/27.
//

#ifndef CIRCLOR2_LOCALPLAYER_H
#define CIRCLOR2_LOCALPLAYER_H


#include <cstdint>
#include "Player.h"
#include "../../../gamemode/GameType.h"

class LocalPlayer: public Player{
public:
    typedef void (*addLevels_t)(LocalPlayer*, int);
    typedef float (*getPickRange_t)(LocalPlayer*);
    typedef bool (*isFlying_t)(LocalPlayer*);
    typedef void (*setPlayerGameType_t)(LocalPlayer*, GameType);
    typedef void (*setPlayerGameTypeWithoutServerNotification_t)(LocalPlayer*, GameType);

    void addLevels(int levels);
    virtual bool isLocalPlayer() const override {
        return true;
    };
    void setPlayerGameType(GameType gameType);
    void setPlayerGameTypeWithoutServerNotification(GameType gameType);
    void setPos(const Vec3 *);
};


#endif //CIRCLOR2_LOCALPLAYER_H
