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
    island_collision(event);

    // player
    player_character->player_animation(event);
    player_character->change_character_img();

    update();
}

void EventHandler::island_collision(QKeyEvent *event) {
    bool player_island_collision = false;
    Island *player_island;
    for(int i = 0; i < islands.size(); i++) {
        player_island_collision = player_character->player_item->collidesWithItem(islands[i]->island_item, Qt::ContainsItemShape);
        if (player_island_collision) {
            player_island = islands[i];
            break;
        }
    }

    if (player_island_collision) {
        if (player_character->collision(event, player_island->island_item)) {
            for(int i = 0; i < islands.size(); i++) {
                islands[i]->move_island(event);
            }
        }
    }
}
