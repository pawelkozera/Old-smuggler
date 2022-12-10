#include "interface.h"
#include "movingspeed.h"

Interface::Interface() {
    cockpit_img.load("../smuggler/assets/interface/cockpit.png");
    map_img.load("../smuggler/assets/interface/map.png");

    map_img = map_img.scaled(1408, 792);
}

void Interface::draw_cockpit(int window_height, PlayerPlane const *player_plane) {
    if (cockpit_item->isVisible()) {
        int gear = (MovingSpeed::current_power / MovingSpeed::division_power_factor_index) - 1;

        if (gear >= 0)
            power->setPlainText(QString::number(gear));
        else
            power->setPlainText("R");

        speed->setPlainText(QString::number(abs(round(MovingSpeed::current_speed / 6))));

        if (player_plane->fuel <= 0)
            fuel->setPlainText("0");
        else
            fuel->setPlainText(QString::number(round(player_plane->fuel)));
        cargo->setPlainText(QString::number(player_plane->cargo));
    }
    else {
        power->setPlainText("");
        speed->setPlainText("");
        fuel->setPlainText("");
        cargo->setPlainText("");
    }
}

void Interface::draw_map() {
    if (map_item->isVisible()) {
        map_item->hide();
    }
    else {
        map_item->show();
    }
}
