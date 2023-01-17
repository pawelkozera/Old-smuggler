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


///Klasa samolotu gracza
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
    int hp;
    bool tank_damaged;
    bool gameOver=false;
    double originalScale;

    /*!Funkcja pobiera nic; zwraca nic*/
    void animation();
    /*!Funkcja pobiera wskaźnik zdarzenia i parametry prędkości; zwraca nic*/
    void simple_movement_event(QKeyEvent *event, int x_speed = MovingSpeed::x_speed, int y_speed = MovingSpeed::y_speed);
    /*!Funkcja pobiera parametry prędkości; zwraca nic*/
    void simple_movement(int x_speed, int y_speed);
    /*!Funkcja pobiera wskaźnik gracza; zwraca nic*/
    std::pair<int, int> center_plane_on_screen(PlayerCharacter *player_character);
    /*!Funkcja pobiera wskaźnik gracza; zwraca nic*/
    std::pair<int, int> leave_plane(PlayerCharacter *player_character);
    /*!Funkcja pobiera wskaźnik zdarzenia i kontener vector wysp; zwraca nic*/
    Island* plane_on_island(QKeyEvent *event, std::vector<Island *> islands);
    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    void change_power(QKeyEvent *event);
    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    void rotate(QKeyEvent *event);
    /*!Funkcja pobiera nic; zwraca nic*/
    void set_up_current_speed();
    /*!Funkcja pobiera nic; zwraca nic*/
    void calculate_x_y_speed();
    /*!Funkcja pobiera maksymalną ilość cargo; zwraca nic*/
    void add_cargo(int max_cargo);
    /*!Funkcja pobiera nic; zwraca nic*/
    void remove_cargo();
    /*!Funkcja pobiera maksymalną ilość paliwa; zwraca nic*/
    void add_fuel(int max_fuel);
    /*!Funkcja pobiera nic; zwraca nic*/
    void remove_fuel();
    /*!Funkcja pobiera nic; zwraca nic*/
    void fuel_usage();
    /*!Funkcja pobiera nic; zwraca nic*/
    void crash();
    /*!Funkcja pobiera kontener vector wysp; zwraca true/false*/
    bool IsOnTargetIsland(std::vector<Island *> islands);
    /*!Funkcja pobiera wskaźnik wyspy; zwraca true/false*/
    bool IsOnIsland(Island *island);
    /*!Funkcja pobiera nic; zwraca nic*/
    void drop_cargo();
    /*!Funkcja pobiera nic; zwraca nic*/
    void set_text_drop();
    /*!Funkcja pobiera nic; zwraca nic*/
    void caluculate_x_y();
    /*!Funkcja pobiera nic; zwraca nic*/
    void restart();
};

#endif // PLAYERPLANE_H
