#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include "menu.h"
#include "hallOfFame.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


///Klasa głównego okna gry
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Menu *menu;
    /*!Funkcja pobiera nic; zwraca nic*/
    void set_window_parameters();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene;


private:

};
#endif // MAINWINDOW_H
