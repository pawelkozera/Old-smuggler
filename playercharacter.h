#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "island.h"
#include "interactiveobject.h"

#include <QPainter>
#include <QGraphicsItem>
#include <vector>


class PlayerCharacter
{
public:
    PlayerCharacter();

    std::vector<QPixmap> player_imgs;
    int current_index_of_player_img;
    int delay_animation_counter;
    const int delay_animation = 7;
    QGraphicsPixmapItem *player_item;


    void player_animation(QKeyEvent *event);
    void change_character_img(int index = -1);
    void change_current_index(int max_index, int min_index);
    Island* player_on_island(QKeyEvent *event, std::vector<Island *> islands);
    InteractiveObject* collision_with_island_objects(QKeyEvent *event, Island* player_island);
    bool collision(QKeyEvent *event, QGraphicsPixmapItem *item, bool ContainsItemShape = false);
};

#endif // PLAYERCHARACTER_H
