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
    Island *island1 = new Island(500, 300, "island1.png");
    island1->setFocus();

    // Adding items to the scene
    Scene->addItem(map);
    Scene->addItem(island1);
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
