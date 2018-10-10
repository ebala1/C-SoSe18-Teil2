#include <QApplication>
#include "spielfeld.h"



Spielfeld * spielfeld;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    spielfeld = new Spielfeld();
    spielfeld->show();

    return a.exec();
}
