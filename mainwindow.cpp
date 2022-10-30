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
    Map map(WINDOW_WIDTH, WINDOW_HEIGHT);

    // islands
    std::vector<Island> islands;
    Island is(500, 300, "island1.png");

    // Adding items to the scene
    //map.add_map_to_scene(Scene);
    //Scene->addRect(map.window_rect);
    Scene->addRect(is.borders);
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

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        qDebug() << "a";
    }
    if (event->key() == Qt::Key_D) {
        qDebug() << "d";
    }
    if (event->key() == Qt::Key_W) {
        qDebug() << "w";
    }
    if (event->key() == Qt::Key_S) {
        qDebug() << "s";
    }
}
