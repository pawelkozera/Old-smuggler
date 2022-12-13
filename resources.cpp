#include "resources.h"

Resources::Resources(QString img_name, Alert *alert, QString alert_img_name) : InteractiveObject(img_name, alert, alert_img_name) {
    cargo_alert = true;
}

void Resources::show_alert(int cargo) {
    int x = item->x();
    int y = item->y() + 200;
    int bar_x = 47;
    int bar_y = 50;
    float percentage = static_cast<float> (cargo)/max_amount_of_cargo();
    int pixels_for_one_chunk = round(percentage*alert->img_bar.width());

    alert->item->setPos(x, y);
    alert->item_bar->setPos(x + bar_x, y + bar_y);

    alert->change_img(alert_img);
    alert->draw_filling(false, pixels_for_one_chunk);

    alert->amount->setDefaultTextColor(QColor(0, 0, 0));
    alert->amount->setPlainText(QString::number(cargo));
    int padding = 10;
    int text_x = alert->item_bar->x() + alert->img_bar.width()/2 - padding;
    int text_y = alert->item_bar->y() + alert->img_bar.height()/2 - padding;
    alert->amount->setPos(text_x, text_y);
}

void Resources::hide_alert() {
    alert->change_img(alert->img);
    alert->draw_filling(true);
    alert->amount->setPlainText("");
}

int Resources::max_amount_of_cargo() {
    return 40;
}
