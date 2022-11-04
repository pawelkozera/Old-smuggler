#include "eventhandler.h"

#include <QDebug>
#include <QKeyEvent>


EventHandler::EventHandler(std::vector<Island *> islands
                           ,PlayerCharacter *player_character)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    this->islands = islands;
    this->player_character = player_character;
}

void EventHandler::keyPressEvent(QKeyEvent *event) {
    // // player
    player_character->collision_on_island(event, islands);
    player_character->player_animation(event);
    player_character->change_character_img();

    update();
}
