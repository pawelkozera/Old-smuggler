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

    void move_object(int x, int y);
    virtual void show_text();
    virtual void add();
};

#endif // INTERACTIVEOBJECT_H
