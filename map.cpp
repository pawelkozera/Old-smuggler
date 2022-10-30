#include "map.h"

#include <QDebug>

Map::Map() {
    map_texture.load("../smuggler/assets/map/background.png");
}

QPixmap Map::get_map_texture() {
    return map_texture;
}
