#include "map.h"

#include <QGraphicsScene>
#include <iostream>
#include <QGraphicsView>
#include <QGridLayout>
#include <QGraphicsPixmapItem>

Map::Map(int width, int height)
{
    map_texture.load("../smuggler/assets/map/background.png");
    window_rect = QRect(0, 0, width, height);
}

QGraphicsPixmapItem* Map::add_map_to_scene(QGraphicsScene *Scene) {
    QGraphicsPixmapItem *p;
    p = Scene->addPixmap(this->map_texture);
    return p;
}
