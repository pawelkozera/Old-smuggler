#ifndef ALERT_H
#define ALERT_H

#include <QGraphicsPixmapItem>


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
    bool show_alert_for_object;

    void change_img(QPixmap img);
    void draw_filling(bool hide = false, int width = 0);
};

#endif // ALERT_H
