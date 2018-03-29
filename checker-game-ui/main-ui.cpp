#include "Game.h"
#include "gamewindow.h"
#include <QApplication>

game::Game myGame;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    myGame.setDifficulty(1);
    myGame.setHumanFirst(true);
    myGame.board.init(6, 6);

    gamewindow w;
    w.show();

    return a.exec();
}
