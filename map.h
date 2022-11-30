#ifndef MAP_H
#define MAP_H

#include <QPixmap>
#include "island.h"


class Map
{
private:
    QPixmap map_texture;
public:
    Map();

    QPixmap get_map_texture();

    void generate_map(std::vector<Island *> islands);
    bool collision_and_gap_between_islands(Island *current_island, std::vector<Island *> islands);
};

#endif // MAP_H
