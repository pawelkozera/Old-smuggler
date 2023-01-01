#ifndef HALLOFFAME_H
#define HALLOFFAME_H

#include <vector>

typedef struct {
    int score;
    char name[20];
} Wpis;

class HallOfFame {
public:
    void show(int score);
    void init();
private:
    void readFile();
    void writeFile();
    std::vector<Wpis> listaSlawy;
};

#endif // HALLOFFAME_H
