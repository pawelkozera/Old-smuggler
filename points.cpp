#include "points.h"


Points::Points(int cargo_delivered, int cargo_lost, int mission_time)
{
    this->cargo_delivered=cargo_delivered;
    this->cargo_lost=cargo_lost;
    this->mission_time=mission_time;
    points_text=new QGraphicsTextItem("Points: "+QString::number(calculatePoints()));
    points_text->setPos(10, 10);
    points_text->hide();
    QFont font=points_text->font();
    font.setPointSize(30);
    font.setBold(true);
    points_text->setFont(font);
    QColor text_color(255,255,255);
    points_text->setDefaultTextColor(text_color);
    stopwatch=new QElapsedTimer();
}

int Points::calculatePoints()
{
    points+=cargo_delivered*100-cargo_lost*50;
    if(mission_time<5)
        points+=mission_time*10;
    return points;
}
