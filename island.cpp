#include "island.h"
#include "movingspeed.h"

#include <QDebug>
#include <QKeyEvent>


Island::Island(int x, int y, QString img_name) {

    is_visible = false;
    island_img.load("../smuggler/assets/map/" + img_name);
    borders = QRect(x, y, island_img.width(), island_img.height());
}

QRectF Island::boundingRect() const {
    // outer most edges
    return borders;
}

void Island::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //painter->drawPixmap(borders, island_img);
}

void Island::move_island(QKeyEvent *event) {
    int x_speed = MovingSpeed::x_speed;
    int y_speed = MovingSpeed::y_speed;
    int island_x = island_item->x();
    int island_y = island_item->y();

    if (event->key() == Qt::Key_A) {
        island_item->setPos(island_x + x_speed, island_y);
    }
    if (event->key() == Qt::Key_D) {
        island_item->setPos(island_x - x_speed, island_y);
    }
    if (event->key() == Qt::Key_W) {
        island_item->setPos(island_x, island_y + y_speed);
    }
    if (event->key() == Qt::Key_S) {
        island_item->setPos(island_x, island_y - y_speed);
    }
}

bool Island::collision_with_player(QKeyEvent *event, QGraphicsPixmapItem *player_character) {
    int x = player_character->x();
    int y = player_character->y();
    int pixels_to_move_x = MovingSpeed::x_speed;
    int pixels_to_move_y = MovingSpeed::y_speed;

    if (event->key() == Qt::Key_A) {
        player_character->setPos(x - pixels_to_move_x, y);
    }
    else if (event->key() == Qt::Key_D) {
        player_character->setPos(x + pixels_to_move_x, y);
    }
    else if (event->key() == Qt::Key_W) {
        player_character->setPos(x, y - pixels_to_move_y);
    }
    else if (event->key() == Qt::Key_S) {
        player_character->setPos(x, y + pixels_to_move_y);
    }

    if (player_character->collidesWithItem(island_item, Qt::ContainsItemShape)) {
        player_character->setPos(x, y);
        return true;
    }
    player_character->setPos(x, y);
    return false;
}
