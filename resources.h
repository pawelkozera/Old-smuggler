#ifndef RESOURCES_H
#define RESOURCES_H

#include "interactiveobject.h"

///Klasa zasobów
class Resources : public InteractiveObject
{
public:
    Resources(QString img_name, Alert *alert, QString alert_img_name);

    /*!Funkcja pobiera ilość cargo; zwraca nic*/
    void show_alert(int cargo);
    /*!Funkcja pobiera nic; zwraca nic*/
    void hide_alert();
    /*!Funkcja pobiera; zwraca maksymalną wartość cargo = 40*/
    int max_amount_of_cargo();
};

#endif // RESOURCES_H
