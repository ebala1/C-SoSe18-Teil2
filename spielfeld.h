#ifndef SPIELFELD_H
#define SPIELFELD_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "myrect.h"
#include "score.h"
#include <QTimer>
#include "enemy.h"
#include <QFile>
#include <QtGui>
#include <feind.h>
#include <ennemi.h>


class Spielfeld:  public QGraphicsView{
    Q_OBJECT
public:
    Spielfeld(QWidget * parent=0);

    QGraphicsScene * scene;
    MyRect * player=new MyRect();
    Score * score;
    Spielfeld * spielfeld;
    Enemy * enemy = new Enemy();
    Feind* feind = new Feind();
    Ennemi * ennemi= new Ennemi();


    void serialize(QFile *file);
    void deserialize(QFile *file);




private slots:
    void start(void);
    void saveFile(void);
    void loadFile(void);
    void stop(void);

private:
    int increment;
    int phase;
    QTimer * timer;

};

#endif // SPIELFELD_H
