#include "eventhandler.h"
#include "movingspeed.h"

#include "qtimer.h"

#include <QDebug>
#include <QKeyEvent>


EventHandler::EventHandler(std::vector<Island *> islands
                           ,PlayerCharacter *player_character,
                           PlayerPlane *player_plane)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(my_timer_slot()));
    int ms = 1000;
    int fps = 60;
    timer->start(ms/fps);

    this->islands = islands;
    this->player_character = player_character;
    this->player_plane = player_plane;

    player_island = NULL;
    object_collided = NULL;
}

void EventHandler::my_timer_slot() {
    if (!player_character_events) {
        std::pair<int, int> pixels_to_move (MovingSpeed::x_speed, MovingSpeed::y_speed);
        for(int i = 0; i < islands.size(); i++) {
            islands[i]->move_island(pixels_to_move.first, pixels_to_move.second);
        }

        player_plane->animation();
    }
}

void EventHandler::keyPressEvent(QKeyEvent *event) {
    // player character
    if (player_character_events) {
        if (event->key() == Qt::Key_E && collision_with_plane) {
            player_character_events = false;
            player_character->change_character_img(12);
            MovingSpeed::x_speed = 0;
            MovingSpeed::y_speed = 0;

            std::pair<int, int> pixels_to_move = player_plane->center_plane_on_screen(player_character);
            for(int i = 0; i < islands.size(); i++) {
                islands[i]->move_island(pixels_to_move.first, pixels_to_move.second);
            }
            player_plane->simple_movement(pixels_to_move.first, pixels_to_move.second);
        }
        else {
            player_island = player_character->player_on_island(event, islands);
            if (player_island) {
                object_collided = player_character->collision_with_island_objects(event, player_island);
                collision_with_plane = player_character->collision(event, player_plane->item);
                collision_with_island_borders = player_character->collision(event, player_island->island_item, true);

                if (!object_collided && !collision_with_plane && collision_with_island_borders) {
                    for(int i = 0; i < islands.size(); i++) {
                        islands[i]->move_island_event(event);
                    }
                    player_plane->simple_movement_event(event);
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
    }
    // player plane
    else {
        Island *plane_on_island = player_plane->plane_on_island(event, islands);
        if (event->key() == Qt::Key_E && plane_on_island && MovingSpeed::x_speed == 0 && MovingSpeed::y_speed == 0) {
            player_character_events = true;
            player_character->change_character_img(0);

            MovingSpeed::x_speed = 3;
            MovingSpeed::y_speed = 3;

            // leaving plane
            std::pair<int, int> pixels_to_move = player_plane->leave_plane(player_character);
            for(int i = 0; i < islands.size(); i++) {
                islands[i]->move_island(pixels_to_move.first, pixels_to_move.second);
            }
            player_plane->simple_movement(pixels_to_move.first, pixels_to_move.second);
        }
        else {
            player_plane->change_power(event);
            player_plane->rotate(event);
            player_plane->set_up_current_speed();
            player_plane->calculate_x_y_speed();
        }
    }

    update();
}
