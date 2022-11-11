#ifndef SOUNDS_H
#define SOUNDS_H

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

class Sounds
{
public:
    Sounds();

    float effects_volume;
    float music_volume;

    QSoundEffect *add_resources;
    QMediaPlayer *music;
    QAudioOutput *audio_output;
};

#endif // SOUNDS_H
