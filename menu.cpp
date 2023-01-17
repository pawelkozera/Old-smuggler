#include "menu.h"

/*!Konstruktor ładujący obrazki menu*/
Menu::Menu() {
    menu_texture.load("../smuggler/assets/menu/menu_background.png");
    menu_title1.load("../smuggler/assets/menu/title1.png");
    points_table_title.load("../smuggler/assets/menu/PointsTable.png");
    btnPlay.load("../smuggler/assets/menu/btnPlay1.png");
    btnPoints.load("../smuggler/assets/menu/btnPoints.png");
    btnSettings.load("../smuggler/assets/menu/btnSettings.png");
    btnExit.load("../smuggler/assets/menu/btnExit.png");
    btnPlay2.load("../smuggler/assets/menu/btnPlay2.png");
    btnPoints2.load("../smuggler/assets/menu/btnPoints2.png");
    btnSettings2.load("../smuggler/assets/menu/btnSettings2.png");
    btnExit2.load("../smuggler/assets/menu/btnExit2.png");
    btnMusicON1.load("../smuggler/assets/menu/btnMusicOn1.png");
    btnMusicON2.load("../smuggler/assets/menu/btnMusicOn2.png");
    btnMusicOFF1.load("../smuggler/assets/menu/btnMusicOFF1.png");
    btnMusicOFF2.load("../smuggler/assets/menu/btnMusicOFF2.png");
    btnBack1.load("../smuggler/assets/menu/btnBack1.png");
    btnBack2.load("../smuggler/assets/menu/btnBack2.png");
    paper.load("../smuggler/assets/menu/paper.png");
    game_over.load("../smuggler/assets/menu/GameOver.png");
    game_over_paper.load("../smuggler/assets/menu/GameOverPaper.png");
}

/*!Konstruktor zwracający teksturę menu*/
QImage Menu::get_menu_texture() {
    return menu_texture;
}

/*!Funkcja rysująca menu*/
void Menu::draw_menu(int width, int height, QAudioOutput *audio)
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

   if(audio->volume()==0)
       pixmapMusic=new QGraphicsPixmapItem(QPixmap::fromImage(btnMusicOFF2));
   else
       pixmapMusic=new QGraphicsPixmapItem(QPixmap::fromImage(btnMusicON2));
   scene->addItem(pixmapMusic);
   pixmapMusic->hide();
   pixmapBack=new QGraphicsPixmapItem(QPixmap::fromImage(btnBack1));
   scene->addItem(pixmapBack);
   pixmapBack->hide();
   SettingsVisible=false;
   pixmapTitlePoints=new QGraphicsPixmapItem(QPixmap::fromImage(points_table_title));
   scene->addItem(pixmapTitlePoints);
   pixmapTitlePoints->hide();
   pixmapPaper=new QGraphicsPixmapItem(QPixmap::fromImage(paper));
   scene->addItem(pixmapPaper);
   pixmapPaper->hide();
}

/*!Funkcja rysująca opcję - opcje*/
void Menu::draw_settings()
{
    scene->removeItem(pixmapExit);
    scene->removeItem(pixmapSetings);
    scene->removeItem(pixmapPoints);
    scene->removeItem(pixmapPlay);

    int btn_x=(1408/2)-(pixmapPlay->pixmap().width()/4)-90;
    int btn_y=(800/2)-(pixmapPlay->pixmap().height()/2)+70;

    pixmapMusic->show();
    pixmapMusic->setPos(btn_x, btn_y);
    pixmapMusic->setScale(0.6);

    pixmapBack->show();
    pixmapBack->setPos(btn_x+40, btn_y+120);
    pixmapBack->setScale(0.5);

}

/*!Funkcja rysująca tablicę wyników*/
void Menu::draw_points_table(HallOfFame *hallOfFame)
{
    scene->removeItem(pixmapExit);
    scene->removeItem(pixmapSetings);
    scene->removeItem(pixmapPoints);
    scene->removeItem(pixmapPlay);
    scene->removeItem(pixmapTitle);

    hallOfFame->readFile();

    pixmapTitlePoints->setPos(1408/6, -100);
    pixmapTitlePoints->setScale(0.9);
    pixmapTitlePoints->show();

    pixmapPaper->show();
    pixmapPaper->setPos(372, 250);
    pixmapPaper->setScale(1.2);

    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    int y_dist=400;
    Wpis element;
    for(int i=0;i<hallOfFame->listaSlawy.size()-1;i++)
    {
        if(i>8)
            break;
        element=hallOfFame->listaSlawy[i];
        QString nick(element.name);
        QString points(QString::number(element.score));
        QGraphicsTextItem *nickItem=new QGraphicsTextItem(nick);
        QGraphicsTextItem *pointsItem=new QGraphicsTextItem(points);
        textItems.append(nickItem);
        textItems.append(pointsItem);
        nickItem->setPos(490, y_dist);
        pointsItem->setPos(770, y_dist);
        nickItem->setFont(font);
        pointsItem->setFont(font);
        y_dist+=30;
        scene->addItem(nickItem);
        scene->addItem(pointsItem);
    }
}

/*!Funkcja rysująca ekran przegranej*/
void Menu::draw_game_over(int points)
{
    panel = new QGraphicsRectItem(0,0,1408,800);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    QImage background=menu_texture.scaled(1408, 800);
    brush.setTextureImage(background);
    panel->setBrush(brush);
    panel->setOpacity(0.9);
    scene->addItem(panel);

    pixmapGameOver = new QGraphicsPixmapItem(QPixmap::fromImage(game_over));
    pixmapGameOver->setPos(1408/6, 50);
    pixmapGameOver->setScale(0.9);
    scene->addItem(pixmapGameOver);

    pixmapGameOverPaper = new QGraphicsPixmapItem(QPixmap::fromImage(game_over_paper));
    pixmapGameOverPaper->setPos(500, 250);
    pixmapGameOverPaper->setScale(0.9);
    scene->addItem(pixmapGameOverPaper);

    nickInput = new QLineEdit();
    nickInput->setVisible(true);
    nickInput->setPlaceholderText("Enter your nick");
    nickInput->setGeometry(600, 400, 230, 60);
    nickInput->setMaxLength(15);
    //nickInput->setFocus();
    QFont fontNick("Arial", 18);
    fontNick.setBold(true);
    nickInput->setFont(fontNick);
    nickInput->setStyleSheet("background: transparent;border: 2px solid black;");
    nickInput->setAlignment(Qt::AlignCenter);
    scene->addWidget(nickInput);

    textPoints = new QGraphicsTextItem(QString::number(points));
    textPoints->setPos(680, 590);
    QFont fontPoints("Arial", 50);
    fontPoints.setBold(true);
    textPoints->setFont(fontPoints);
    scene->addItem(textPoints);
}

/*!Funkcja usuwająca ekran przegranej*/
void Menu::remove_game_over()
{
    scene->removeItem(panel);
    scene->removeItem(pixmapGameOver);
    scene->removeItem(pixmapGameOverPaper);
    scene->removeItem(textPoints);
    nickInput->setVisible(false);
}

/*!Funkcja usuwająca menu*/
void Menu::remove_menu()
{
    scene->removeItem(pixmapExit);
    scene->removeItem(pixmapSetings);
    scene->removeItem(pixmapPoints);
    scene->removeItem(pixmapPlay);
    scene->removeItem(panel);
    scene->removeItem(pixmapTitle);
    scene->removeItem(pixmapBack);
    scene->removeItem(pixmapMusic);
    scene->removeItem(pixmapTitlePoints);
    scene->removeItem(pixmapPaper);
    panel->setOpacity(1);
    for (int i = 0; i < textItems.size(); ++i)
    {
        scene->removeItem(textItems[i]);
    }
}

/*!Funkcja zmieniająca wielkość podświetlonej opcji*/
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

/*!Funkcja zmieniająca wielkość podświetlonej opcji w opcjach gry*/
void Menu::change_size_settings(int selectedOption, QAudioOutput *audio)
{
    int btn_x=(1408/2)-(pixmapPlay->pixmap().width()/4)-90;
    int btn_y=(800/2)-(pixmapPlay->pixmap().height()/2)+70;
    if(selectedOption==0)
    {
        BackEnable=false;
        MusicEnable=true;
        pixmapBack->setPixmap(QPixmap::fromImage(btnBack1));
        pixmapBack->setScale(0.5);
        pixmapBack->setPos(btn_x+40, btn_y+120);
        if(audio->volume()==0)
        {
            pixmapMusic->setPixmap(QPixmap::fromImage(btnMusicOFF2));
        }
        else
        {
            pixmapMusic->setPixmap(QPixmap::fromImage(btnMusicON2));
        }
        pixmapMusic->setPos(btn_x, btn_y);
        pixmapMusic->setScale(0.6);

    }
    else if(selectedOption==1)
    {
        BackEnable=true;
        MusicEnable=false;
        if(audio->volume()==0)
        {
            pixmapMusic->setPixmap(QPixmap::fromImage(btnMusicOFF1));
        }
        else
        {
            pixmapMusic->setPixmap(QPixmap::fromImage(btnMusicON1));
        }
        pixmapMusic->setPos(btn_x+40, btn_y);
        pixmapMusic->setScale(0.5);
        pixmapBack->setPixmap(QPixmap::fromImage(btnBack2));
        pixmapBack->setScale(0.6);
        pixmapBack->setPos(btn_x, btn_y+120);
    }
}
