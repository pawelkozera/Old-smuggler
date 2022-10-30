#ifndef MAP_H
#define MAP_H

#include <QPainter>
#include <QGraphicsItem>

class Map : public QGraphicsItem
{
public:
    Map(int width, int height);

    QPixmap map_texture;
    QRect window_rect;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MAP_H
