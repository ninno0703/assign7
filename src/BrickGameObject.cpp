#include "BrickGameObject.h"
#include "BreakoutGameObject.h"           
#include "iconFactory.h"

static Icon brickIcon       = IconFactory::createIcon({{"#"}}, Color::RED);
static Icon playerBrickIcon = IconFactory::createIcon({{"#"}}, Color::YELLOW);

BrickGameObject::BrickGameObject(const Position& pos, bool isPlayer)
    : GameObject(pos, isPlayer ? playerBrickIcon : brickIcon),
      player(isPlayer) {}

void BrickGameObject::update() {
    _icon = player ? playerBrickIcon : brickIcon;
}

bool BrickGameObject::onCollision(ICollider* other) {
    auto* ball = dynamic_cast<BreakoutGameObject*>(other);
    if (ball && ball->getType() == BALL) {
        int dx, dy;
        ball->getBallDirection(dx, dy);
        ball->setDirection(dx, -dy);      
        return true;                      
    }
    return false;
}

bool BrickGameObject::intersect(ICollider* other) {
    auto* b = dynamic_cast<BrickGameObject*>(other);
    return b && getPosition().distance(b->getPosition()) <= 1;
}

ICollider* BrickGameObject::getCollider() { return this; }
