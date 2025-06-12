#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "unit.h"
#include "icon.h"
#include "collider.h"
#include <iostream>
class GameObject{

public:
    GameObject(const Position& pos, const Icon& icon);
    Position getPosition() const;
    void move(int dx, int dy);
    Icon getIcon() const;
    virtual void update();
    virtual void setplayer(bool isPlayer){}
    virtual ICollider* getCollider() {
        return nullptr; // Default implementation, can be overridden
    }
protected:
    Position _pos;
    Icon _icon;
};

#endif
