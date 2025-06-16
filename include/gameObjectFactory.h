#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <memory>
#include "BreakoutGameObject.h"  
#include "BrickGameObject.h"

class GameObjectFactory {
public:
    static std::unique_ptr<GameObject>
        createBreakoutObject(const Position& pos, BreakoutType type);

    static std::unique_ptr<GameObject>
        createBrickObject(const Position& pos, bool isPlayer);
};

#endif
