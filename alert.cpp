#include "alert.h"
#include "QPainter"

/*!Konstruktor ładujący obrazki interfejsu*/
Alert::Alert() {
    img.load("../smuggler/assets/objects/alert_default.png");
    img_bar_default.load("../smuggler/assets/objects/alert_default.png");
    img_bar.load("../smuggler/assets/objects/alert_bar.png");
    show_alert_for_object = false;
}

/*!Funkcja podmieniająca obrazki*/
void Alert::change_img(QPixmap img) {
    item->setPixmap(img);
}

/*!Funkcja wypełniająca tło*/
void Alert::draw_filling(bool hide, int width) {
    if (hide)
        item_bar->setPixmap(img_bar_default);
    else {
        QPixmap scaled = img_bar.scaled(QSize(width, img_bar.height()));
        item_bar->setPixmap(scaled);
    }
}
