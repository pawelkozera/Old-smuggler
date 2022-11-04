#include "interactiveobject.h"

InteractiveObject::InteractiveObject(QString img_name) {
    img.load("../smuggler/assets/map/" + img_name);
}
