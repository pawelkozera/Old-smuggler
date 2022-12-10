#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "island.h"
#include "map.h"
#include "playercharacter.h"
#include "playerplane.h"
#include "settings.h"
#include "sounds.h"
#include "interface.h"

#include <vector>
#include <QGraphicsRectItem>
#include <QTimer>


class EventHandler : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    EventHandler(std::vector<Island *> islands,
                 PlayerCharacter *player_character,
                 PlayerPlane *player_plane,
                 Settings *settings,
                 Sounds *sounds,
                 Interface *interface);

    QTimer *timer;

    bool player_character_events;
    bool collision_with_plane;
    bool collision_with_island_borders;

    std::vector<Island *> islands;
    Island *player_island;
    InteractiveObject *interactive_object_collided;
    Settings *settings;
    PlayerCharacter *player_character;
    PlayerPlane *player_plane;
    Sounds *sounds;
    Interface *interface;
    Map *map;

    std::pair<int, int> player_last_position;

    virtual void keyPressEvent(QKeyEvent *event);
    void entering_plane_event();
    void character_on_island_event(QKeyEvent *event);
    void character_moving(QKeyEvent *event);
    void leaving_plane_event();
    void plane_events(QKeyEvent *event);
    void set_interactive_object_collided(InteractiveObject *object_collided_bufor);
    void add_resources_to_plane(QKeyEvent *event);
    void select_target_island();

public slots:
    void my_timer_slot();
};

#endif // EVENTHANDLER_H
