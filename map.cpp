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
    std::uniform_int_distribution<> distr(-20000, 20000); // range for x, y position

    // map generating
    int random_x, random_y;
    bool run_loop = true;

    for (int i = 1; i < islands.size(); i++) {
        while (run_loop) {
            random_x = distr(gen);
            random_y = distr(gen);

            islands[i]->island_item->setPos(random_x, random_y);
            if (!collision_and_gap_between_islands(islands[i], islands)) run_loop = false;
        }
        run_loop = true;
    }
}

bool Map::collision_and_gap_between_islands(Island *current_island, std::vector<Island *> islands) {
    int gap_between_islands = 500;
    int distance_between_islands;
    int x1 = current_island->island_item->x();
    int y1 = current_island->island_item->y();
    int x2, y2 = 0;

    for (int i = 0; i < islands.size(); i++) {
        if (current_island == islands[i]) continue;

        if (current_island->island_item->collidesWithItem(islands[i]->island_item)) return true;

        x2 = islands[i]->island_item->x();
        y2 = islands[i]->island_item->y();
        distance_between_islands = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

        if (distance_between_islands < gap_between_islands) return true;
    }

    return false;
}
