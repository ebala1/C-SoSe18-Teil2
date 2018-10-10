#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "myrect.h"
#include "score.h"
#include <QDebug>
#include <QApplication>
#include "spielfeld.h"

extern Spielfeld * spielfeld;

Enemy::Enemy(): QObject(), QGraphicsRectItem(){

    setRect(150,0,80,30);   // Rechteck(Objekt) wird erstellt, fällt von der Position 150 herunter, beginnt bei 0, die letzten Zahlen bestimmen die Größe des Rechtecks

}

void Enemy::move(){


    //Eine Funktion, die dafür sorgt, dass beim Zusammentreffen von MyRect und einem Feind:
    //1.der score um 1 Punkt erhöht wird
    //2.das Objekt von Feind aus dem Spielfeld gelöscht/enfernt

    QList<QGraphicsItem *> colliding_items= collidingItems();
    for(int i=0, n=colliding_items.size(); i < n; ++i){
      if (typeid(*(colliding_items[i])) == typeid(MyRect)){

            scene()->removeItem(this);              //berührt das Objekt das Obejkt Myrect in  der scene, wird es gelöscht
            spielfeld->score->increase();           //somit wird das score im Spielfeld wird mithife der increase()-Funktion(siehe score.cpp) um einen Punkt erhöht
            delete this;                            //Bei Erfüllung der höheren Stufe der Aufgabe, kann dies verändert werden, sodass bei Berührung der Objekte ein Leben gelöscht wird
                                                    // und bei dem Zusammentreffen von Ennemi, Enemy, Feind und dem Rand 0 der scene um einen Punkt erhöht
                                                    //Stufe 1: gleichmäßiger und regelmäßiger Anstieg der Punkte
    }
    }


    setPos(x()-2,y()+10);   // y()+10, da sich die Objekte von Ennemi/Feind/Enemy runter bewegen müssen
                            //x()-2 Objekt fällt etwas nach links

    if (pos().y() + rect().height() < 0){   // Sobald die Objekte unten am Rand (0) ankommen,werden sie entfernt
        scene()->removeItem(this);

        delete this;

    }
}

qreal Enemy::getEnemy(){        //Position der Enemy-Objekte für die Speicherung, da die pos.x schon vorgegeben ist und sich nicht ändert, wird nachder pos.y gesucht
    return pos().y();           // in die Datei wird hier jedoch die Zahl 0 eingelesen, da dies der Startpunkt der Objekte ist.
                                //Wenn man alle vorhandenen Objekte in der scene während dem Speichern in die Datei einlesen will, müsste man eine Art Schleife erzeugen, die die pos().y()
                                //aller Objekte einspeichert(unabhängig von der Menge)
}
