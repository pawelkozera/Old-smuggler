#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include <QGraphicsPixmapItem>

class InteractiveObject : public QGraphicsPixmapItem
{
public:
    InteractiveObject(QString img_name);

    QPixmap img;
    QGraphicsPixmapItem *item;

    void move_object(int x, int y);
};

#endif // INTERACTIVEOBJECT_H
