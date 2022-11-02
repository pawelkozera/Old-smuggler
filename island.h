#ifndef ISLAND_H
#define ISLAND_H

#include <QPainter>
#include <QGraphicsItem>


class Island : public QGraphicsPixmapItem
{
public:
    Island(int x, int y, QString img_name);
    bool is_visible;
    QRect borders;
    QPixmap island_img;
    QGraphicsPixmapItem *island_item;
    int last_position;
    QString  last_direction;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    void move_island(QKeyEvent *event);
    bool collision_with_player(QGraphicsPixmapItem *player_character);
    void set_last_position(int position, QString direction);
    void move_to_the_last_position();
};

#endif // ISLAND_H
