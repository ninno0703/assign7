#ifndef BRICK_GAME_OBJECT_H
#define BRICK_GAME_OBJECT_H

#include "collider.h"
#include "gameObject.h"
#include "unit.h"

class BrickGameObject : public GameObject, public ICollider {
public:
    BrickGameObject(const Position& pos, bool isPlayer);

    void update() override;
    bool onCollision(ICollider* other) override;
    bool intersect(ICollider* other) override;
    ICollider* getCollider() override;

    void setplayer(bool isPlayer) override {
        player = isPlayer;
    }

private:
    bool player = false;
};

#endif // BRICK_GAME_OBJECT_H
