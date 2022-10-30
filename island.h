#ifndef ISLAND_H
#define ISLAND_H

#include <QWidget>

class Island : public QWidget
{
    Q_OBJECT
public:
    explicit Island(QWidget *parent = nullptr);

    Island(int x, int y, QString img_name);
    QRect borders;
    bool is_visible;

    void paintEvent(QPaintEvent *event) override;

signals:

};

#endif // ISLAND_H
