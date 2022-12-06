#include "map.h"

#include <QDebug>
#include <random>
#include <cmath>


Map::Map() {
    map_texture.load("../smuggler/assets/map/background.png");
}

QPixmap Map::get_map_texture() {
    return map_texture;
}

void Map::generate_map(std::vector<Island *> islands) {
    // random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-200, 200); // range for x, y position

    // map generating
    int random_x, random_y;
    bool run_loop = true;

    for (int i = 1; i < islands.size(); i++) {
        while (run_loop) {
            random_x = distr(gen) * 10;
            random_y = distr(gen) * 10;

            islands[i]->island_item->setPos(random_x, random_y);
            if (!collision_and_gap_between_islands(islands[i], islands)) run_loop = false;
        }
        qDebug() << islands[i]->island_item->x() << " " << islands[i]->island_item->y();
        run_loop = true;
    }
}

bool Map::collision_and_gap_between_islands(Island *current_island, std::vector<Island *> islands) {
    for (int i = 0; i < islands.size(); i++) {
        islands[i]->island_item->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
        if (current_island == islands[i]) continue;

        if (current_island->island_item->collidesWithItem(islands[i]->island_item)) return true;
    }

    for (int i = 0; i < islands.size(); i++) {
        islands[i]->island_item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    }

    return false;
}

void Map::generate_img_of_map(std::vector<Island *> islands) {
    const QImage blank_map("../smuggler/assets/interface/blank_map.png");
    QImage map(blank_map.width(), blank_map.height(), QImage::Format_ARGB32_Premultiplied);

    QPainter painter(&map);
    painter.drawImage(0, 0, blank_map);

    map.save("../smuggler/assets/interface/map.png");
}
