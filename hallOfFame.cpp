#include "hallOfFame.h"
#include <stdio.h>
#include <string>
#include <string.h>

const char* filename = "rekordy.txt";

HallOfFame::HallOfFame()
{
    readFile();
    table=new QTableWidget(listaSlawy.size(), 2);
    table->setHorizontalHeaderLabels({"Score", "Name"});
    table->setGeometry(0,0, 1408, 800);
    table->setFont(QFont("Arial", 20));
}

void HallOfFame::show(int score) {
    readFile();
}


void HallOfFame::init() {
    listaSlawy.push_back( { 1000, "Rzr"} );
    listaSlawy.push_back( { 100, "Kuzikson"} );
    writeFile();
}

void HallOfFame::drawHallOfFame()
{
    for(int i=0;i<listaSlawy.size();i++)
    {
        Wpis element=listaSlawy[i];
        QTableWidgetItem* scoreItem = new QTableWidgetItem(QString::number(element.score));
        QTableWidgetItem* nameItem = new QTableWidgetItem(element.name);
        table->setItem(i, 0, scoreItem);
        table->setItem(i, 1, nameItem);
    }
}

void HallOfFame::readFile() {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
        {
            printf("Could not open file for reading");
            return;
        }
    char scoreName[20];
    int score;
    listaSlawy.clear();
    while (fscanf(fptr, "%d,%s", &score, scoreName) == 2) {
        printf("%d %s\n", score, scoreName);
        Wpis element;
        element.score = score;
        strncpy(element.name, scoreName, 20);
        listaSlawy.push_back(element);
    }
    fclose(fptr);
}

void HallOfFame::writeFile() {
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
        {
            printf("Could not open file for writing");
            return;
        }
    for(auto element : listaSlawy) {
        fprintf(fptr, "%d,%s\n", element.score, element.name);
    }
    fclose(fptr);
}
