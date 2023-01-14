#ifndef Menu_H
#define Menu_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QImage>
#include <QPushButton>
#include <QIcon>
#include <QGraphicsSceneMouseEvent>

#include "sounds.h"
#include "hallOfFame.h"

class Menu
{
    QImage menu_texture;
    QImage menu_title1;
    QImage btnPlay;
    QImage btnPoints;
    QImage btnSettings;
    QImage btnExit;
    QImage btnPlay2;
    QImage btnPoints2;
    QImage btnSettings2;
    QImage btnExit2;
    QImage btnBack1;
    QImage btnBack2;
    QImage points_table_title;
    QImage paper;

 public:
    QImage btnMusicON1;
    QImage btnMusicON2;
    QImage btnMusicOFF1;
    QImage btnMusicOFF2;
    QGraphicsPixmapItem *pixmapPlay;
    QGraphicsPixmapItem *pixmapPoints;
    QGraphicsPixmapItem *pixmapSetings;
    QGraphicsPixmapItem *pixmapExit;
    QGraphicsPixmapItem *pixmapTitle;
    QGraphicsPixmapItem *pixmapMusic;
    QGraphicsPixmapItem *pixmapBack;
    QGraphicsRectItem *panel;
    QGraphicsPixmapItem *pixmapTitlePoints;
    QGraphicsPixmapItem *pixmapPaper;
    QList<QGraphicsTextItem*> textItems;

    bool PlayEnable=true;
    bool PointsEnable=false;
    bool SettingsEnable=false;
    bool ExitEnable=false;
    bool MusicEnable=false;
    bool BackEnable=false;
    bool SettingsVisible=false;
    bool PointsVisible=false;
    int selectedOption=0;
    int selectedOptonStettings=0;

    Menu();
    void draw_menu( int width, int height, QAudioOutput *audio);
    void draw_settings();
    void draw_points_table(HallOfFame *hallOfFame);
    void remove_menu();
    void change_size(int selectedOption);
    void change_size_settings(int selectedOption, QAudioOutput *audio);
    QImage get_menu_texture();
    bool menuIsEnable=false;
    QGraphicsScene *scene;
};

#endif // Menu_H
