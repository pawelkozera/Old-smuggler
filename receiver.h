#ifndef RECEIVER_H
#define RECEIVER_H

#include "interactiveobject.h"

class Receiver : public InteractiveObject
{
public:
    Receiver(QString img_name, Alert *alert, QString alert_img_name);

    QPixmap alert_img_no_cargo;

    void show_alert(int cargo);
    void hide_alert();
};

#endif // RECEIVER_H
