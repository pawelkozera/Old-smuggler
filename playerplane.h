#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "playercharacter.h"
#include "wind.h"
#include "cloud.h"

#include <QGraphicsItem>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QTimer>
#include <QObject>
#include <QLineF>
#include <QLine>

class PlayerPlane: public QObject
{
    Q_OBJECT
public:
    PlayerPlane(Wind *wind, QList<Cloud*> clouds);

    std::vector<QPixmap> imgs;
    int current_index_of_plane_img;
    QGraphicsPixmapItem *item;
    float rotation_degree;
    int delay_animation_counter;
    int delay_animation;
    float fuel;
    int cargo;
    Wind *wind;
    Cloud *cloud;
    QVector2D plane_speed;
    void UpdateCrashAppearance();
    QTimer* crash_timer;
    QGraphicsTextItem *text_drop;
    QGraphicsPixmapItem *cargo_item;
    int x, y;
    QList<Cloud*> clouds;

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
    void fuel_usage();
    void crash();
    bool IsOnTargetIsland(std::vector<Island *> islands);
    void drop_cargo();
    void set_text_drop();
    void caluculate_x_y();
};

#endif // PLAYERPLANE_H
