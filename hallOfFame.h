#ifndef HALLOFFAME_H
#define HALLOFFAME_H

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFile>

typedef struct {
    int score;
    char name[20];
} Wpis;

class HallOfFame {
public:
    HallOfFame();
    void init();

    bool visible=false;

    void readFile();
    void writeFile();
    std::vector<Wpis> listaSlawy;
};

#endif // HALLOFFAME_H
