#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "island.h"
#include "playercharacter.h"
#include "playerplane.h"
#include "interactiveobject.h"

#include <vector>
#include <QGraphicsRectItem>


class EventHandler : public QGraphicsRectItem
{
public:
    EventHandler(std::vector<Island *> islands,
                 PlayerCharacter *player_character,
                 PlayerPlane *player_plane);

    bool player_character_events = true;
    bool collision_with_plane = false;
    bool collision_with_island_borders = false;

    std::vector<Island *> islands;
    Island *player_island;
    InteractiveObject *object_collided;

    PlayerCharacter *player_character;
    PlayerPlane *player_plane;

    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // EVENTHANDLER_H
