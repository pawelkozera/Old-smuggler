#include "map.h"

#include <QGraphicsScene>
#include <iostream>
#include <QGraphicsView>
#include <QGridLayout>

Map::Map()
{
    map_texture.load("C:/Users/admin/Desktop/projektc++/smuggler/background.png");
}

void Map::add_map_to_scene(QGraphicsScene *Scene) {
    Scene->addPixmap(this->map_texture);
}
