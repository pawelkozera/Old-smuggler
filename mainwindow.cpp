#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "map.h"

#include <QPixmap>
#include <QGraphicsPixmapItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->graphicsView);
    this->setFixedSize(1366, 768);
    setWindowTitle(tr("Old Smuggler"));

    Scene = new QGraphicsScene();

    Map map;
    map.add_map_to_scene(Scene);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

