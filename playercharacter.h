#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "island.h"
#include "interactiveobject.h"

#include <QPainter>
#include <QGraphicsItem>
#include <vector>


///Klasa
class PlayerCharacter
{
public:
    PlayerCharacter();

    std::vector<QPixmap> player_imgs;
    int current_index_of_player_img;
    int delay_animation_counter;
    const int delay_animation = 7;
    QGraphicsPixmapItem *player_item;

    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    void player_animation(QKeyEvent *event);
    /*!Funkcja pobiera indeks i ustawia go na -1; zwraca nic*/
    void change_character_img(int index = -1);
    /*!Funkcja pobiera maksymalny indeks i minimalny indeks; zwraca nic*/
    void change_current_index(int max_index, int min_index);
    /*!Funkcja pobiera wskaźnik zdarzenia i kontener vector wysp; zwraca NULL*/
    Island* player_on_island(QKeyEvent *event, std::vector<Island *> islands);
    /*!Funkcja pobiera wskaźnik zdarzenia i kontener vector wysp; zwraca NULL*/
    InteractiveObject* collision_with_island_objects(QKeyEvent *event, Island* player_island);
    /*!Funkcja pobiera wskaźnik zdarzenia, wskaźnik przedmiotu i ustawia zmienną ContainsItemSahpe = false; zwraca tue/false*/
    bool collision(QKeyEvent *event, QGraphicsPixmapItem *item, bool ContainsItemShape = false);
};

#endif // PLAYERCHARACTER_H
