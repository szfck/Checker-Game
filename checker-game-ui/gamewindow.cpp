#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QKeyEvent>
#include <QHBoxLayout>


gamewindow::gamewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    addboard();

    // Connect button signal to appropriate slot
    connect(ui->replayPushButton, SIGNAL (released()), this, SLOT (handleButton()));

    replay();
}

void gamewindow::handleButton() {
    replay();
}


void gamewindow::replay() {
    myGame.board.init(6, 6);
    int diff = ui->difficultyComboBox->currentIndex() + 1;
    int firstplay = ui->firstplayComboBox->currentIndex() ^ 1;
    board->display();
    qDebug("diff :%d\n", diff);
    qDebug("firstPlay: %d\n", firstplay);

    myGame.setDifficulty(diff);
    myGame.setHumanFirst(firstplay);
}

void gamewindow::addboard() {
    board = new boardui(ui->boardWidget);
}

gamewindow::~gamewindow()
{
    delete ui;
}
