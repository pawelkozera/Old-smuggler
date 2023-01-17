#ifndef HALLOFFAME_H
#define HALLOFFAME_H

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFile>

/*!Struktura punktów i nazwy gracza*/
typedef struct {
    int score;
    char name[20];
} Wpis;


///Klasa tablicy wyników
class HallOfFame {
public:
    HallOfFame();

    bool visible=false;

    /*!Funkcja pobiera nic; zwraca nic*/
    void readFile();
    /*!Funkcja pobiera nick gracza i ilość zdobytych punktów; zwraca nic*/
    void writeFile(QString nick, int points);
    std::vector<Wpis> listaSlawy;
};

#endif // HALLOFFAME_H
