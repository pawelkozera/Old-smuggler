#include "resources.h"

Resources::Resources(QString img_name, Settings *settings, Alert *alert, QString alert_img_name) : InteractiveObject(img_name, settings, alert, alert_img_name) {
    item = settings->scene->addPixmap(img);
    item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
}

void Resources::show_alert(int cargo) {
    int x = item->x();
    int y = item->y() + 200;
    int bar_x = 47;
    int bar_y = 50;
    float amount = static_cast<float> (cargo)/max_amount_of_cargo();
    int percentage = round(amount*alert->img_bar.width());

    alert->item->setPos(x, y);
    alert->item_bar->setPos(x + bar_x, y + bar_y);

    alert->change_img(alert_img);
    alert->draw_filling(false, percentage);
}

void Resources::hide_alert() {
    alert->change_img(alert->img);
    alert->draw_filling(true);
}

int Resources::max_amount_of_cargo() {
    return 40;
}
