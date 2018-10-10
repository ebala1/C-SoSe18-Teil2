#include "spielfeld.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "enemy.h"
#include <QApplication>
#include "myrect.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "score.h"
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>


Spielfeld::Spielfeld(QWidget *parent){


    QGraphicsScene * scene = new QGraphicsScene();
    scene->setStickyFocus(true);            //Scene bleibt beständig und rutscht beim Bewegen des Players nicht
    QPen pen;


    //Erstellung der Buttons für die Funktionen : Starten, Stoppen, Speichern und Laden

    QPushButton *startButton = new QPushButton(tr("Start"));
    startButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    startButton->move(1,60);    //Position des Buttons

    QPushButton *stopButton = new QPushButton(tr("Stop"));
    stopButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    stopButton->move(1,120);

    QPushButton* saver = new QPushButton(tr("Save"));
    saver->setFont(QFont("Times", 18, QFont::Bold));
    connect(saver, SIGNAL(clicked()), this, SLOT(saveFile()));
    saver->move(685, 60);

    QPushButton* loader = new QPushButton(tr("Load"));
    loader->setFont(QFont("Times", 18, QFont::Bold));
    connect(loader, SIGNAL(clicked()), this, SLOT(loadFile()));
    loader->move(685, 120);


    //Erstellung des Players/Avatar

    player = new MyRect();
    player->setRect(0,0,40,40);
    QBrush style(Qt::red, Qt::BDiagPattern);
    player->setBrush(style);


    score = new Score();


    scene->addItem(player);                             //Avatar
    scene->addEllipse(708,15,40,40,pen, QBrush(Qt::red));//Zeigt Leben 1 vom Player
    scene->addEllipse(752,15,40,40,pen, QBrush(Qt::red));
    scene->addEllipse(664,15,40,40,pen, QBrush(Qt::red));
    scene->addItem(score);                              //Score-Anzeige wird in die scene eingefügt und ist somit sichtbar im Spiel
    scene->addWidget(startButton);                      //Start-Button
    scene->addWidget(stopButton);                       //Stopp-Button
    scene->addWidget(saver);                            //Speichern-Button
    scene->addWidget(loader);                           //Laden-Button





    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();


    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();                                               //kleines extra Fenster öffnet sich aufgrund von view, dieser kann aber sofort geschlossen werden
    view->setFixedSize(800,600);
    scene->setSceneRect(0,0,1000,800);
    scene->setBackgroundBrush(Qt::lightGray);

    player->setPos(view->width()/2,view->height() - player->rect().height()); // setzt den player immer mittig, auch wenn man die size der scene ändert


    increment=0;
    phase=0;
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));     //Timer für spwan der Objekte : Ennemi, Enemy, Feind






    show();
}

void Spielfeld::start(void)
{
   timer->start(2000);// spawn/Bewegung der Objekte beginnt
   player->start() ;   //Player soll ab start beweglich werden(funktioniert nicht ganz, da player schon vorher beweglich ist)
   player->setFocus(); //ohne bewegt sich der player nach dem Button-Klick nicht, Fokus wird auf den Player gesetzt (davor auf scene)

}

void Spielfeld::stop(void)
{
   timer->stop();      //spawn/Bewegung der Objekte endet
   player->stop();
}


void Spielfeld::saveFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;
    dialog.setFileMode(QFileDialog::AnyFile);  //DialogFenster öffnet und man kann den Spielstand nach einem unbestimmten Namen einspeichern
    fileName = dialog.getSaveFileName(this,
        tr("Speichern als"), ".", tr("Position  (*.pos)")); // Datei-Typ ist vorgegeben: .pos (nicht änderbar)
    if (fileName.isNull() == false) {
        file.setFileName(fileName);

        if (file.open(QIODevice::ReadWrite)) {
            serialize(&file);
        }
        else {
            QMessageBox::warning(this, tr("Dateifehler"),
                tr("Folgende Datei kann nicht verwendet werden: ") + fileName, QMessageBox::Ok);
        }
    }
    player->setFocus(); // Fokus wird auf player gesetzt, damit nach dem Klick auf den Speichern-Button der player beweglich bleibt
}

void Spielfeld::serialize(QFile * file) {
    QTextStream out(file);
    out << "MeinZeichnungsFormat " << endl;
    // Auslesen der Daten und schreiben/spiechern in die Datei
    out << "score: " << QString::number(score->getScore())<<" Enemy: "<<QString::number(enemy->getEnemy())<<" Ennemi: "<<
    QString::number(ennemi->getEnnemi())<< " Feind: "<<QString::number(feind->getFeind()) <<" Player: "<< QString::number(player->getPlayer());

}

void Spielfeld::loadFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;
    dialog.setFileMode(QFileDialog::AnyFile);       //Dialog-Fenster öffnet sich -> Auswahl einer Datei
    fileName = dialog.getOpenFileName(this,
        tr("Speichern als"), ".", tr("Position (*.pos)"));
    if (fileName.isNull() == false) {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Dateifehler"),
                tr("Folgende Datei kann nicht geöffnet werden: ") + fileName, QMessageBox::Ok);
        }
        deserialize(&file);
        file.close();
        return;
    }
    player->setFocus(); // Fokus wird auf player gesetzt, damit nach dem Klick auf den Speichern-Button der player beweglich bleibt
}
void Spielfeld::deserialize(QFile * file)
{
    // habe die Datei lesen Funktion so geändert, dass sie so
    // funktioniert wie in der QT Dokumentation hier
    // http://doc.qt.io/qt-5/qfile.html#reading-files-directly
    QTextStream in(file);
    int lineNumber = 0;
    while (in.atEnd() == false) {
        QString line = in.readLine();
        //  Überprüfen ob die erste Zeile MeinZeichnungsFormat hat
        if (lineNumber == 0) {
            if (line != QString("MeinZeichnungsFormat ")) {
                QMessageBox::warning(this, tr("Formatfehler"),
                    tr("Das ist keine Zechnungsdatei!"), QMessageBox::Ok);
                return;
            }
        } else {
            // Hier kommt das lesen der Daten rein
            // Überprüfen ob eine Zeile mit z.B. score: anfängt
            //
            if (line.startsWith(QString("score: "))) {

                // Die Zeile beim Leerzeichen trennen in ein Array
                // 'score 123'
                // Array [0] wird 'score:'
                // Array [1] wird '123'
                // Wenn noch mehr Leerzeichen da sind, kommen auch mehr Arrayfelder
                QStringList array = line.split(QString(" "));

                int newScore = array[1].toInt();
                int newPlayer= array[9].toInt();




                score->setScore(newScore);  // Die Funktion setScore soll die private Ganzzahl score der Klasse Score überschreiben.
                                            // newScore haben wir in Zeile 193 als die Zahl definiert, die in unserer gespeicherten Datei stand.
                player->setPlayer(newPlayer);

                score->update();        //Score wird mit newScore überschrieben
                player->update();



            }
        }
        lineNumber++;

    }


}

