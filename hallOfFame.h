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

    bool visible=false;

    void readFile();
    void writeFile(QString nick, int points);
    std::vector<Wpis> listaSlawy;
};

#endif // HALLOFFAME_H
