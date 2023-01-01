#include "hallOfFame.h"
#include <stdio.h>
#include <string>
#include <string.h>

const char* filename = "rekordy.txt";

void HallOfFame::show(int score) {
    readFile();
}


void HallOfFame::init() {
    listaSlawy.push_back( { 1000, "Rzr"} );
    listaSlawy.push_back( { 100, "Kuzikson"} );
    writeFile();
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
