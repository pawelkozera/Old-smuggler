#include "playerplane.h"
#include "movingspeed.h"

#include <QKeyEvent>
#include <QDebug>
#include <cmath>

PlayerPlane::PlayerPlane() {
    current_index_of_plane_img = 0;
    fuel = 0;
    cargo = 0;
    rotation_degree = 0;
    delay_animation = 3;
    delay_animation_counter = 0;

    QPixmap plane_img;
    for (int i = 1; i <= 3; i++) {
        QString location = "../smuggler/assets/player_plane/plane" + QString::number(i) + QString(".png");
        plane_img.load(location);
        imgs.push_back(plane_img);
    }
}

void PlayerPlane::animation() {
    if (current_index_of_plane_img >= 2 && delay_animation_counter == delay_animation) {
        current_index_of_plane_img = 0;
        delay_animation_counter = 0;
        item->setPixmap(imgs[current_index_of_plane_img]);
    }
    else {
        if (delay_animation_counter == delay_animation) {
            current_index_of_plane_img++;
            item->setPixmap(imgs[current_index_of_plane_img]);
            delay_animation_counter = 0;
        }
    }
    delay_animation_counter++;
}

std::pair<int, int> PlayerPlane::center_plane_on_screen(PlayerCharacter *player_character) {
    std::pair<int, int> pixels_to_move;
    pixels_to_move.first = player_character->player_item->x() - item->x() - imgs[0].width()/2;
    pixels_to_move.second = player_character->player_item->y() - item->y() - imgs[0].height()/2;

    return pixels_to_move;
}

std::pair<int, int> PlayerPlane::leave_plane(PlayerCharacter *player_character) {
    std::pair<int, int> pixels_to_move;
    float radius = 18;
    const float pi = 3.14159265;
    float degree = 0;
    int x_last_position = player_character->player_item->x();
    int y_last_position = player_character->player_item->y();
    int x = 0;
    int y = 0;

    bool character_plane_collision = true;
    while (radius <= 40 && character_plane_collision) {
        x = radius * sin(pi * 2.0 * degree / 360.0);
        y = radius * cos(pi * 2.0 * degree / 360.0);

        if (degree <= 90)
            player_character->player_item->setPos(x_last_position - x, y_last_position - y);
        else if (degree <= 180)
            player_character->player_item->setPos(x_last_position - x, y_last_position + y);
        else if (degree <= 270)
            player_character->player_item->setPos(x_last_position + x, y_last_position + y);
        else
            player_character->player_item->setPos(x_last_position - x, y_last_position - y);

        character_plane_collision = player_character->player_item->collidesWithItem(item);

        degree += 3;
        if (degree > 360) {
            degree = 0;
            radius += 4;
        }
    }

    player_character->player_item->setPos(x_last_position, y_last_position);
    pixels_to_move.first = x;
    pixels_to_move.second = y;

    return pixels_to_move;
}

void PlayerPlane::simple_movement_event(QKeyEvent *event,  int x_speed, int y_speed) {
    if (event->key() == Qt::Key_A) {
        simple_movement(x_speed, 0);
    }
    else if (event->key() == Qt::Key_D) {
        simple_movement(-x_speed, 0);
    }
    else if (event->key() == Qt::Key_W) {
        simple_movement(0, y_speed);
    }
    else if (event->key() == Qt::Key_S) {
        simple_movement(0, -y_speed);
    }
}

void PlayerPlane::simple_movement(int x_speed, int y_speed) {
    int plane_x = item->x();
    int plane_y = item->y();
    item->setPos(plane_x + x_speed, plane_y + y_speed);
}

Island* PlayerPlane::plane_on_island(QKeyEvent *event, std::vector<Island *> islands) {
    bool plane_on_island = false;

    for(int i = 0; i < islands.size(); i++) {
        plane_on_island = item->collidesWithItem(islands[i]->island_item, Qt::ContainsItemShape);
        if (plane_on_island) {
            return islands[i];
        }
    }
    return NULL;
}

void PlayerPlane::change_power(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) {
        if (MovingSpeed::current_power < MovingSpeed::max_power)
            MovingSpeed::current_power++;
    }
    else if (event->key() == Qt::Key_S) {
        if (MovingSpeed::current_power > 0)
            MovingSpeed::current_power--;
    }
}

void PlayerPlane::rotate(QKeyEvent *event) {
    float rotate = 0;

    if (MovingSpeed::current_speed < 30)
        rotate = 0;
    else if (MovingSpeed::current_speed <= 61)
        rotate = 1;
    else if (MovingSpeed::current_speed <= 121)
        rotate = 2;
    else
        rotate = 3;

    if (event->key() == Qt::Key_A) {
        float i = 0;
        while (i < rotate) {
            i += 0.05;
            rotation_degree -= 0.05;
            item->setRotation(rotation_degree);
        }
    }
    else if (event->key() == Qt::Key_D) {
        float i = 0;
        while (i < rotate) {
            i += 0.05;
            rotation_degree += 0.05;
            item->setRotation(rotation_degree);
        }
    }

    if (abs(rotation_degree) >= 360) {
        float degree = abs(rotation_degree) - 360;
        rotation_degree = degree;
    }

}

void PlayerPlane::set_up_current_speed() {
    int current_power = MovingSpeed::current_power/MovingSpeed::division_power_factor_index;
    if (current_power > 10 || current_power < 0)
        return;

    int max_speed = MovingSpeed::max_speed[current_power];

    if (MovingSpeed::current_speed < max_speed)
        MovingSpeed::current_speed += 0.4;
    else if (MovingSpeed::current_speed > max_speed)
        MovingSpeed::current_speed -= 0.5;

    if (MovingSpeed::current_speed < 0)
        MovingSpeed::current_speed = 0;
}

void PlayerPlane::calculate_x_y_speed() {
    const long double pi = 3.14159265358979323851;

    MovingSpeed::x_speed = -(MovingSpeed::current_speed*cos(rotation_degree*pi/180.0)/MovingSpeed::division_factor_speed);
    MovingSpeed::y_speed = -(MovingSpeed::current_speed*sin(rotation_degree*pi/180.0)/MovingSpeed::division_factor_speed);
}

void PlayerPlane::add_cargo(int max_cargo) {
    if (cargo < max_cargo)
        cargo++;
}

void PlayerPlane::remove_cargo() {
    if (cargo > 0)
        cargo--;
}

void PlayerPlane::add_fuel(int max_fuel) {
    if (fuel < max_fuel)
        fuel++;
}

void PlayerPlane::remove_fuel() {
    if (fuel > 0)
        fuel--;
}
