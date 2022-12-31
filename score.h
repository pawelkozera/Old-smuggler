#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QGraphicsScene>

class Score {
public:
    Score();
    void setScoreView(QGraphicsTextItem *_score_view) {
        score_view=_score_view;
    };
    void increase(int);
    void reset();
    int getScore();
private:
    int score=0;
    QGraphicsTextItem *score_view;
};

#endif // SCORE_H
