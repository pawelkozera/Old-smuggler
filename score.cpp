#include "score.h"
#include <Qfont>

Score::Score(){
    score = 0;
}

void Score::increase(int val){
    score+=val;
    score_view->setPlainText("Score: " + QString::number(score));
}

void Score::reset(){
    score=0;
}

int Score::getScore(){
    return score;
}
