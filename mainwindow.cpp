#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "map.h"
#include <island.h>

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>
#include <vector>

const int WINDOW_WIDTH = 1408;
const int WINDOW_HEIGHT = 800;

void set_window_parameters();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->set_window_parameters();

    Scene = new QGraphicsScene();

    // map
    Map *map = new Map(WINDOW_WIDTH, WINDOW_HEIGHT);
    map->setFocus();

    // islands
    //std::vector<Island> islands;
    Island *starting_island = new Island(500, 300, "starting_island.png");
    starting_island->setFocus();

    // Adding items to the scene
    Scene->addItem(starting_island);
    ui->graphicsView->setBackgroundBrush(map->map_texture);
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
    setWindowTitle(tr("Old Smuggler"));
}
