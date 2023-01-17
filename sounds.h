#ifndef SOUNDS_H
#define SOUNDS_H

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>


///Klasa dźwięków
class Sounds
{
public:
    Sounds();

    float effects_volume;
    float music_volume;

    QSoundEffect *add_resources;
    QSoundEffect *gun_shot;
    QSoundEffect *prop_plane;
    QSoundEffect *map_opening;
    QSoundEffect *menu_button;
    QSoundEffect *menu_button_space;
    QSoundEffect *score;
    QMediaPlayer *music;
    QAudioOutput *audio_output;
};

#endif // SOUNDS_H
