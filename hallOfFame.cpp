#include "hallOfFame.h"
#include <stdio.h>
#include <string>
#include <string.h>

const QString fileName = "rekordy.txt";

HallOfFame::HallOfFame()
{
    readFile();
}


void HallOfFame::init() {
    listaSlawy.push_back( { 1000, "Rzr"} );
    listaSlawy.push_back( { 100, "Kuzikson"} );
    writeFile();
}

void HallOfFame::readFile() {
    listaSlawy.clear();
    QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Error while opening file";
            return;
        }

        QTextStream stream(&file);
        while(!stream.atEnd()) {
            Wpis wpis;
            stream >> wpis.score;
            stream >> wpis.name;
            listaSlawy.push_back(wpis);
        }
        file.close();
}

void HallOfFame::writeFile() {
    QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Error while opening file";
            return;
        }

        QTextStream stream(&file);
        for (const auto& wpis : listaSlawy) {
            stream << wpis.score << " " << wpis.name << "\n";
        }
        file.close();
}
