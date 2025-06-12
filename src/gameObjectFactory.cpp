// TODO implementation
#include "gameObjectFactory.h"

std::unique_ptr<GameObject> GameObjectFactory::createGameObject(const Position& pos, RPSType type) {
    return std::make_unique<RPSGameObject>(pos, type);
}