#include "cloud.h"


Cloud::Cloud(int x)
{
    QString imagePath = "../smuggler/assets/clouds/Cloud_" +QString::number(x)+".png";
    QImage image(imagePath);
    cloudPixmap = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    cloudPixmap->setOpacity(0.5);
    QRandomGenerator generator;
    double randomScale = generator.generateDouble() * 2 + 1;
    cloudPixmap->setScale(randomScale);
    int randomX=QRandomGenerator::global()->bounded(-10000, 10000);
    int randomY=QRandomGenerator::global()->bounded(-10000, 10000);
    cloudPixmap->setPos(randomX, randomY);
}

void Cloud::move_cloud_event(QKeyEvent *event)
{
    long double x_speed=MovingSpeed::x_speed;
    long double y_speed=MovingSpeed::y_speed;

    if (event->key() == Qt::Key_A) {
        move_cloud(x_speed, 0);
    }
    else if (event->key() == Qt::Key_D) {
        move_cloud(-x_speed, 0);
    }
    else if (event->key() == Qt::Key_W) {
        move_cloud(0, y_speed);
    }
    else if (event->key() == Qt::Key_S) {
        move_cloud(0, -y_speed);
    }
}

void Cloud::move_cloud(long double x_speed, long double y_speed)
{
    float cloud_x = cloudPixmap->x();
    float cloud_y = cloudPixmap->y();
    cloudPixmap->setPos(cloud_x + x_speed, cloud_y + y_speed);
}
