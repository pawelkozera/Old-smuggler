#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "map.h"

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>

void set_window_parameters();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->set_window_parameters();

    Scene = new QGraphicsScene();

    Map map;
    QGraphicsPixmapItem *p = map.add_map_to_scene(Scene);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_window_parameters() {
    this->setCentralWidget(ui->graphicsView);
    this->setFixedSize(1366, 768);
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
