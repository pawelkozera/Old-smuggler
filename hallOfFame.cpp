#include "hallOfFame.h"
#include <stdio.h>
#include <string>
#include <string.h>

const QString fileName = "rekordy.txt";

HallOfFame::HallOfFame()
{
    readFile();
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
            stream >> wpis.name;
            stream >> wpis.score;
            listaSlawy.push_back(wpis);
        }
        file.close();
}

void HallOfFame::writeFile(QString nick, int points) {
    QFile file(fileName);
       if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
       {
           qDebug() << "Error while opening file";
           return;
       }

       QTextStream stream(&file);
       stream << nick << " " << points <<"\n";
       file.close();
}
