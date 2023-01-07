#ifndef COMPASS_H
#define COMPASS_H

#include <QImage>
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include "playerplane.h"
#include "island.h"


class Compass
{
public:
    Compass();
    double caluclateDistance(PlayerPlane *player, Island *island);

    QImage compassImg;
    QImage arrowImg;
    QGraphicsPixmapItem *compassItem;
    QGraphicsPixmapItem *arroItem;
    qreal prevoious_distance;

};

#endif // COMPASS_H
