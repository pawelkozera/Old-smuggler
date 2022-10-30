#ifndef MAP_H
#define MAP_H

#include <QPixmap>


class Map
{
private:
    QPixmap map_texture;
public:
    Map();

    QPixmap get_map_texture();
};

#endif // MAP_H
