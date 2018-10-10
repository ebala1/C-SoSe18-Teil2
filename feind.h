  #ifndef FEIND_H
#define FEIND_H

#include <QGraphicsRectItem>
#include <QObject>

class Feind: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Feind();
    qreal getFeind();

public slots:
    void move();
};

#endif // FEIND_H
