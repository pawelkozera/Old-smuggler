#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWidget>

class Map : public QWidget
{
public:
    Map(int width, int height);

    QPixmap map_texture;
    QRect window_rect;

    QGraphicsPixmapItem* add_map_to_scene(QGraphicsScene *Scene);
};

#endif // MAP_H
