#include "myrect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QtGui>
#include "enemy.h"
#include "feind.h"
#include "ennemi.h"
#include "spielfeld.h"
#include <QDebug>



MyRect::MyRect(){
    timer = new QTimer();               //QTimer für spawn()
    eTimer = new QTimer();              //QTimer für move()
}




void MyRect::keyPressEvent(QKeyEvent *event){       //Die Tastenbewegung vom Avatar
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)                          //Avatar/Player bewegt sich nur bis zum Rand (0)
        moveBy(-50,0);                              //Schnelligkeit der Bewegung kann eingestellt werden
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 850)                  //Avatar/Player bewegt sich bis zum Rand (850)
       moveBy(50,0);
    }

}

void MyRect::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
    Feind * feind = new Feind();
    scene()->addItem(feind);
    Ennemi * ennemi = new Ennemi();
    scene()->addItem(ennemi);

    connect(eTimer,SIGNAL(timeout()),enemy,SLOT(move()));           //Hier wird bei Stopp(ButtonKlick) die Bewegung der Objekte gestoppt. Objekte bleiben bei gestoppter Stelle stehen
    connect(eTimer,SIGNAL(timeout()),feind,SLOT(move()));
    connect(eTimer,SIGNAL(timeout()),ennemi,SLOT(move()));
}

void MyRect::start(void) { timer->start(2000); eTimer->start(50); increment=1; };
void MyRect::stop(void) { timer->stop(); eTimer->stop();}



qreal MyRect::getPlayer(){        //Methode, um beim serialize die Daten der Position vom Player ins Dokument einzuspeichern.
    return pos().x();       //da sich der Player nur von Rechts ach Links bewegen kann, ist nur die pos.x entscheident für die Dokumentation
}

void MyRect::setPlayer(int newPlayer){

    player=newPlayer;               //Methode für deserialize, um die position des Players in Spiel aufzurufen
                                    //Funktion auch in setScore (siehe score.cpp)
}
