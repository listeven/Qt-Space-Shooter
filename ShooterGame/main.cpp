#include <QApplication>
#include <QFontDatabase>
#include "Game.h"
#include <QDebug>


// Adding enemy instantiation here to test it out. Later maybe move it to a Game class?

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/res/fonts/ARCADECLASSIC.TTF");
    //qDebug() << QFontDatabase::applicationFontFamilies(0);
    game = new Game();

    return a.exec();
}
