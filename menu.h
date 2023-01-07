#ifndef Menu_H
#define Menu_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QImage>
#include <QPushButton>
#include <QIcon>
#include <QGraphicsSceneMouseEvent>




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

 public:
    QGraphicsPixmapItem *pixmapPlay;
    QGraphicsPixmapItem *pixmapPoints;
    QGraphicsPixmapItem *pixmapSetings;
    QGraphicsPixmapItem *pixmapExit;
    QGraphicsPixmapItem *pixmapTitle;
    QGraphicsRectItem *panel;;

    bool PlayEnable=true;
    bool PointsEnable=false;
    bool SettingsEnable=false;
    bool ExitEnable=false;
    int selectedOption=0;

    Menu();
    void draw_menu( int width, int height);
    void remove_menu();
    void change_size(int selectedOption);
    QImage get_menu_texture();
    bool menuIsEnable=false;
    QGraphicsScene *scene;
};

#endif // Menu_H
