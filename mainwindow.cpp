#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "map.h"
#include "island.h"
#include "playercharacter.h"
#include "eventhandler.h"

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

    Scene = new QGraphicsScene(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // map
    Map map;

    // islands
    std::vector<Island *> islands;
    islands.push_back(new Island("starting_island.png"));

    // player character
    PlayerCharacter *player_character = new PlayerCharacter(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    player_character->player_item = Scene->addPixmap(player_character->player_imgs[0]);
    player_character->player_item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    player_character->player_item->setPos(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    // event handler
    EventHandler *eventHandler = new EventHandler(islands, player_character);
    eventHandler->setFocus();
    Scene->addItem(eventHandler);

    // Adding items to the scene
    for (int i = 0; i < islands.size(); i++) {
         islands[i]->island_item = Scene->addPixmap(islands[i]->island_img);
         islands[i]->island_item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
         islands[i]->island_item->setPos(WINDOW_WIDTH/4, WINDOW_HEIGHT/10);
    }

    Scene->addItem(player_character);

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
