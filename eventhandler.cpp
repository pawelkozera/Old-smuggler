#include "eventhandler.h"

#include <QDebug>
#include <QKeyEvent>


EventHandler::EventHandler(std::vector<Island *> islands
                           ,PlayerCharacter *player_character,
                           PlayerPlane *player_plane)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    this->islands = islands;
    this->player_character = player_character;
    this->player_plane = player_plane;

    player_island = NULL;
    object_collided = NULL;
}

void EventHandler::keyPressEvent(QKeyEvent *event) {
    // // player
    if (player_character_events) {
        player_island = player_character->player_on_island(event, islands);
        if (player_island) {
            object_collided = player_character->collision_with_island_objects(event, player_island);
            bool collision_with_plane = player_character->collision(event, player_plane->item);
            bool collision_with_island_borders = player_character->collision(event, player_island->island_item, true);

            if (!object_collided && !collision_with_plane && collision_with_island_borders) {
                for(int i = 0; i < islands.size(); i++) {
                    islands[i]->move_island(event);
                }
                player_plane->simple_movement(event);
            }
            else if (object_collided) {
                /*
                Resources *res = static_cast<Resources*>(island_object); // check if it's resource or fuel !!!!!!!!!!!!
                res->show_text();
                */
            }
        }

        player_character->player_animation(event);
        player_character->change_character_img();
    }

    update();
}
