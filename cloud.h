#ifndef CLOUD_H
#define CLOUD_H

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QPixmap>
#include <QKeyEvent>
#include <QtMath>
#include <QList>

#include "movingspeed.h"


///Klasa Chmur
class Cloud : public QObject
{
    Q_OBJECT
public:
    Cloud(int x);
    /*!Funkcja pobiera wskaźnik zdarzenia; zwraca nic*/
    void move_cloud_event(QKeyEvent *event);
    /*!Funkcja pobiera parametry prędkości; zwraca nic*/
    void move_cloud(long double x_speed, long double y_speed);

    QGraphicsPixmapItem *cloudPixmap;
};

#endif // CLOUD_H
