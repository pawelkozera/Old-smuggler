#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>

class Map
{
public:
    Map();

    QPixmap map_texture;

    void add_map_to_scene(QGraphicsScene *Scene);
};

#endif // MAP_H
