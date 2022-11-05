#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include <QGraphicsItem>

class PlayerPlane : public QGraphicsPixmapItem
{
public:
    PlayerPlane(int x, int y);

    std::vector<QPixmap> imgs;
    int current_index_of_plane_img;
    QGraphicsPixmapItem *item;

    void simple_movement(QKeyEvent *event);
};

#endif // PLAYERPLANE_H
