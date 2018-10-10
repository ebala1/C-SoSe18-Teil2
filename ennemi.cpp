#include "ennemi.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "myrect.h"
#include "spielfeld.h"
#include <QDebug>

extern Spielfeld * spielfeld;

Ennemi::Ennemi(): QObject(), QGraphicsRectItem(){


    // //Aussehen und Position vom Objekt
    setRect(550,0,30,70);


}

void Ennemi::move(){

    //Eine Funktion, die dafür sorgt, dass beim Auftreff von MyRect und einem Ennemi
    //1.score um 1 Punkt erhöht wird
    //2.das Objekt von Feind aus dem Spielfeld gelöscht
    QList<QGraphicsItem *> colliding_items= collidingItems();
    for(int i=0, n=colliding_items.size(); i < n; ++i){
      if (typeid(*(colliding_items[i])) == typeid(MyRect)){

            scene()->removeItem(this);          // siehe enemy.cpp

            spielfeld->score->increase();       //      ''

            delete this;
    }
    }

    setPos(x(),y()+7);                      // y()+7, da sich die Objekte von Ennemi/Feind/Enemy runter bewegen müssen
                                            //x position nicht angegeben, da dieses Objekt gerade runterfällt
    if (pos().y() + rect().height() < 0)    {// Sobald die Objekte unten am Rand (0) ankommen,

        scene()->removeItem(this);

        delete this;
    }
}

qreal Ennemi::getEnnemi(){                     //Selbe Prinzip wie bei getEnemy() (siehe enemy.cpp)
    return pos().y();
}

