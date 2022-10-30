#ifndef ISLAND_H
#define ISLAND_H

#include <QPainter>
#include <QGraphicsItem>

class Island : public QGraphicsRectItem
{
public:
    Island(int x, int y, QString img_name);
    bool is_visible;
    QRect borders;
    QPixmap island_img;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // ISLAND_H
