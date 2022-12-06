#include "eventhandler.h"
#include "movingspeed.h"

#include "qtimer.h"

#include <QDebug>
#include <QKeyEvent>


EventHandler::EventHandler(std::vector<Island *> islands
                           ,PlayerCharacter *player_character,
                           PlayerPlane *player_plane,
                           Settings *settings,
                           Sounds *sounds,
                           Interface *interface)
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
    this->settings = settings;
    this->sounds = sounds;
    this->interface = interface;

    player_character_events = true;
    collision_with_plane = false;
    collision_with_island_borders = false;

    player_last_position.first = 0;
    player_last_position.second = 0;

    player_island = NULL;
    interactive_object_collided = NULL;
}

void EventHandler::my_timer_slot() {
    sounds->music->play();

    if (!player_character_events) {
        interface->draw_speedometer(settings->window_height, false);

        for(int i = 0; i < islands.size(); i++) {
            islands[i]->move_island(MovingSpeed::x_speed, MovingSpeed::y_speed);
        }

        player_plane->animation();
        player_plane->set_up_current_speed();
        player_plane->calculate_x_y_speed();
    }
    else {
    }
}

void EventHandler::keyPressEvent(QKeyEvent *event) {
    // player character
    if (player_character_events) {
        if (event->key() == Qt::Key_E && collision_with_plane) {
            entering_plane_event();
        }
        else {
            character_on_island_event(event);
        }
    }
    // player plane
    else {
        if (event->key() == Qt::Key_E && MovingSpeed::current_speed == 0) {
            Island *plane_on_island = player_plane->plane_on_island(event, islands);
            if (plane_on_island) {
                leaving_plane_event();
                interface->draw_speedometer(settings->window_height);
            }
        }
        else {
            plane_events(event);
        }
    }

    update();
}

void EventHandler::entering_plane_event() {
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

void EventHandler::character_on_island_event(QKeyEvent *event) {
    player_island = player_character->player_on_island(event, islands);
    if (player_island) {
        InteractiveObject *object_collided_bufor = player_character->collision_with_island_objects(event, player_island);
        collision_with_plane = player_character->collision(event, player_plane->item);
        collision_with_island_borders = player_character->collision(event, player_island->island_item, true);

        if (!object_collided_bufor && !collision_with_plane && collision_with_island_borders) {
            character_moving(event);
        }
        else if (object_collided_bufor) {
            set_interactive_object_collided(object_collided_bufor);
        }

        if (interactive_object_collided) {
            add_resources_to_plane(event);
        }
    }

    player_character->player_animation(event);
    player_character->change_character_img();
}

void EventHandler::character_moving(QKeyEvent *event) {
    for(int i = 0; i < islands.size(); i++) {
        islands[i]->move_island_event(event);
    }
    player_plane->simple_movement_event(event);
}

void EventHandler::leaving_plane_event() {
    player_character_events = true;
    player_character->change_character_img(0);

    MovingSpeed::x_speed = 3;
    MovingSpeed::y_speed = 3;

    std::pair<int, int> pixels_to_move = player_plane->leave_plane(player_character);
    for(int i = 0; i < islands.size(); i++) {
        islands[i]->move_island(pixels_to_move.first, pixels_to_move.second);
    }
    player_plane->simple_movement(pixels_to_move.first, pixels_to_move.second);
}

void EventHandler::plane_events(QKeyEvent *event) {
    player_plane->change_power(event);
    player_plane->rotate(event);
}

void EventHandler::set_interactive_object_collided(InteractiveObject *object_collided_bufor) {
    player_last_position.first = player_plane->item->x();
    player_last_position.second = player_plane->item->y();
    interactive_object_collided = object_collided_bufor;
    interactive_object_collided->alert->show_alert_for_object = true;

    if (interactive_object_collided->cargo_alert)
        interactive_object_collided->show_alert(player_plane->cargo);
    else
        interactive_object_collided->show_alert(player_plane->fuel);
}

void EventHandler::add_resources_to_plane(QKeyEvent *event) {
    bool player_position_changed = (player_last_position.first != player_plane->item->x() || player_last_position.second != player_plane->item->y());

    if (event->key() == Qt::Key_E) {
        if (interactive_object_collided->cargo_alert) {
            player_plane->add_cargo(interactive_object_collided->max_amount_of_cargo());
            interactive_object_collided->show_alert(player_plane->cargo);
            sounds->add_resources->play();
        }
        else {
            player_plane->add_fuel(interactive_object_collided->max_amount_of_fuel());
            interactive_object_collided->show_alert(player_plane->fuel);
            sounds->add_resources->play();
        }
    }
    else if (event->key() == Qt::Key_Q) {
        if (interactive_object_collided->cargo_alert) {
            player_plane->remove_cargo();
            interactive_object_collided->show_alert(player_plane->cargo);
            sounds->add_resources->play();
        }
        else {
            player_plane->remove_fuel();
            interactive_object_collided->show_alert(player_plane->fuel);
            sounds->add_resources->play();
        }
    }
    else if (interactive_object_collided->alert->show_alert_for_object && player_position_changed) {
        interactive_object_collided->alert->show_alert_for_object = false;
        interactive_object_collided->hide_alert();
        interactive_object_collided = NULL;
    }
}
