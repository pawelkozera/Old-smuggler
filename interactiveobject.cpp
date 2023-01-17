#include "interactiveobject.h"

#include <QPoint>

/*!Konstruktor wyglądu i cech interaktywnych obiektów*/
InteractiveObject::InteractiveObject(QString img_name, Alert *alert, QString alert_img_name) {
    img.load("../smuggler/assets/objects/" + img_name);
    this->alert = alert;
    this->alert_img.load("../smuggler/assets/objects/" + alert_img_name);;
    cargo_alert = false;
    fuel_alert = false;

    int max_amount_of_cargo = 0;
}

/*!Funkcja "stania" obiektów względem gracza*/
void InteractiveObject::move_object(long double x, long double y) {
    long double current_x = item->x();
    long double current_y = item->y();
    item->setPos(current_x + x, current_y + y);
}

/*!Funkcja wyświetlania*/
void InteractiveObject::show_alert(int amount) {}
/*!Funkcja ukrywania*/
void InteractiveObject::hide_alert() {}
/*!Funkcja zwracająca 0 cargo*/
int InteractiveObject::max_amount_of_cargo( ){return 0;};
/*!Funkcja zwracająca 0 paliwa*/
int InteractiveObject::max_amount_of_fuel(){return 0;};
