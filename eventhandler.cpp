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
    bool player_island_collision = true;
    for(int i = 0; i < islands.size(); i++) {
        Island *island = islands[i];
        player_island_collision = island->collision_with_player(player_character->player_item);
        if (!player_island_collision) {
            break;
        }
    }

    if (!player_island_collision) {
        for(int i = 0; i < islands.size(); i++) {
            Island *island = islands[i];
            island->move_to_the_last_position();
        }
    }
    else {
        for(int i = 0; i < islands.size(); i++) {
            islands[i]->move_island(event);
        }
    }

    // player
    player_character->player_animation(event);

    update();
}
