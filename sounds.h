#ifndef SOUNDS_H
#define SOUNDS_H

#include <QSoundEffect>

class Sounds : public QSoundEffect
{
public:
    Sounds();

    QSoundEffect *add_resources;
    float volume;
};

#endif // SOUNDS_H
