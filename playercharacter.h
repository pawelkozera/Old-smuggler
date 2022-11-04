#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "island.h"

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
    QGraphicsPixmapItem *player_item;


    void player_animation(QKeyEvent *event);
    void change_character_img();
    void change_current_index(int max_index, int min_index);
    void collision_on_island(QKeyEvent *event, std::vector<Island *> islands);
    bool collision(QKeyEvent *event, QGraphicsPixmapItem *item, bool ContainsItemShape = false);
};

#endif // PLAYERCHARACTER_H
