//
// Created by TheChuan1503 on 2025/4/26.
//

#ifndef CIRCLOR2_CIRCLOR_H
#define CIRCLOR2_CIRCLOR_H


#include "mc/entity/actor/Actor.h"
#include "mc/level/Level.h"

class Circlor {
public:
    static bool isFirstTick;

    static double getFunctionValue(const char *path);
    static bool getFunctionBoolValue(const char *path);
    static void setFunctionValue(const char *path, double value);
    static std::string getFunctionStringValue(const char *path);
    static void setFunctionStringValue(const char *path, const char *value);
    static void setIsFirstTick(bool value);
    static float randf(float, float);

    static double getValue(const char *path);
    static void setValue(const char *path, double value);
    static std::string getString(const char *path);
    static void setString(const char *path, const char *value);
    static bool getBool(const char *path);
    static void setBool(const char *path, bool value);

    static void onClientInstanceUpdate();
    static void onTick(Level*);
    static void onDoubleTick(Level*);

    static std::string invoke(std::string);

    static bool addEffect(unsigned int effectId, int durationTicks, int level, bool effectVisible);
    static bool addEffect(Actor *actor, unsigned int effectId, int durationTicks, int level, bool effectVisible);
    static void chatD(std::string const&);
    static void chatI(std::string const&);
    static void chatE(std::string const&);
    static void chatW(std::string const&);
};


#endif //CIRCLOR2_CIRCLOR_H
