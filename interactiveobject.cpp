#include "interactiveobject.h"

InteractiveObject::InteractiveObject(QString img_name) {
    img.load("../smuggler/assets/objects/" + img_name);
    setPos(0, 0);
}

void InteractiveObject::move_object(int x, int y) {
    int current_x = item->x();
    int current_y = item->y();
    item->setPos(current_x + x, current_y + y);
}
