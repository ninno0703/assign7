#ifndef RPS_H
#define RPS_H

#include "collider.h"
#include "gameObject.h"
#include "unit.h"

enum RPSType { ROCK = 0, PAPER, SCISSORS };
extern Icon PSR[3];
class RPSGameObject : public GameObject, public ICollider {

public:
  RPSGameObject(const Position& pos, RPSType type);
  void update() override;
  bool onCollision(ICollider *other) override;
  bool intersect(ICollider *other) override;
  RPSType getType() const;
  void setType(RPSType type);
  //void setDirection(Direction);
  ICollider* getCollider() override;
  void setplayer(bool isPlayer) override {
      player = isPlayer;
  }
private:
  RPSType t;
  bool player = false;
  //Direction d;
};

#endif
