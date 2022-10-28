#include "map.h"

#include <QGraphicsScene>
#include <iostream>
#include <QGraphicsView>
#include <QGridLayout>
#include <QGraphicsPixmapItem>

Map::Map()
{
    map_texture.load("../smuggler/assets/map/background.png");
}

QGraphicsPixmapItem* Map::add_map_to_scene(QGraphicsScene *Scene) {
    QGraphicsPixmapItem *p;
    p = Scene->addPixmap(this->map_texture);
    return p;
}
