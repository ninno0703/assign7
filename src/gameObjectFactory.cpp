#include "gameObjectFactory.h"

std::unique_ptr<GameObject> GameObjectFactory::createBreakoutObject(const Position& pos, BreakoutType type) {
    return std::make_unique<BreakoutGameObject>(pos, type);
}

std::unique_ptr<GameObject> GameObjectFactory::createBrickObject(const Position& pos, bool isPlayer) {
    return std::make_unique<BrickGameObject>(pos, isPlayer);
}