#ifndef WIND_H
#define WIND_H

#include <QVector2D>
#include <cstdlib>
#include <QImage>
#include <QGraphicsPixmapItem>


///Klasa wiatru
class Wind
{
public:
    Wind();
    /*!Funkcja pobiera nic; zwraca nic*/
    void UpdateWindDirection();
    /*!Funkcja pobiera nic; zwraca nic*/
    void UpdateWindStrength();
    /*!Funkcja pobiera nic; zwraca nic*/
    void UpdateArrow();
    /*!Funkcja pobiera nic; zwraca kierunek wiatru*/
    QVector2D GetWindDirection() const;
    /*!Funkcja pobiera nic; zwraca moc wiatru*/
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
