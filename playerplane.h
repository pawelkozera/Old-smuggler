#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "playercharacter.h"

#include <QGraphicsItem>

class PlayerPlane : public QGraphicsPixmapItem
{
public:
    PlayerPlane(int x, int y);

    std::vector<QPixmap> imgs;
    int current_index_of_plane_img;
    QGraphicsPixmapItem *item;

    void simple_movement_event(QKeyEvent *event, int x_speed = MovingSpeed::x_speed, int y_speed = MovingSpeed::y_speed);
    void simple_movement(int x_speed, int y_speed);
    std::pair<int, int> center_plane_on_screen(PlayerCharacter *player_character);
};

#endif // PLAYERPLANE_H
