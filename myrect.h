#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QWidget>

class MyRect:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    MyRect();
    void keyPressEvent(QKeyEvent * event);
      void start(void);
      void stop(void);
      qreal getPlayer();
      void setPlayer(int newPlayer);
public slots:
    void spawn();

private:
    QTimer *timer;
    QTimer *eTimer;
    int player = pos().x();
   int increment;
    int phase;
};

#endif // MYRECT_H
