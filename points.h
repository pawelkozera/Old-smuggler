#ifndef POINTS_H
#define POINTS_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QElapsedTimer>

class Points
{
public:
    Points(int cargo_delivered=0, int cargo_lostt=0, int mission_time=0);
    int calculatePoints();

    int points=0;
    int cargo_delivered;
    int cargo_lost;
    int mission_time;
    QGraphicsTextItem *points_text;
    QElapsedTimer  *stopwatch;
};

#endif // POINTS_H
