#include "resources.h"

Resources::Resources(QString img_name, Settings *settings) : InteractiveObject(img_name) {
    item = settings->scene->addPixmap(img);
    item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
}

void Resources::show_text() {
    int current_x = item->x() + img.width()/2;
    int current_y = item->y();
}

void Resources::add() {
}
