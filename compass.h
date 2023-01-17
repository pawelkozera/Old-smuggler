#ifndef COMPASS_H
#define COMPASS_H

#include <QImage>
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include "playerplane.h"
#include "island.h"


///Klasa kompasu
class Compass
{
public:
    Compass();
    /*!Funkcja pobiera wskaźnik na gracza i wyspę; zwraca dystans do wyspy docelowej*/
    double caluclateDistance(PlayerPlane *player, Island *island);

    QImage compassImg;
    QImage arrowImg;
    QGraphicsPixmapItem *compassItem;
    QGraphicsPixmapItem *arroItem;
    qreal prevoious_distance;

};

#endif // COMPASS_H
