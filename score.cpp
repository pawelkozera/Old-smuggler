#include "score.h"
#include <Qfont>

/*!Konstruktor tworzący wynik i ustawia go na 0*/
Score::Score(){
    score = 0;
}

/*!Funkcja zwiększająca wynik zależna od zrzutów cargo*/
void Score::increase(int val){
    score+=val;
    score_view->setPlainText("Score: " + QString::number(score));
}

/*!Funkcja resetująca wynik*/
void Score::reset(){
    score=0;
}

/*!Funkcja zwracająca wynik*/
int Score::getScore(){
    return score;
}
