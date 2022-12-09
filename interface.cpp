#include "interface.h"
#include "movingspeed.h"

Interface::Interface() {
    speedometer_img.load("../smuggler/assets/interface/speedometer.png");
    map_img.load("../smuggler/assets/interface/map.png");

    map_img = map_img.scaled(1408, 792);
}

void Interface::draw_speedometer(int window_height) {
    if (speedometer_item->isVisible()) {
        int gear = (MovingSpeed::current_power / MovingSpeed::division_power_factor_index) - 1;

        if (gear >= 0)
            power->setPlainText(QString::number(gear));
        else
            power->setPlainText("R");

        speed->setPlainText(QString::number(abs(round(MovingSpeed::current_speed / 6))));
    }
    else {
        power->setPlainText("");
        speed->setPlainText("");
    }
}

void Interface::draw_map() {
    if (map_item->isVisible())
        map_item->hide();
    else
        map_item->show();
}
