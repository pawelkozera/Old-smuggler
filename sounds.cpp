#include "sounds.h"
#include <QDebug>
Sounds::Sounds() {
    volume = 1.0;

    add_resources = new QSoundEffect;
    add_resources->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/key_pressed.wav"));
    add_resources->setVolume(volume);
}
