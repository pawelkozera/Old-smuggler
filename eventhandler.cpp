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
    // islands
    for(int i = 0; i < islands.size(); i++) {
        islands[i]->move_island(event);
    }

    // player
    player_character->player_animation(event);

    update();
}
