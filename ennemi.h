#ifndef ENNEMI_H
#define ENNEMI_H

#include <QGraphicsRectItem>
#include <QObject>

class Ennemi: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Ennemi();
    qreal getEnnemi();

public slots:
    void move();
};

#endif // ENNEMI_H
