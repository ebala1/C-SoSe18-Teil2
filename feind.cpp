#include "feind.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "myrect.h"
#include "spielfeld.h"
#include <QDebug>

extern Spielfeld * spielfeld;

Feind::Feind(): QObject(), QGraphicsRectItem(){

    //Aussehen und Position vom Objekt
    setRect(350,0,80,80);


}

void Feind::move(){

    //Eine Funktion, die dafür sorgt, dass beim Auftreff von MyRect und einem Feind
    //1.score um 1 Punkt erhöht wird
    //2.das Objekt von Feind aus dem Spielfeld gelöscht

    QList<QGraphicsItem *> colliding_items= collidingItems();
    for(int i=0, n=colliding_items.size(); i < n; ++i){
     if (typeid(*(colliding_items[i])) == typeid(MyRect)){



            scene()->removeItem(this);              //Prinzip wie bei enemy.cpp
            spielfeld->score->increase();


            delete this;
        }
    }
    setPos(x(),y()+5); // Bewegung der von oben kommenden Objekten



    if (pos().y() + rect().height() < 0){ // Sobald die Objekte unten am Rand (0) ankommen,werden diese gelöscht

    scene()->removeItem(this);

    delete this;

    }
}

qreal Feind::getFeind(){              //Selbe Prinzip wie bei getEnemy() (siehe enemy.cpp)
    return pos().y();
}

