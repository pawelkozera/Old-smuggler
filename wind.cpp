#include "wind.h"
#include <cmath>

/*!Konstruktor cech wiatru i ładujący ikonkę wiatru*/
Wind::Wind()
{
    direction = QVector2D(0,0);
    strength = 0.4;
    windSock.load("../smuggler/assets/wind/windsock.png");
    arrow.load("../smuggler/assets/wind/arrow.png");
    WindSock=new QGraphicsPixmapItem(QPixmap::fromImage(windSock));
    WindSock->setPos(1270, 670);
    WindSock->hide();
    WindSock->setScale(0.2);
    DirectionPixmap=new QGraphicsPixmapItem(QPixmap::fromImage(arrow));
    DirectionPixmap->setPos(1080, 495);
    DirectionPixmap->setScale(0.1);
    DirectionPixmap->setTransformOriginPoint(QPointF(DirectionPixmap->boundingRect().width() / 2, DirectionPixmap->boundingRect().height() / 2));
    DirectionPixmap->hide();
    srand(time(NULL));
}

/*!Funkcja aktualizująca kierunek wiatru*/
void Wind::UpdateWindDirection()
{
    int wind_direction_degrees = rand() % 360;
    direction = QVector2D(cos(wind_direction_degrees), sin(wind_direction_degrees));
    UpdateArrow();
}

/*!Funkcja aktualizująca siłe wiatru do 0.4*/
void Wind::UpdateWindStrength()
{
    strength=0.4;
}

/*!Funkcja aktualizująca pozycję strzałki wiatru*/
void Wind::UpdateArrow()
{
    DirectionPixmap->setRotation(0);
    QVector2D wind_direction=GetWindDirection();
    qreal wind_angle = qAtan2(wind_direction.y(), wind_direction.x());
    wind_angle = wind_angle * 180.0 / M_PI;
    DirectionPixmap->setRotation(wind_angle);
}

/*!Funkcja zwracająca kierunek wiatru*/
QVector2D Wind::GetWindDirection() const
{
    return direction;
}

/*!Funkcja zwracająca siłę wiatru*/
float Wind::GetWindStrength() const
{
    return 0.4;
}
