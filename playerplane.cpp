#include "playerplane.h"
#include "movingspeed.h"

#include <QKeyEvent>
#include <QDebug>

PlayerPlane::PlayerPlane(int x, int y) {
    current_index_of_plane_img = 0;

    QPixmap plane_img;
    for (int i = 1; i <= 3; i++) {
        QString location = "../smuggler/assets/player_plane/plane" + QString::number(i) + QString(".png");
        plane_img.load(location);
        imgs.push_back(plane_img);
    }

    setPos(x, y);
}

std::pair<int, int> PlayerPlane::center_plane_on_screen(PlayerCharacter *player_character) {
    std::pair<int, int> pixels_to_move;
    pixels_to_move.first = player_character->player_item->x() - item->x() - imgs[0].width()/2;
    pixels_to_move.second = player_character->player_item->y() - item->y() - imgs[0].height()/2;

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
