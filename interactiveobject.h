#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include "alert.h"
#include <QGraphicsItem>
#include <QPainter>


///Klasa interaktywnych obiektów
class InteractiveObject
{
public:
    InteractiveObject(QString img_name, Alert *alert, QString alert_img);

    QPixmap img;
    QGraphicsPixmapItem *item;
    Alert *alert;
    QPixmap alert_img;
    bool cargo_alert;
    bool fuel_alert;

    /*!Funkcja pobiera parametry pozycji obiektu; zwraca nic*/
    void move_object(long double x, long double y);
    /*!Funkcja wirtualna pobiera ilość; zwraca nic*/
    virtual void show_alert(int amount);
    /*!Funkcja wirtualna pobiera nic; zwraca nic*/
    virtual void hide_alert();
    /*!Funkcja pobiera nic; zwraca nic*/
    int virtual max_amount_of_cargo();
    /*!Funkcja pobiera nic; zwraca 0 cargo*/
    int virtual max_amount_of_fuel();
    /*!Funkcja pobiera nic; zwraca 0 paliwa*/
};

#endif // INTERACTIVEOBJECT_H
