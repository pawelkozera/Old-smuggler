#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "island.h"
#include "map.h"
#include "playercharacter.h"
#include "playerplane.h"
#include "settings.h"
#include "sounds.h"
#include "interface.h"
#include "menu.h"
#include "ui_mainwindow.h"
#include "wind.h"
#include "compass.h"
#include "score.h"
#include "hallOfFame.h"
#include "cloud.h"
#include "enemyplane.h"

#include <vector>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QThread>
#include <QLine>


///Klasa Obsługi zdarzeń
class EventHandler : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    EventHandler(std::vector<Island *> islands,
                 PlayerCharacter *player_character,
                 PlayerPlane *player_plane,
                 Settings *settings,
                 Sounds *sounds,
                 Interface *interface,
                 Menu *menu,
                 Ui::MainWindow *ui,
                 QGraphicsScene *scene,
                 Wind *wind,
                 Compass *compass,
                 HallOfFame *hallOfFame,
                 QList<Cloud*> clouds,
                 std::vector<EnemyPlane *> enemyPlanes);

    QTimer *main_timer;
    QTimer *timer2;
    QTimer *timerCloud;
    QTimer *timerGameOver;
    QTimer *waitForCrash;

    bool player_character_events;
    bool collision_with_plane;
    bool collision_with_island_borders;

    int ms;
    int fps;

    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;

    std::vector<Island *> islands;
    Island *player_island, *target_island;
    InteractiveObject *interactive_object_collided;
    Settings *settings;
    PlayerCharacter *player_character;
    PlayerPlane *player_plane;
    Sounds *sounds;
    Interface *interface;
    Map *map;
    Menu *menu;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Wind *wind;
    QGraphicsPixmapItem *cargo_item;
    Compass *compass;
    Score *score;
    HallOfFame *hallOfFame;
    QList<Cloud*> clouds;
    QGraphicsScene *tmpScene;
    std::vector<EnemyPlane *> enemyPlanes;

    std::pair<int, int> player_last_position;

    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    virtual void keyPressEvent(QKeyEvent *event);
    /*!Funkcja pobiera nic; zwraca nic*/
    void entering_plane_event();
    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    void character_on_island_event(QKeyEvent *event);
    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    void character_moving(QKeyEvent *event);
    /*!Funkcja pobiera; zwraca nic*/
    void leaving_plane_event();
    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    void plane_events(QKeyEvent *event);
    /*!Funkcja pobiera wskaźnik obiektu zderzającego; zwraca nic*/
    void set_interactive_object_collided(InteractiveObject *object_collided_bufor);
    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    void interactive_objects_handler(QKeyEvent *event);
    /*!Funkcja pobiera wskaźnik indeksu poprzedniego celu; zwraca nic*/
    void select_target_island(Island const *previous_target_index = NULL);
    /*!Funkcja pobiera; zwraca nic*/
    void drop_cago();
    /*!Funkcja pobiera nic; zwraca nic*/
    void cargo_item_update();
    /*!Funkcja pobiera nic; zwraca nic*/
    void UpdateArrowDirection();
    /*!Funkcja pobiera nic; zwraca nic*/
    void setArrow();
    /*!Funkcja pobiera nic; zwraca nic*/
    void moveCloud();
    /*!Funkcja pobiera nic; zwraca nic*/
    void handleReturnPressed();
    /*!Funkcja pobiera nic; zwraca nic*/
    void GameOver();
    /*!Funkcja pobiera nic; zwraca nic*/
    void wait();
    /*!Funkcja pobiera nic; zwraca nic*/
    void reset_game();
    /*!Funkcja pobiera nic; zwraca nic*/
    void fuel_run_out();

public slots:
    void main_events();

};

#endif // EVENTHANDLER_H
