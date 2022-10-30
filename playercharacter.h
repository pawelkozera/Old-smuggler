#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <QPainter>
#include <QGraphicsItem>
#include <vector>


class PlayerCharacter : public QGraphicsRectItem
{
public:
    PlayerCharacter(int screen_width, int screen_height);

    std::vector<QPixmap> player_imgs;
    int current_index_of_player_img;
    int delay_animation_counter;
    int delay_animation;
    QRect player_rect;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    void player_animation(QKeyEvent *event);
};

#endif // PLAYERCHARACTER_H
