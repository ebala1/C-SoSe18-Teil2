#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent= 0);
    void increase();
    int getScore();
    void setScore(int newScore);
    void update();

private:
    int score=0;
//int newScore;
};

#endif // SCORE_H
