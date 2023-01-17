#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QGraphicsScene>


///Klasa wyników
class Score {
public:
    Score();
    /*!Funkcja pobiera; zwraca nic*/
    void setScoreView(QGraphicsTextItem *_score_view) {
        score_view=_score_view;
    };
    /*!Funkcja pobiera wartość wyniku; zwraca nic*/
    void increase(int);
    /*!Funkcja pobiera nic; zwraca nic*/
    void reset();
    /*!Funkcja pobiera nic; zwraca wynik*/
    int getScore();
private:
    int score=0;
    QGraphicsTextItem *score_view;
};

#endif // SCORE_H
