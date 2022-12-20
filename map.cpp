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
    std::uniform_int_distribution<> distr_x(-800, 800); // range for x, y position
    std::uniform_int_distribution<> distr_y(-800, 800); // range for x, y position

    // map generating
    int random_x, random_y;
    bool run_loop = true;

    for (int i = 1; i < islands.size(); i++) {
        while (run_loop) {
            random_x = distr_x(gen) * 10;
            random_y = distr_y(gen) * 10;

            if (random_x > 5000 && random_y >= 4000) continue;

            islands[i]->island_item->setPos(random_x, random_y);
            if (!collision_and_gap_between_islands(islands[i], islands)) run_loop = false;
        }
        qDebug() << islands[i]->island_item->x() << " " << islands[i]->island_item->y();
        islands[i]->x_starting = islands[i]->island_item->x();
        islands[i]->y_starting = islands[i]->island_item->y();
        run_loop = true;
    }

    islands[0]->x_starting = islands[0]->island_item->x();
    islands[0]->y_starting = islands[0]->island_item->y();
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

    int blank_area_x_start = 441;
    int blank_areay_start = 164;
    int blank_area_width = 1110;
    int blank_area_height = 720;

    int map_width, map_height, map_x, map_y;

    for (int i = 0; i < islands.size(); i++) {
        map_width = islands[i]->island_img.width()*0.05;
        map_height = islands[i]->island_img.height()*0.05;
        QImage bufor_map = islands[i]->island_img.toImage();
        bufor_map = bufor_map.scaled(map_width, map_height);

        map_x = islands[i]->x_starting*0.05 + blank_area_width/2;
        map_y = islands[i]->y_starting*0.05 + blank_area_height/2;
        painter.drawImage(blank_area_x_start + map_x, blank_areay_start + map_y, bufor_map);

        if (islands[i]->target_island) {
            QImage bufor_map_target = islands[i]->island_img.toImage();
            bufor_map_target = bufor_map_target.scaled(islands[i]->island_img.width()*0.1, islands[i]->island_img.height()*0.1);
            painter.drawImage(60, 120, bufor_map_target);
        }
    }

    map.save("../smuggler/assets/interface/map.png");
}
