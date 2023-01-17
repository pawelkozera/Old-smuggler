#ifndef FUEL_H
#define FUEL_H

#include "interactiveobject.h"


///Klasa paliwa
class Fuel : public InteractiveObject
{
public:
    Fuel(QString img_name, Alert *alert, QString alert_img_name);

    /*!Funkcja pobiera ilość paliwa; zwraca nic*/
    void show_alert(int fuel);
    /*!Funkcja pobiera nic; zwraca nic*/
    void hide_alert();
    /*!Funkcja pobiera nic; zwraca ilość paliwa*/
    int max_amount_of_fuel();
};

#endif // FUEL_H
