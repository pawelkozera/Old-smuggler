#include "island.h"

#include <QPainter>
#include <QDebug>

Island::Island(QWidget *parent)
    : QWidget{parent}
{

}

Island::Island(int x, int y, QString img_name) {
    is_visible = false;

    QPixmap island;
    island.load("../smuggler/assets/map/island1.png");

    borders = QRect(x, y, island.width(), island.height());
}

void Island::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawEllipse(0, 0, 100, 100);
    painter.drawText(QPoint(30, 30), "aAAAAAAAAAAAAAAAAAAa");
    qDebug() << "ASD";
}
