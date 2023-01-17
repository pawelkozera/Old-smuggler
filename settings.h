#ifndef SETTINGS_H
#define SETTINGS_H

#include <QGraphicsScene>


///Klasa ustawień
class Settings
{
public:
    Settings(int window_width, int window_height);

    int window_width;
    int window_height;

    QGraphicsScene *scene;
};

#endif // SETTINGS_H
