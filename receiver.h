#ifndef RECEIVER_H
#define RECEIVER_H

#include "interactiveobject.h"


///Klasa odbiorcy
class Receiver : public InteractiveObject
{
public:
    Receiver(QString img_name, Alert *alert, QString alert_img_name);

    QPixmap alert_img_no_cargo;

    /*!Funkcja pobiera ilość cargo; zwraca nic*/
    void show_alert(int cargo);
    /*!Funkcja pobiera nic; zwraca nic*/
    void hide_alert();
};

#endif // RECEIVER_H
