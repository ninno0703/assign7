#include "RPSGameObject.h"
#include "iconFactory.h"

Icon PSR[3]= {IconFactory::createIcon({{"R"}}, Color::RED),
                    IconFactory::createIcon({{"P"}}, Color::GREEN),
                    IconFactory::createIcon({{"S"}}, Color::BLUE)
                    };
Icon playerIcon = IconFactory::createIcon({{"R"}}, Color::YELLOW);
RPSGameObject::RPSGameObject(const Position& pos, RPSType type) 
     : GameObject(pos, (type == ROCK   ? PSR[0]
       : type == PAPER ? PSR[1]
                       : PSR[2])), t(type) {
    // Initialize the icon based on the type
    if(player) _icon=playerIcon;
  }
void RPSGameObject::update() {
        
    switch (t) {
        case ROCK:
            if(!player) _icon = PSR[0]; // If not player, use ROCK icon
            else _icon = playerIcon; // If this is the player, use the player icon
            break;
        case PAPER:
            _icon = PSR[1]; // Example icon for PAPER
            // Update logic for PAPER
            break;
        case SCISSORS:
            _icon = PSR[2]; // Example icon for SCISSORS
            // Update logic for SCISSORS
            break;
        default:
            // Handle unexpected type
            break;
    }
}
bool RPSGameObject::onCollision(ICollider *other) {
    RPSGameObject *otherRPS = dynamic_cast<RPSGameObject *>(other);
    if (!otherRPS) return 0; // Not an RPSGameObject, no collision handling
    if(otherRPS->getType() == t) {
        // Handle collision with same type (e.g., no effect)
        return 0;
    }
    if(otherRPS->getType() == ROCK && t == SCISSORS) {
        // Scissors lose to Rock
        setType(ROCK); // Change Scissors to Rock
        // Handle Scissors losing to Rock
    } else if(otherRPS->getType() == PAPER && t == ROCK) {
        if(player) return 1;
        setType(PAPER); // Change Rock to Paper
        // Rock loses to Paper
        // Handle Rock losing to Paper
    } else if(otherRPS->getType() == SCISSORS && t == PAPER) {
        setType(SCISSORS); // Change Paper to Scissors
        // Paper loses to Scissors
        // Handle Paper losing to Scissors
    }
    return 0;
}
bool RPSGameObject::intersect(ICollider *other) {
    RPSGameObject *otherRPS = dynamic_cast<RPSGameObject *>(other);
    if (!otherRPS) return false; // Not an RPSGameObject, no intersection
    if(getPosition().distance(otherRPS->getPosition())<=1) return true; // Same position, intersection occurs
    // Implement intersection logic here
    return false; // Placeholder return value
}
RPSType RPSGameObject::getType() const {
    return t;
}
void RPSGameObject::setType(RPSType type) {
    t=type;
}
ICollider* RPSGameObject::getCollider() {
    return this; // Return itself as the collider
}
/*void RPSGameObject::setDirection(Direction dir) {
    _dir = dir;
}*/