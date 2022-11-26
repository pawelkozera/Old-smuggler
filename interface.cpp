#include "interface.h"
#include "movingspeed.h"

Interface::Interface() {
    speedometer_img.load("../smuggler/assets/interface/speedometer.png");
    blank_img.load("../smuggler/assets/interface/blank.png");
}

void Interface::draw_speedometer(int window_height, bool blank) {
    if (blank) {
        speedometer_item->setPixmap(blank_img);
        power->setPlainText("");
        speed->setPlainText("");
    }
    else {
        speedometer_item->setPixmap(speedometer_img);
        int gear = (MovingSpeed::current_power / MovingSpeed::division_power_factor_index) - 1;

        if (gear >= 0)
            power->setPlainText(QString::number(gear));
        else
            power->setPlainText("R");

        speed->setPlainText(QString::number(abs(round(MovingSpeed::current_speed / 6))));
    }
}
