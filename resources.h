#ifndef RESOURCES_H
#define RESOURCES_H

#include "interactiveobject.h"
#include "settings.h"


class Resources : public InteractiveObject
{
public:
    Resources(QString img_name, Settings *settings, Alert *alert, QString alert_img_name);

    void show_alert(int cargo);
    void hide_alert();
    int max_amount_of_cargo();
};

#endif // RESOURCES_H
