#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include <QGraphicsPixmapItem>

class InteractiveObject : public QGraphicsPixmapItem
{
public:
    InteractiveObject();

    QPixmap img;
    QGraphicsPixmapItem *item;
};

#endif // INTERACTIVEOBJECT_H
