#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "map.h"
#include "island.h"
#include "playercharacter.h"
#include "eventhandler.h"
#include "resources.h"
#include "fuel.h"
#include "playerplane.h"
#include "settings.h"
#include "sounds.h"
#include "interface.h"
#include "receiver.h"
#include "hallOfFame.h"
#include "menu.h"
#include "wind.h"
#include "compass.h"
#include "antiaircraftgun.h"
#include "cloud.h"

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>
#include <vector>


const int WINDOW_WIDTH = 1408;
const int WINDOW_HEIGHT = 800;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->set_window_parameters();

    srand (time(NULL));

    // settings
    Settings *settings = new Settings(WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene = new QGraphicsScene(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    settings->scene = Scene;

    // sounds
    Sounds *sounds = new Sounds();


    // islands
    std::vector<Island *> islands;
    islands.push_back(new Island("starting_island.png"));
    islands.push_back(new Island("island1.png"));
    islands.push_back(new Island("island2.png"));
    islands.push_back(new Island("island3.png"));
    islands.push_back(new Island("island4.png"));

    int x = WINDOW_WIDTH/4;
    int y = WINDOW_HEIGHT/10;
    // Adding items to the scene
    for (int i = 0; i < islands.size(); i++) {
         islands[i]->island_item = Scene->addPixmap(islands[i]->island_img);
         islands[i]->island_item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
         islands[i]->island_item->setPos(x, y);
    }

    // map
    Map map;
    map.generate_map(islands);
    map.generate_img_of_map(islands);

    // alert
    Alert *alert = new Alert();
    alert->item = Scene->addPixmap(alert->img);
    alert->item_bar = Scene->addPixmap(alert->img_bar_default);
    alert->amount = Scene->addText("");

    // interactive objects
    Resources *boxes = new Resources("boxes.png", alert, "alert_cargo.png");
    boxes->item = settings->scene->addPixmap(boxes->img);
    boxes->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    boxes->item->setPos(islands[0]->island_item->x() + 256, islands[0]->island_item->y() + 480);
    islands[0]->objects.push_back(boxes);

    Fuel *fuel = new Fuel("gas_storage.png", alert, "alert_fuel.png");
    fuel->item = settings->scene->addPixmap(fuel->img);
    fuel->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    fuel->item->setPos(islands[0]->island_item->x() + 288, islands[0]->island_item->y() + 32);
    islands[0]->objects.push_back(fuel);

    std::vector<std::pair<int, int>> reciver_coordinates;
    reciver_coordinates.push_back(std::pair<int, int> (islands[1]->island_item->x() + 832, islands[1]->island_item->y() + 1024));
    reciver_coordinates.push_back(std::pair<int, int> (islands[2]->island_item->x() + 1120, islands[2]->island_item->y() + 1024));
    reciver_coordinates.push_back(std::pair<int, int> (islands[3]->island_item->x() + 768, islands[3]->island_item->y() + 886));
    reciver_coordinates.push_back(std::pair<int, int> (islands[4]->island_item->x() + 1024, islands[4]->island_item->y() + 800));

    for (int i = 1; i < islands.size(); i++) {
        Receiver *receiver = new Receiver("receiver.png", alert, "alert_receiver.png");
        receiver->item = settings->scene->addPixmap(receiver->img);
        receiver->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

        receiver->item->setPos(reciver_coordinates[i - 1].first, reciver_coordinates[i - 1].second);
        islands[i]->objects.push_back(receiver);
    }

    // player character
    x = WINDOW_WIDTH/2;
    y = WINDOW_HEIGHT/2;
    PlayerCharacter *player_character = new PlayerCharacter();
    player_character->player_item = Scene->addPixmap(player_character->player_imgs[0]);
    player_character->player_item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    player_character->player_item->setPos(x, y);

    // buforing player character islands collision
    for (int i = 0; i < islands.size(); i++) {
        player_character->player_item->collidesWithItem(islands[i]->island_item, Qt::ContainsItemShape);
    }

    // wind vane
    Wind *wind= new Wind();

    // clouds
    QList<Cloud*> clouds;
    int n=1;
    for(int i=0; i<200; i++){
        Cloud *cloud = new Cloud(n);
        clouds.append(cloud);
        if(n==3)
            n=1;
        else
            n++;
    }

    // AntiAircraftGun
    std::vector<std::pair<int, int>> antiaircraftgun_coordinates;
    antiaircraftgun_coordinates.push_back(std::pair<int, int> (islands[1]->island_item->x() + 1600, islands[1]->island_item->y() + 286));
    antiaircraftgun_coordinates.push_back(std::pair<int, int> (islands[2]->island_item->x() + 1760, islands[2]->island_item->y() + 480));
    antiaircraftgun_coordinates.push_back(std::pair<int, int> (islands[3]->island_item->x() + 1792, islands[3]->island_item->y() + 192));
    antiaircraftgun_coordinates.push_back(std::pair<int, int> (islands[4]->island_item->x() + 1792, islands[4]->island_item->y() + 544));

    for (int i = 1; i < islands.size(); i++) {
        AntiAircraftGun *antiAircraftGun = new AntiAircraftGun("aircraftgun.png", settings, 5);
        antiAircraftGun->item = Scene->addPixmap(antiAircraftGun->img);
        antiAircraftGun->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
        antiAircraftGun->item->setTransformOriginPoint(antiAircraftGun->img.width()/2, antiAircraftGun->img.height()/2);

        antiAircraftGun->item->setPos(antiaircraftgun_coordinates[i - 1].first, antiaircraftgun_coordinates[i - 1].second);
        islands[i]->antiAircraftGun = antiAircraftGun;
    }

    // player plane
    x = islands[0]->island_item->x() + 4;
    y = islands[0]->island_item->y() + 224;
    PlayerPlane *player_plane = new PlayerPlane(wind, clouds);
    player_plane->item = Scene->addPixmap(player_plane->imgs[0]);
    player_plane->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    player_plane->item->setPos(x, y);
    player_plane->item->setTransformOriginPoint(player_plane->imgs[0].width()/2, player_plane->imgs[0].height()/2);
    player_plane->originalScale = player_plane->item->scale();

    // EnemyPlane
    std::vector<EnemyPlane *> enemyPlanes;

    for (int i = 1; i < 4; i += 2) {
        EnemyPlane *enemyPlane1 = new EnemyPlane("plane1.png", settings, 10);
        enemyPlane1->item = Scene->addPixmap(enemyPlane1->img);
        enemyPlane1->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
        enemyPlane1->item->setTransformOriginPoint(enemyPlane1->img.width()/2, enemyPlane1->img.height()/2);
        enemyPlane1->item->setPos(islands[i]->island_item->x() + 256, islands[i]->island_item->y() + 384);

        enemyPlane1->x_points.push_back(islands[i]->island_item->x() - WINDOW_WIDTH);
        enemyPlane1->y_points.push_back(islands[i]->island_item->y() - WINDOW_WIDTH);
        enemyPlane1->x_points.push_back(islands[i+1]->island_item->x() - WINDOW_WIDTH);
        enemyPlane1->y_points.push_back(islands[i+1]->island_item->y() - WINDOW_WIDTH);

        enemyPlanes.push_back(enemyPlane1);
    }

    // Clouds
    for (Cloud* cloud : clouds)
        Scene->addItem(cloud->cloudPixmap);

    // interface
    Interface *interface = new Interface();
    interface->cockpit_item = Scene->addPixmap(interface->cockpit_img);
    int padding = 15;
    interface->cockpit_item->setPos(5, WINDOW_HEIGHT - interface->cockpit_img.height() - padding);
    interface->power = Scene->addText("");
    interface->speed = Scene->addText("");
    interface->fuel = Scene->addText("");
    interface->cargo = Scene->addText("");
    interface->power->setPos(172, interface->cockpit_item->y() + 135);
    interface->speed->setPos(170, interface->cockpit_item->y() + 55);
    interface->fuel->setPos(300, interface->cockpit_item->y() + 95);
    interface->cargo->setPos(54, interface->cockpit_item->y() + 95);
    interface->cockpit_item->hide();

    interface->can_item = Scene->addPixmap(interface->can_img);
    interface->can_item->setPos(5, WINDOW_HEIGHT - interface->cockpit_img.height() - padding*2 - interface->can_img.height());
    interface->can_item->hide();

    interface->key_to_draw_map = Scene->addText("Press M for map");
    interface->key_to_draw_map->setDefaultTextColor(QColor(255, 255, 255));
    interface->key_to_draw_map->setPos(WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT - padding - 20);

    interface->key_to_draw_score = Scene->addText("Score: 0");
    interface->key_to_draw_score->setDefaultTextColor(QColor(255, 255, 255));
    interface->key_to_draw_score->setFont(QFont("Arial", 30, QFont::Bold));
    interface->key_to_draw_score->setPos(5, 10);

    interface->map_item = Scene->addPixmap(interface->map_img);
    interface->map_item->setPos(0, 0);
    interface->map_item->hide();

    // compass
    Compass *compass=new Compass();
    Scene->addItem(compass->compassItem);
    Scene->addItem(compass->arroItem);
    //Scene->addItem(cloud->cloudPixmap);

    // menu
    menu=new Menu();
    menu->scene=Scene;
    menu->draw_menu(WINDOW_WIDTH, WINDOW_HEIGHT, sounds->audio_output);

    // hall of fame
    HallOfFame *hallOfFame=new HallOfFame();

    // event handler
    EventHandler *eventHandler = new EventHandler(islands, player_character, player_plane, settings, sounds, interface, menu, ui, Scene, wind, compass, hallOfFame, clouds, enemyPlanes);
    eventHandler->setFocus();
    eventHandler->score = new Score();
    eventHandler->score->setScoreView(interface->key_to_draw_score);
    Scene->addItem(eventHandler);
    eventHandler->select_target_island();
    eventHandler->WINDOW_HEIGHT = WINDOW_HEIGHT;
    eventHandler->WINDOW_WIDTH = WINDOW_WIDTH;

    ui->graphicsView->setBackgroundBrush(map.get_map_texture());
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->setScene(menu->scene);
    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_window_parameters() {
    this->setCentralWidget(ui->graphicsView);
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setWindowTitle(tr("Old Smuggler"));
}
