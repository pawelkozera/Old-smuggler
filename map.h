#ifndef MAP_H
#define MAP_H

#include <QPixmap>
#include "island.h"


///Klasa map
class Map
{
private:
    QPixmap map_texture;
public:
    Map();

    QPixmap get_map_texture();

    /*!Funkcja pobiera kontener vector wysp; zwraca nic*/
    void generate_map(std::vector<Island *> islands);
    /*!Funkcja pobiera wskaźnik aktywnej wyspy i kontener vector wysp; zwraca true/false*/
    bool collision_and_gap_between_islands(Island *current_island, std::vector<Island *> islands);
    /*!Funkcja pobiera kontener vector wysp; zwraca nic*/
    void generate_img_of_map(std::vector<Island *> islands);
};

#endif // MAP_H
