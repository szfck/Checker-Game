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

    // TODO show diff pane
    game.setDifficulty(1);

    // TODO show first pane
    game.setHumanFirst(true);


    // TODO main pane
    game.run();

    return 0;
}
