#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "island.h"
#include "playercharacter.h"
#include "playerplane.h"
#include "settings.h"

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
                 Settings *settings);
    QTimer *timer;

    bool player_character_events = true;
    bool collision_with_plane = false;
    bool collision_with_island_borders = false;

    std::vector<Island *> islands;
    Island *player_island;
    InteractiveObject *object_collided;
    Settings *settings;

    PlayerCharacter *player_character;
    PlayerPlane *player_plane;

    virtual void keyPressEvent(QKeyEvent *event);
    void entering_plane_event();
    void character_on_island_event(QKeyEvent *event);
    void character_moving(QKeyEvent *event);
    void leaving_plane_event();
    void plane_events(QKeyEvent *event);

public slots:
    void my_timer_slot();
};

#endif // EVENTHANDLER_H
