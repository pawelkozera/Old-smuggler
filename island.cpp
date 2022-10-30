#include "island.h"
#include "movingspeed.h"

#include <QDebug>
#include <QKeyEvent>

Island::Island(int x, int y, QString img_name) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    is_visible = false;
    island_img.load("../smuggler/assets/map/island1.png");
    borders = QRect(x, y, island_img.width(), island_img.height());
}

QRectF Island::boundingRect() const {
    // outer most edges
    return borders;
}

void Island::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(borders, island_img);
}

void Island::keyPressEvent(QKeyEvent *event) {
    int x_speed = MovingSpeed::x_speed;
    int y_speed = MovingSpeed::y_speed;

    if (event->key() == Qt::Key_A) {
        setPos(x() - x_speed, y());
    }
    if (event->key() == Qt::Key_D) {
        setPos(x() + x_speed, y());
    }
    if (event->key() == Qt::Key_W) {
        setPos(x(), y() - y_speed);
    }
    if (event->key() == Qt::Key_S) {
        setPos(x(), y() + y_speed);
    }
    update();
}
