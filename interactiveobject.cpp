#include "interactiveobject.h"

#include <QPoint>

InteractiveObject::InteractiveObject(QString img_name, Alert *alert, QString alert_img_name) {
    img.load("../smuggler/assets/objects/" + img_name);
    this->alert = alert;
    this->alert_img.load("../smuggler/assets/objects/" + alert_img_name);;
    cargo_alert = false;

    int max_amount_of_cargo = 0;
}

void InteractiveObject::move_object(long double x, long double y) {
    long double current_x = item->x();
    long double current_y = item->y();
    item->setPos(current_x + x, current_y + y);
}

void InteractiveObject::show_alert(int amount) {}
void InteractiveObject::hide_alert() {}
int InteractiveObject::max_amount_of_cargo( ){return 0;};
int InteractiveObject::max_amount_of_fuel(){return 0;};
