#include "gameObject.h"

Position GameObject::getPosition() const {
    return _pos;
}
Icon GameObject::getIcon() const {
    return _icon;
}
void GameObject::move(int dx, int dy) {
    _pos.move(dx, dy);
}
void GameObject::update() {
}
GameObject::GameObject(const Position& pos, const Icon& icon) : _pos(pos), _icon(icon) {
}
