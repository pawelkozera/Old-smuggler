#include "compass.h"

/*!Konstruktor wyglądu, cech kompasu*/
Compass::Compass()
{
    compassImg.load("../smuggler/assets/compass/navigate.png");
    arrowImg.load("../smuggler/assets/compass/arrow.png");
    compassItem=new QGraphicsPixmapItem(QPixmap::fromImage(compassImg));
    arroItem=new QGraphicsPixmapItem(QPixmap::fromImage(arrowImg));
    compassItem->setPos(1270, 25);
    compassItem->setScale(0.8);
    arroItem->setPos(1080,-165);
    arroItem->setScale(0.1);
    compassItem->hide();
    arroItem->hide();
    prevoious_distance=1000000000;
    QPointF center_point(arroItem->boundingRect().width()/2,arroItem->boundingRect().height()/2);
    arroItem->setTransformOriginPoint(center_point);
}

/*!Funkcja sprawdzająca dystans do wyspy docelowej*/
double Compass::caluclateDistance(PlayerPlane *player, Island *island)
{
    double distance=QLineF(player->item->pos(), island->island_item->pos()).length();

    return distance;
}
