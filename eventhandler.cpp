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
    bool player_on_island = false;
    Island *player_island;
    for(int i = 0; i < islands.size(); i++) {
        player_on_island = player_character->player_item->collidesWithItem(islands[i]->island_item, Qt::ContainsItemShape);
        if (player_on_island) {
            player_island = islands[i];
            break;
        }
    }

    if (player_on_island) {
        bool player_object_on_island_collision = false;
        player_on_island = player_character->collision(event, player_island->island_item, true);
        QGraphicsPixmapItem *island_object_item;

        for(int i = 0; i < player_island->objects.size(); i++) {
            island_object_item = player_island->objects[i]->item;
            player_object_on_island_collision = player_character->collision(event, island_object_item);
        }

        if (!player_object_on_island_collision && player_on_island) {
            for(int i = 0; i < islands.size(); i++) {
                islands[i]->move_island(event);
            }
        }
    }
}
