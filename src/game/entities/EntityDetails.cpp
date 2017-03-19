#include "Entity.h"
#include "game/player/Player.h"
#include "EntityDetails.h"

#include "communication/outgoing/user/CreditsMessageComposer.h"

EntityDetails::EntityDetails(Entity *entity) :
    entity(entity) { }

EntityDetails::~EntityDetails() {


}

void EntityDetails::setCredits(int new_amount) {

    this->credits = new_amount;

    if (entity->getEntityType() == PLAYER) {
        Player *player = dynamic_cast<Player*>(entity);
        player->send(CreditsMessageComposer(new_amount));
    }
}