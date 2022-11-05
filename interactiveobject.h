#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include <QGraphicsItem>
#include <QPainter>

class InteractiveObject : public QGraphicsPixmapItem
{
public:
    InteractiveObject(QString img_name);

    QPixmap img;
    QGraphicsPixmapItem *item;
    QGraphicsTextItem *text;

    void move_object(int x, int y);
};

#endif // INTERACTIVEOBJECT_H
