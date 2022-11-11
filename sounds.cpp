#include "sounds.h"
#include <QDebug>


Sounds::Sounds() {
    effects_volume = 1.0;
    music_volume = 0.1;

    add_resources = new QSoundEffect;
    add_resources->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/key_pressed.wav"));
    add_resources->setVolume(effects_volume);

    music = new QMediaPlayer;
    audio_output = new QAudioOutput;
    music->setAudioOutput(audio_output);
    audio_output->setVolume(music_volume);
    music->setSource(QUrl::fromLocalFile("../smuggler/sounds/music/AdhesiveWombat _Night_Shade.mp3"));
}
