#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "island.h"
#include "playercharacter.h"

#include <vector>
#include <QGraphicsRectItem>


class EventHandler : public QGraphicsRectItem
{
public:
    EventHandler(std::vector<Island *> islands,
                 PlayerCharacter *player_character);

    std::vector<Island *> islands;
    PlayerCharacter *player_character;

    virtual void keyPressEvent(QKeyEvent *event);
    void island_collision(QKeyEvent *event);
};

#endif // EVENTHANDLER_H
