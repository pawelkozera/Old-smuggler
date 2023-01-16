#include "sounds.h"
#include <QDebug>


Sounds::Sounds() {
    effects_volume = 1.0;
    music_volume = 0;

    add_resources = new QSoundEffect;
    add_resources->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/key_pressed.wav"));
    add_resources->setVolume(effects_volume);

    gun_shot = new QSoundEffect;
    gun_shot->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/gun.wav"));
    gun_shot->setVolume(effects_volume);

    prop_plane = new QSoundEffect;
    prop_plane->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/prop_plane.wav"));
    prop_plane->setVolume(0.1);

    map_opening = new QSoundEffect;
    map_opening->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/map_opening.wav"));
    map_opening->setVolume(effects_volume);

    menu_button = new QSoundEffect;
    menu_button->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/menu_button.wav"));
    menu_button->setVolume(effects_volume);

    menu_button_space = new QSoundEffect;
    menu_button_space->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/menu_button_space.wav"));
    menu_button_space->setVolume(effects_volume);

    score = new QSoundEffect;
    score->setSource(QUrl::fromLocalFile("../smuggler/sounds/effects/score.wav"));
    score->setVolume(effects_volume);

    music = new QMediaPlayer;
    audio_output = new QAudioOutput;
    music->setAudioOutput(audio_output);
    audio_output->setVolume(music_volume);
    music->setSource(QUrl::fromLocalFile("../smuggler/sounds/music/AdhesiveWombat _Night_Shade.mp3"));
}
