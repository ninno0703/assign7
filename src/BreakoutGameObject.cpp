#include "BreakoutGameObject.h"
#include "BrickGameObject.h"           
#include "iconFactory.h"
#include "environment.h"

static Icon paddleIcon       = IconFactory::createIcon({{"=="}}, Color::CYAN);
static Icon playerPaddleIcon = IconFactory::createIcon({{"=="}}, Color::YELLOW);
static Icon ballIcon         = IconFactory::createIcon({{"O"}},  Color::WHITE);

BreakoutGameObject::BreakoutGameObject(const Position& pos, BreakoutType tp)
    : GameObject(pos, tp == BALL ? ballIcon : paddleIcon), type(tp) {
    if (type == PADDLE && player) _icon = playerPaddleIcon;
    if (type == BALL) { dirX = 1; dirY = -1; }
}

void BreakoutGameObject::update() {
    switch (type) {
        case PADDLE:
            _icon = player ? playerPaddleIcon : paddleIcon;
            break;
        case BALL:
            _icon = ballIcon;
            move(dirX, dirY);
            break;
    }
}

bool BreakoutGameObject::onCollision(ICollider* other) {
    if (type == BALL) {
        if (auto* paddle = dynamic_cast<BreakoutGameObject*>(other);
            paddle && paddle->getType() == PADDLE) {
            dirY = -1;
            Position pp = paddle->getPosition();
            Position bp = getPosition();
            dirX = (bp.x() < pp.x()) ? -1 : (bp.x() > pp.x()) ? 1 : dirX;
            return false;
        }

        if (auto* brick = dynamic_cast<BrickGameObject*>(other)) {
            dirY = -dirY;
            return true;   
        }
    }
    return false; 
}

bool BreakoutGameObject::intersect(ICollider* other) {
    if (auto* ob = dynamic_cast<BreakoutGameObject*>(other))
        return (getPosition().distance(ob->getPosition()) <= 2&& (getPosition().y() == ob->getPosition().y()-1 || 
                getPosition().y() == ob->getPosition().y()));

    if (auto* brick = dynamic_cast<BrickGameObject*>(other))
        return getPosition().distance(brick->getPosition()) <= 1;

    return false;
}

BreakoutType BreakoutGameObject::getType() const { return type; }
void BreakoutGameObject::setType(BreakoutType t) { type = t; }
ICollider* BreakoutGameObject::getCollider()     { return this; }

void BreakoutGameObject::setDirection(int dx, int dy) { dirX = dx; dirY = dy; }
void BreakoutGameObject::getBallDirection(int& dx, int& dy) const { dx = dirX; dy = dirY; }
