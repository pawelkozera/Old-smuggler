#include "menu.h"


Menu::Menu() {
    menu_texture.load("../smuggler/assets/menu/menu_background.png");
    menu_title1.load("../smuggler/assets/menu/title1.png");
    btnPlay.load("../smuggler/assets/menu/btnPlay1.png");
    btnPoints.load("../smuggler/assets/menu/btnPoints.png");
    btnSettings.load("../smuggler/assets/menu/btnSettings.png");
    btnExit.load("../smuggler/assets/menu/btnExit.png");
    btnPlay2.load("../smuggler/assets/menu/btnPlay2.png");
    btnPoints2.load("../smuggler/assets/menu/btnPoints2.png");
    btnSettings2.load("../smuggler/assets/menu/btnSettings2.png");
    btnExit2.load("../smuggler/assets/menu/btnExit2.png");
}

QImage Menu::get_menu_texture() {
    return menu_texture;
}

void Menu::draw_menu(int width, int height)
{
    panel = new QGraphicsRectItem(0,0,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    QImage background=menu_texture.scaled(width, height);
    brush.setTextureImage(background);
    panel->setBrush(brush);
    panel->setOpacity(0.9);
    scene->addItem(panel);

   pixmapTitle= new QGraphicsPixmapItem(QPixmap::fromImage(menu_title1));
   pixmapTitle->setPos(width/6, -100);
   pixmapTitle->setScale(0.9);
   scene->addItem(pixmapTitle);


   pixmapPlay=new QGraphicsPixmapItem(QPixmap::fromImage(btnPlay2));
   int btn_x=(width/2)-(pixmapPlay->pixmap().width()/4);
   int btn_y=(height/2)-(pixmapPlay->pixmap().height()/2);
   int y_dist=100;
   pixmapPlay->setPos(btn_x-50, btn_y);
   pixmapPlay->setScale(0.6);
   scene->addItem(pixmapPlay);

   pixmapPoints=new QGraphicsPixmapItem(QPixmap::fromImage(btnPoints));
   pixmapPoints->setPos(btn_x, btn_y+y_dist);
   pixmapPoints->setScale(0.5);
   scene->addItem(pixmapPoints);

   pixmapSetings=new QGraphicsPixmapItem(QPixmap::fromImage(btnSettings));
   pixmapSetings->setPos(btn_x, btn_y+y_dist*2);
   pixmapSetings->setScale(0.5);
   scene->addItem(pixmapSetings);

   pixmapExit=new QGraphicsPixmapItem(QPixmap::fromImage(btnExit));
   pixmapExit->setPos(btn_x, btn_y+y_dist*3);
   pixmapExit->setScale(0.5);
   scene->addItem(pixmapExit);

}

void Menu::remove_menu()
{
    scene->removeItem(pixmapExit);
    scene->removeItem(pixmapSetings);
    scene->removeItem(pixmapPoints);
    scene->removeItem(pixmapPlay);
    scene->removeItem(panel);
    scene->removeItem(pixmapTitle);
    panel->setOpacity(1);
}

void Menu::change_size(int selectedOption)
{
    int btn_x=(1408/2)-(pixmapPlay->pixmap().width()/4);
    int btn_y=(800/2)-(pixmapPlay->pixmap().height()/2);
    int y_dist=100;
    if(selectedOption==0)
    {

        PlayEnable=true;
        SettingsEnable=false;
        PointsEnable=false;
        ExitEnable=false;
        pixmapPlay->setPixmap(QPixmap::fromImage(btnPlay2));
        pixmapPlay->setPos(btn_x-50, btn_y);
        pixmapPlay->setScale(0.6);
        pixmapExit->setPos(btn_x, btn_y+y_dist*3);
        pixmapExit->setScale(0.5);
        pixmapExit->setPixmap(QPixmap::fromImage(btnExit));
        pixmapPoints->setPos(btn_x, btn_y+y_dist);
        pixmapPoints->setScale(0.5);
        pixmapPoints->setPixmap(QPixmap::fromImage(btnPoints));
    }
    else if(selectedOption==1)
    {
        PlayEnable=false;
        SettingsEnable=false;
        PointsEnable=true;
        ExitEnable=false;
        pixmapPoints->setPixmap(QPixmap::fromImage(btnPoints2));
        pixmapPoints->setPos(btn_x-50, btn_y+y_dist);
        pixmapPoints->setScale(0.6);
        pixmapPlay->setPos(btn_x, btn_y);
        pixmapPlay->setScale(0.5);
        pixmapPlay->setPixmap(QPixmap::fromImage(btnPlay));
        pixmapSetings->setPos(btn_x, btn_y+y_dist*2);
        pixmapSetings->setScale(0.5);
        pixmapSetings->setPixmap(QPixmap::fromImage(btnSettings));
    }
    else if(selectedOption==2)
    {
        PlayEnable=false;
        SettingsEnable=true;
        PointsEnable=false;
        ExitEnable=false;
        pixmapSetings->setPixmap(QPixmap::fromImage(btnSettings2));
        pixmapSetings->setPos(btn_x-50, btn_y+y_dist*2);
        pixmapSetings->setScale(0.6);
        pixmapPoints->setPixmap(QPixmap::fromImage(btnPoints));
        pixmapPoints->setPos(btn_x, btn_y+y_dist);
        pixmapPoints->setScale(0.5);
        pixmapExit->setPos(btn_x, btn_y+y_dist*3);
        pixmapExit->setScale(0.5);
        pixmapExit->setPixmap(QPixmap::fromImage(btnExit));
    }
    else if(selectedOption==3)
    {
        PlayEnable=false;
        SettingsEnable=false;
        PointsEnable=false;
        ExitEnable=true;
        pixmapExit->setPixmap(QPixmap::fromImage(btnExit2));
        pixmapExit->setPos(btn_x-50, btn_y+y_dist*3);
        pixmapExit->setScale(0.6);
        pixmapSetings->setPixmap(QPixmap::fromImage(btnSettings));
        pixmapSetings->setPos(btn_x, btn_y+y_dist*2);
        pixmapSetings->setScale(0.5);
        pixmapPlay->setPixmap(QPixmap::fromImage(btnPlay));
        pixmapPlay->setPos(btn_x, btn_y);
        pixmapPlay->setScale(0.5);
    }
}







