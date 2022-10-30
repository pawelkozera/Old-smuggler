#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "island.h"

#include <vector>

#include <QGraphicsRectItem>

class EventHandler : public QGraphicsRectItem
{
public:
    EventHandler(std::vector<Island *> islands);

    std::vector<Island *> islands;

    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // EVENTHANDLER_H
