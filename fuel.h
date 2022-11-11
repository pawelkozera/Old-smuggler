#ifndef FUEL_H
#define FUEL_H

#include "interactiveobject.h"


class Fuel : public InteractiveObject
{
public:
    Fuel(QString img_name, Alert *alert, QString alert_img_name);

    void show_alert(int fuel);
    void hide_alert();
    int max_amount_of_fuel();
};

#endif // FUEL_H
