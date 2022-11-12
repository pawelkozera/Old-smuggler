#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "playercharacter.h"

#include <QGraphicsItem>

class PlayerPlane
{
public:
    PlayerPlane();

    std::vector<QPixmap> imgs;
    int current_index_of_plane_img;
    QGraphicsPixmapItem *item;
    float rotation_degree;
    int delay_animation_counter;
    int delay_animation;
    int fuel;
    int cargo;

    void animation();
    void simple_movement_event(QKeyEvent *event, int x_speed = MovingSpeed::x_speed, int y_speed = MovingSpeed::y_speed);
    void simple_movement(int x_speed, int y_speed);
    std::pair<int, int> center_plane_on_screen(PlayerCharacter *player_character);
    std::pair<int, int> leave_plane(PlayerCharacter *player_character);
    Island* plane_on_island(QKeyEvent *event, std::vector<Island *> islands);
    void change_power(QKeyEvent *event);
    void rotate(QKeyEvent *event);
    void set_up_current_speed();
    void calculate_x_y_speed();
    void add_cargo(int max_cargo);
    void remove_cargo();
    void add_fuel(int max_fuel);
    void remove_fuel();
};

#endif // PLAYERPLANE_H
