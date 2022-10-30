#include "map.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>

Map::Map(int width, int height) {
    map_texture.load("../smuggler/assets/map/background.png");
    window_rect = QRect(0, 0, width, height);
}

QRectF Map::boundingRect() const {
    // outer most edges
    return window_rect;
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(window_rect, map_texture);
}

void Map::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        qDebug() << "m";
    }
    if (event->key() == Qt::Key_D) {
        qDebug() << "m";
    }
    if (event->key() == Qt::Key_W) {
        qDebug() << "m";
    }
    if (event->key() == Qt::Key_S) {
        qDebug() << "m";
    }
    update();
}
