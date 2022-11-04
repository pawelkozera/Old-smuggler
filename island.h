#ifndef ISLAND_H
#define ISLAND_H

#include <QPainter>
#include <QGraphicsItem>


class Island : public QGraphicsPixmapItem
{
public:
    Island(QString img_name);
    bool is_visible;
    QPixmap island_img;
    QGraphicsPixmapItem *island_item;

    void move_island(QKeyEvent *event);
};

#endif // ISLAND_H
