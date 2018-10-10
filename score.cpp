#include "score.h"
#include <QFont>
#include <spielfeld.h>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
score=0;
setPlainText(QString("Score: ") + QString::number(score));
setDefaultTextColor(Qt::red);
setFont(QFont("times",16));
}

void Score::increase()
{
    score++;            //Score erhöht sich jeweils um einen Punkt
    update();

}

void Score::update() {          //geladener Score wird überschriben
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore()           //Methode um den aktuellen Score beim Speichern in die Datei einzulesen
{
    return score;
}

void Score::setScore(int newScore)
{

    // Diese Funktion nimmt einen neue Zahl, hier newScore gennannt, als Parameter beim Aufruf
    // Wir haben ja einmal die Klasse Score, zu der auch alle Funktionen hier gehören
    // und eine private integer Variable score, also eine Ganzzahl, die wir hier mit dem Wert von newScore überschreiben
    score = newScore;
}
