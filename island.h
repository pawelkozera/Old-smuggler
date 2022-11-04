#ifndef ISLAND_H
#define ISLAND_H

#include "interactiveobject.h"

#include <QPainter>
#include <QGraphicsItem>


class Island : public QGraphicsPixmapItem
{
public:
    Island(QString img_name);
    bool is_visible;
    QPixmap island_img;
    QGraphicsPixmapItem *island_item;
    std::vector<InteractiveObject *> objects;

    void move_island(QKeyEvent *event);
    void move_objects_on_island(int x, int y);
};

#endif // ISLAND_H
