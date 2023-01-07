#ifndef WIND_H
#define WIND_H

#include <QVector2D>
#include <cstdlib>
#include <QImage>
#include <QGraphicsPixmapItem>

class Wind
{
public:
    Wind();
    void UpdateWindDirection();
    void UpdateWindStrength();
    void UpdateArrow();
    QVector2D GetWindDirection() const;
    float GetWindStrength() const;

    QGraphicsPixmapItem *WindSock;
    QGraphicsPixmapItem *DirectionPixmap;

private:
    QVector2D direction;
    double strength;
    QImage windSock;
    QImage arrow;
};

#endif // WIND_H
