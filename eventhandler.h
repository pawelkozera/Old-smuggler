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

#include <vector>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QThread>
#include <QLine>


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
                 QList<Cloud*> clouds);

    QTimer *timer;
    QTimer *timer2;
    QTimer *timerCloud;

    bool player_character_events;
    bool collision_with_plane;
    bool collision_with_island_borders;

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

    std::pair<int, int> player_last_position;

    virtual void keyPressEvent(QKeyEvent *event);
    void entering_plane_event();
    void character_on_island_event(QKeyEvent *event);
    void character_moving(QKeyEvent *event);
    void leaving_plane_event();
    void plane_events(QKeyEvent *event);
    void set_interactive_object_collided(InteractiveObject *object_collided_bufor);
    void interactive_objects_handler(QKeyEvent *event);
    void select_target_island(Island const *previous_target_index = NULL);
    void drop_cago();
    void cargo_item_update();
    void UpdateArrowDirection();
    void setArrow();
    void moveCloud();


public slots:
    void my_timer_slot();


};

#endif // EVENTHANDLER_H
