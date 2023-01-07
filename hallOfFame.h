#ifndef HALLOFFAME_H
#define HALLOFFAME_H

#include <vector>
#include <QTableWidget>

typedef struct {
    int score;
    char name[20];
} Wpis;

class HallOfFame {
public:
    HallOfFame();
    void show(int score);
    void init();
    void drawHallOfFame();

    QTableWidget *table;
    bool visible=false;

private:
    void readFile();
    void writeFile();
    std::vector<Wpis> listaSlawy;
};

#endif // HALLOFFAME_H
