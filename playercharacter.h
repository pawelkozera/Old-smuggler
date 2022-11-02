#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <QPainter>
#include <QGraphicsItem>
#include <vector>


class PlayerCharacter : public QGraphicsPixmapItem
{
public:
    PlayerCharacter(int x, int y);

    std::vector<QPixmap> player_imgs;
    int current_index_of_player_img;
    int delay_animation_counter;
    int delay_animation;
    QRect player_rect;
    QGraphicsPixmapItem *player_item;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    void player_animation(QKeyEvent *event);
};

#endif // PLAYERCHARACTER_H
