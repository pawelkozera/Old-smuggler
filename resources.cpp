#include "resources.h"

Resources::Resources(QString img_name) : InteractiveObject(img_name) {

}

void Resources::show_text() {
    int current_x = item->x();
    int current_y = item->y();

    text->setDefaultTextColor(QColor(255, 255, 255));
    text->setPos(current_x, current_y + 200);
}
