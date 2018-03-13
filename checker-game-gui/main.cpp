#include "mainwindow.h"
#include <QApplication>
#include "Game.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();

    game::Game game;

    game.setDifficulty(1);
    game.setHumanFirst(true);

    game.run();

    return 0;
}
