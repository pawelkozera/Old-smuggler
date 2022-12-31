#include "eventhandler.h"
#include "movingspeed.h"

#include "qtimer.h"

#include <QDebug>
#include <QKeyEvent>

#include <random>


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
        interface->draw_cockpit(settings->window_height, player_plane);

        for(int i = 0; i < islands.size(); i++) {
            islands[i]->move_island(MovingSpeed::x_speed, MovingSpeed::y_speed);
        }

        player_plane->animation();
        player_plane->set_up_current_speed();
        player_plane->calculate_x_y_speed();
        player_plane->fuel_usage();
    }
    else {
    }
}

void EventHandler::keyPressEvent(QKeyEvent *event) {
    // player character
    if (player_character_events) {
        if (event->key() == Qt::Key_E && collision_with_plane) {
            entering_plane_event();
            interface->cockpit_item->show();
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
                interface->cockpit_item->hide();
                interface->draw_cockpit(settings->window_height, player_plane);
            }
        }
        else {
            plane_events(event);
        }
    }
    // both plane and player character
    if (event->key() == Qt::Key_M) {
        interface->draw_map();
    }

    update();
}

void EventHandler::entering_plane_event() {
    player_character_events = false;
    player_character->player_item->hide();
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
            interactive_objects_handler(event);
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
    player_character->player_item->show();

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
    else if (interactive_object_collided->fuel_alert)
        interactive_object_collided->show_alert(player_plane->fuel);
    else
        interactive_object_collided->show_alert(player_plane->cargo);
}

void EventHandler::interactive_objects_handler(QKeyEvent *event) {
    bool player_position_changed = (player_last_position.first != player_plane->item->x() || player_last_position.second != player_plane->item->y());

    if (event->key() == Qt::Key_E) {
        if (interactive_object_collided->cargo_alert) {
            player_plane->add_cargo(interactive_object_collided->max_amount_of_cargo());
            interactive_object_collided->show_alert(player_plane->cargo);
            sounds->add_resources->play();
        }
        else if (interactive_object_collided->fuel_alert) {
            player_plane->add_fuel(interactive_object_collided->max_amount_of_fuel());
            interactive_object_collided->show_alert(player_plane->fuel);
            sounds->add_resources->play();
        }
        else {
            if (player_island->target_island) {
                if (player_plane->cargo > 0) {
                    score->increase(player_plane->cargo);
                    player_plane->cargo = 0;
                    interactive_object_collided->show_alert(player_plane->cargo);
                    select_target_island(player_island);
                }
            }
        }
    }
    else if (event->key() == Qt::Key_Q) {
        if (interactive_object_collided->cargo_alert) {
            player_plane->remove_cargo();
            interactive_object_collided->show_alert(player_plane->cargo);
            sounds->add_resources->play();
        }
        else if (interactive_object_collided->fuel_alert) {
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

void EventHandler::select_target_island(const Island *previous_target_island) {
    for (int i = 0; i < islands.size(); i++) {
        islands[i]->target_island = false;
    }

    // random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, islands.size() - 1);

    int island_index;
    do {
       island_index = distr(gen);
    }
    while (islands[island_index] == previous_target_island);


    islands[island_index]->target_island = true;
    map->generate_img_of_map(islands);
    interface->map_img.load("../smuggler/assets/interface/map.png");

    interface->map_img = interface->map_img.scaled(1408, 792);
    interface->map_item->setPixmap(interface->map_img);
}
