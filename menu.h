#ifndef Menu_H
#define Menu_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QImage>
#include <QPushButton>
#include <QIcon>
#include <QGraphicsSceneMouseEvent>
#include <QLineEdit>
#include <QAction>

#include "sounds.h"
#include "hallOfFame.h"

///Klasa menu
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
    QImage game_over;
    QImage game_over_paper;

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
    QGraphicsPixmapItem *pixmapGameOver;
    QGraphicsPixmapItem *pixmapGameOverPaper;
    QLineEdit *nickInput;
    QGraphicsTextItem *textPoints;

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
    /*!Funkcja pobiera parametry rozmiarów i wskaźnik na audio; zwraca nic*/
    void draw_menu(int width, int height, QAudioOutput *audio);
    /*!Funkcja pobiera nic; zwraca nic*/
    void draw_settings();
    /*!Funkcja pobiera wskaźnik na tablicę wyników; zwraca nic*/
    void draw_points_table(HallOfFame *hallOfFame);
    /*!Funkcja pobiera ilość punktów; zwraca nic*/
    void draw_game_over(int points);
    /*!Funkcja pobiera nic; zwraca nic*/
    void remove_game_over();
    /*!Funkcja pobiera nic; zwraca nic*/
    void remove_menu();
    /*!Funkcja pobiera wybraną opcję; zwraca nic*/
    void change_size(int selectedOption);
    /*!Funkcja pobiera wybraną opcję i wskaźnik na audio; zwraca nic*/
    void change_size_settings(int selectedOption, QAudioOutput *audio);
    QImage get_menu_texture();
    bool menuIsEnable=false;
    QGraphicsScene *scene;
};

#endif // Menu_H
