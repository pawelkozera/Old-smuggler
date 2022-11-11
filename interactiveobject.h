#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include "alert.h"
#include <QGraphicsItem>
#include <QPainter>

class InteractiveObject : public QGraphicsPixmapItem
{
public:
    InteractiveObject(QString img_name, Alert *alert, QString alert_img);

    QPixmap img;
    QGraphicsPixmapItem *item;
    Alert *alert;
    QPixmap alert_img;
    bool cargo_alert;

    void move_object(int x, int y);
    virtual void show_alert(int amount);
    virtual void hide_alert();
    int virtual max_amount_of_cargo();
    int virtual max_amount_of_fuel();
};

#endif // INTERACTIVEOBJECT_H
