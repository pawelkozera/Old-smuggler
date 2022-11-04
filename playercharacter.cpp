#include "playercharacter.h"
#include "movingspeed.h"

#include <QDebug>
#include <QKeyEvent>


PlayerCharacter::PlayerCharacter(int x, int y) {
    current_index_of_player_img = 0;
    delay_animation_counter = 0;
    delay_animation = 7;

    QPixmap player_img;
    for (int i = 1; i <= 12; i++) {
        QString location = "../smuggler/assets/player_character/player" + QString::number(i) + QString(".png");
        player_img.load(location);
        player_imgs.push_back(player_img);
    }

    setPos(x, y);
}


void PlayerCharacter::player_animation(QKeyEvent *event) {
    bool key_pressed = false;
    // moving left
    if (event->key() == Qt::Key_A) {
        key_pressed = true;
        if (delay_animation_counter == delay_animation) {
            change_current_index(11, 9);
        }
    }

    // moving right
    if (event->key() == Qt::Key_D) {
        key_pressed = true;
        if (delay_animation_counter == delay_animation) {
            change_current_index(5, 3);
        }
    }

    // moving up
    if (event->key() == Qt::Key_W) {
        key_pressed = true;
        if (delay_animation_counter == delay_animation) {
            change_current_index(8, 6);
        }
    }

    // moving down
    if (event->key() == Qt::Key_S) {
        key_pressed = true;
        if (delay_animation_counter == delay_animation) {
            change_current_index(2, 0);
        }
    }
    if (key_pressed)
        delay_animation_counter++;
}

void PlayerCharacter::change_current_index(int max_index, int min_index) {
    if (current_index_of_player_img < max_index && current_index_of_player_img >= min_index) {
        current_index_of_player_img++;
    }
    else {
        current_index_of_player_img = min_index;
    }
    delay_animation_counter = 0;
}

void PlayerCharacter::change_character_img() {
    player_item->setPixmap(player_imgs[current_index_of_player_img]);
}

void PlayerCharacter::collision_on_island(QKeyEvent *event, std::vector<Island *> islands) {
    bool player_on_island = false;
    Island *player_island;
    for(int i = 0; i < islands.size(); i++) {
        player_on_island = player_item->collidesWithItem(islands[i]->island_item, Qt::ContainsItemShape);
        if (player_on_island) {
            player_island = islands[i];
            break;
        }
    }

    if (player_on_island) {
        bool player_object_on_island_collision = false;
        player_on_island = collision(event, player_island->island_item, true);
        QGraphicsPixmapItem *island_object_item;

        for(int i = 0; i < player_island->objects.size(); i++) {
            island_object_item = player_island->objects[i]->item;
            player_object_on_island_collision = collision(event, island_object_item);
            if (player_object_on_island_collision)
                break;
        }

        if (!player_object_on_island_collision && player_on_island) {
            for(int i = 0; i < islands.size(); i++) {
                islands[i]->move_island(event);
            }
        }
    }
}

bool PlayerCharacter::collision(QKeyEvent *event, QGraphicsPixmapItem *item, bool ContainsItemShape) {
    int x = this->x();
    int y = this->y();

    int pixels_to_move_x = MovingSpeed::x_speed + 1;
    int pixels_to_move_y = MovingSpeed::y_speed + 1;

    if (event->key() == Qt::Key_A) {
        player_item->setPos(x - pixels_to_move_x, y);
    }
    else if (event->key() == Qt::Key_D) {
        player_item->setPos(x + pixels_to_move_x, y);
    }
    else if (event->key() == Qt::Key_W) {
        player_item->setPos(x, y - pixels_to_move_y);
    }
    else if (event->key() == Qt::Key_S) {
        player_item->setPos(x, y + pixels_to_move_y);
    }

    if (ContainsItemShape) {
        if (player_item->collidesWithItem(item, Qt::ContainsItemShape)) {
            player_item->setPos(x, y);
            return true;
        }
    }
    else {
        if (player_item->collidesWithItem(item)) {
            player_item->setPos(x, y);
            return true;
        }
    }
    player_item->setPos(x, y);
    return false;
}

