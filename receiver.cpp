#include "receiver.h"

/*!Konstruktor odbierający, ładującu obrazek braku cargo*/
Receiver::Receiver(QString img_name, Alert *alert, QString alert_img_name) : InteractiveObject(img_name, alert, alert_img_name) {
    fuel_alert = false;
    cargo_alert = false;

    alert_img_no_cargo.load("../smuggler/assets/objects/alert_receiver_no_cargo.png");
}

/*!Funkcja wyświetlająca alert o braku cargo*/
void Receiver::show_alert(int cargo) {
    int x = item->x();
    int y = item->y() - 100;

    alert->item->setPos(x, y);

    if (cargo > 0)
        alert->change_img(alert_img);
    else
        alert->change_img(alert_img_no_cargo);
}

/*!Funkcja chowająca alert*/
void Receiver::hide_alert() {
    alert->change_img(alert->img);
}
