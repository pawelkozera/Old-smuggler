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

    // player plane
    x = islands[0]->island_item->x() + 4;
    y = islands[0]->island_item->y() + 224;
    PlayerPlane *player_plane = new PlayerPlane();
    player_plane->item = Scene->addPixmap(player_plane->imgs[0]);
    player_plane->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    player_plane->item->setPos(x, y);
    player_plane->item->setTransformOriginPoint(player_plane->imgs[0].width()/2, player_plane->imgs[0].height()/2);

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

    interface->key_to_draw_map = Scene->addText("Press M for map");
    interface->key_to_draw_map->setDefaultTextColor(QColor(255, 255, 255));
    interface->key_to_draw_map->setPos(WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT - padding - 20);

    interface->key_to_draw_score = Scene->addText("Score: 0");
    interface->key_to_draw_score->setDefaultTextColor(QColor(255, 255, 255));
    interface->key_to_draw_score->setPos(5, 10);

    interface->map_item = Scene->addPixmap(interface->map_img);
    interface->map_item->setPos(0, 0);
    interface->map_item->hide();

    // event handler
    EventHandler *eventHandler = new EventHandler(islands, player_character, player_plane, settings, sounds, interface);
    eventHandler->setFocus();
    eventHandler->score = new Score();
    eventHandler->score->setScoreView(interface->key_to_draw_score);
    Scene->addItem(eventHandler);
    eventHandler->select_target_island();

    eventHandler->hallOfFame = new HallOfFame();
    eventHandler->hallOfFame->init();

    ui->graphicsView->setBackgroundBrush(map.get_map_texture());
    ui->graphicsView->setScene(Scene);
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
