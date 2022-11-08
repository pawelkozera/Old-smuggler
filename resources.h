#ifndef RESOURCES_H
#define RESOURCES_H

#include "interactiveobject.h"
#include "settings.h"


class Resources : public InteractiveObject
{
public:
    Resources(QString img_name, Settings *settings);


    QPixmap alert_img;
    QGraphicsPixmapItem *alert_item;
    QGraphicsRectItem *filling;

    void show_text();
    void add();
};

#endif // RESOURCES_H
