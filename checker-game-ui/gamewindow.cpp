#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QKeyEvent>

gamewindow::gamewindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::gamewindow) {
    ui->setupUi(this);
    addboard();

    // Connect button signal to appropriate slot
    connect(ui->replayPushButton, SIGNAL(released()), this,
            SLOT(handleReplayButton()));

    replay();
}

void gamewindow::handleReplayButton() { replay(); }

void gamewindow::replay() {
    int diff = ui->difficultyComboBox->currentIndex() + 1;
    int firstplay = ui->firstplayComboBox->currentIndex() ^ 1;

    qDebug("diff :%d\n", diff);
    qDebug("firstPlay: %d\n", firstplay);

    myGame.setDifficulty(diff);
    myGame.setHumanFirst(firstplay);

    board->newgame();
}

void gamewindow::addboard() { board = new boardui(ui->boardWidget); }

gamewindow::~gamewindow() { delete ui; }
