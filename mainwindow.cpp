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
    Settings *settings = new Settings();
    Scene = new QGraphicsScene(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    settings->scene = Scene;

    // map
    Map map;

    // islands
    std::vector<Island *> islands;
    islands.push_back(new Island("starting_island.png"));

    int x = WINDOW_WIDTH/4;
    int y = WINDOW_HEIGHT/10;
    // Adding items to the scene
    for (int i = 0; i < islands.size(); i++) {
         islands[i]->island_item = Scene->addPixmap(islands[i]->island_img);
         islands[i]->island_item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
         islands[i]->island_item->setPos(x, y);
    }

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

    // player character
    x = WINDOW_WIDTH/2;
    y = WINDOW_HEIGHT/2;
    PlayerCharacter *player_character = new PlayerCharacter(x, y);
    player_character->player_item = Scene->addPixmap(player_character->player_imgs[0]);
    player_character->player_item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    player_character->player_item->setPos(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    // player plane
    x = islands[0]->island_item->x() + 4;
    y = islands[0]->island_item->y() + 224;
    PlayerPlane *player_plane = new PlayerPlane(x, y);
    player_plane->item = Scene->addPixmap(player_plane->imgs[0]);
    player_plane->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    player_plane->item->setPos(x, y);
    player_plane->item->setTransformOriginPoint(player_plane->imgs[0].width()/2, player_plane->imgs[0].height()/2);

    // event handler
    EventHandler *eventHandler = new EventHandler(islands, player_character, player_plane, settings);
    eventHandler->setFocus();
    Scene->addItem(eventHandler);

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
