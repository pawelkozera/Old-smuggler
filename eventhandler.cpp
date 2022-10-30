#include "eventhandler.h"

#include <QDebug>
#include <QKeyEvent>

EventHandler::EventHandler(std::vector<Island *> islands) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    this->islands = islands;
}

void EventHandler::keyPressEvent(QKeyEvent *event) {
    for(int i = 0; i < islands.size(); i++) {
        islands[i]->move_island(event);
    }

    update();
}
