#ifndef ISLAND_H
#define ISLAND_H

#include <QPainter>
#include <QGraphicsItem>


class Island : public QGraphicsPixmapItem
{
public:
    Island(QString img_name);
    bool is_visible;
    QRect borders;
    QPixmap island_img;
    QGraphicsPixmapItem *island_item;

    void move_island(QKeyEvent *event);
    bool collision_with_player(QKeyEvent *event, QGraphicsPixmapItem *player_character);
};

#endif // ISLAND_H
