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
        power->setPlainText(QString::number(MovingSpeed::current_power / MovingSpeed::division_power_factor_index));
        speed->setPlainText(QString::number(round(MovingSpeed::current_speed / 6)));
    }
}
