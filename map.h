#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWidget>

class Map : public QWidget
{
public:
    Map();

    QPixmap map_texture;

    QGraphicsPixmapItem* add_map_to_scene(QGraphicsScene *Scene);
};

#endif // MAP_H
