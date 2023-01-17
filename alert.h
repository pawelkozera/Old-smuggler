#ifndef ALERT_H
#define ALERT_H

#include <QGraphicsPixmapItem>


///Klasa obrazków z pliku
class Alert
{
public:
    Alert();

    QPixmap img;
    QGraphicsPixmapItem *item;
    QPixmap img_bar_default;
    QPixmap img_bar;
    QGraphicsPixmapItem *item_bar;
    QGraphicsTextItem *amount;
    /*!Funkcja pobiera nic; zwraca true/false*/
    bool show_alert_for_object;
    /*!Funkcja pobiera obrazek; zwraca nic*/
    void change_img(QPixmap img);
    /*!Funkcja pobiera obrazek; zwraca nic*/
    void draw_filling(bool hide = false, int width = 0);
};

#endif // ALERT_H
