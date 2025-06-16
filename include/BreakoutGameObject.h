#ifndef BREAKOUT_GAME_OBJECT_H
#define BREAKOUT_GAME_OBJECT_H

#include "gameObject.h"
#include "collider.h"
#include "unit.h"

enum BreakoutType { PADDLE = 0, BALL };

class BreakoutGameObject : public GameObject, public ICollider {
public:
    BreakoutGameObject(const Position& pos, BreakoutType type);

    void update() override;
    bool onCollision(ICollider* other) override;
    bool intersect(ICollider* other) override;

    BreakoutType getType() const;
    void setType(BreakoutType type);

    ICollider* getCollider() override;

    void setplayer(bool isPlayer) override { player = isPlayer; }

    void setDirection(int dx, int dy);
    void getBallDirection(int& dx, int& dy) const;

private:
    BreakoutType type;
    bool  player = false;
    int   dirX   = 0;
    int   dirY   = 0;
};

#endif // BREAKOUT_GAME_OBJECT_H
