#include "fuel.h"

/*!Konstruktor paliwa*/
Fuel::Fuel(QString img_name, Alert *alert, QString alert_img_name) : InteractiveObject(img_name, alert, alert_img_name) {
    fuel_alert = true;
}

/*!Funkcja wyświetlania i wyczerpywania się paliwa*/
void Fuel::show_alert(int fuel) {
    int width_gap_box_alert = alert->img.width() - img.width();
    int x = item->x() - width_gap_box_alert/2;
    int y = item->y() - 160;
    int bar_x = 47;
    int bar_y = 50;
    float percentage = static_cast<float> (fuel)/max_amount_of_fuel();
    int pixels_for_one_chunk = round(percentage*alert->img_bar.width());

    alert->item->setPos(x, y);
    alert->item_bar->setPos(x + bar_x, y + bar_y);

    alert->change_img(alert_img);
    alert->draw_filling(false, pixels_for_one_chunk);

    alert->amount->setDefaultTextColor(QColor(0, 0, 0));
    alert->amount->setPlainText(QString::number(fuel));
    int padding = 10;
    int text_x = alert->item_bar->x() + alert->img_bar.width()/2 - padding;
    int text_y = alert->item_bar->y() + alert->img_bar.height()/2 - padding;
    alert->amount->setPos(text_x, text_y);
}

/*!Funkcja chowająca wartość paliwa*/
void Fuel::hide_alert() {
    alert->change_img(alert->img);
    alert->draw_filling(true);
    alert->amount->setPlainText("");
}

/*!Funkcja zwracająca ilość paliwa*/
int Fuel::max_amount_of_fuel() {return 20;}
