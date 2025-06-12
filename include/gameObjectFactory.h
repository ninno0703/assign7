// TODO 
// Finish the declaration of GameObjectFactory that
// 1. offers some methods to create a GameObject.
// 2. encapsulates the constructor from the caller. 
#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H
#include "gameObject.h"
#include <memory>
#include "RPSGameObject.h"
class GameObjectFactory {
public:
    // Factory method to create a GameObject
    static std::unique_ptr<GameObject> createGameObject(const Position& pos, RPSType type);

    // Other factory methods can be added here for different types of GameObjects
};
#endif

