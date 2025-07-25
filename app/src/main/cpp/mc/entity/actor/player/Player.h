//
// Created by TheChuan1503 on 2025/5/2.
//

#ifndef CIRCLOR2_PLAYER_H
#define CIRCLOR2_PLAYER_H

#include "../../../math/Vec3.h"
#include "../Actor.h"
#include "../../../gamemode/GameType.h"

class Player: public Actor {
public:
    typedef void (*attack_t) (Player*, Actor*);
    typedef float (*getCameraOffset_t) (Player*);
    typedef GameType (*getPlayerGameType_t) (Player*);
    typedef float (*getSpeed_t) (Player*);
    typedef void (*teleportTo_t) (Player *player, Vec3&, bool, int, int, bool);

    void attack (Actor*);
    GameType getPlayerGameType();
    virtual bool isPlayer() const override {
        return true;
    };
    void teleportTo(Vec3 &, bool, int, int, bool);
};

#endif //CIRCLOR2_PLAYER_H
