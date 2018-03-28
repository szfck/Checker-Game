#include "boardui.h"
#include <QDebug>
#include <set>
#include <QMessageBox>

cellui::cellui(QWidget* parent) : QLabel(parent) {
    count = 0;
    this->cell = cell;
    if (cell.status == PLAYER1) {
        setOne();
    } else if (cell.status == PLAYER2) {
        setTwo();
    }
}

cellui::~cellui() {

}

void cellui::mousePressEvent(QMouseEvent *e) {
    static_cast<boardui*>(this->parent())->click(this);
}

void cellui::setOne() {
    this->clear();
    this->setPixmap(QPixmap(":/assets/pawn_black.svg"));
    this->displayBackground();
}

void cellui::setTwo() {
    this->clear();
    this->setPixmap(QPixmap(":/assets/pawn_white.svg"));
    this->displayBackground();
}

void cellui::setRec() {
    this->clear();
    this->setStyleSheet("QLabel {background-color: rgb(0, 255, 0);}:hover{background-color: rgb(170,85,127);}");
}

void cellui::display() {
    this->clear();
    if (this->cell.status == PLAYER1) {
        setOne();
    } else if (this->cell.status == PLAYER2) {
        setTwo();
    }
    displayBackground();
}

void cellui::setEmpty() {
    this->clear();
    displayBackground();
}

void cellui::displayBackground() {
    if((cell.x + cell.y) % 2 == 0) {
        this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
    } else {
        this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
    }
}

boardui::boardui(QWidget* parent) : QWidget(parent) {
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            cells[i][j] = new cellui(this);
            int y = 21 + (j - 1) * 85;
            int x = 552 - (21 + i * 85);
            cells[i][j]->setGeometry(y, x, 85, 85);
        }
    }
}

boardui::~boardui() {

}

void boardui::newgame() {
    myGame.board.init(6, 6);
    display();

    // If AI play first
    if (myGame.getCurrentPlayer()->type == PLAYER2) {
        aiplay();
    }

    display();
}

void boardui::display() {
    pressCount = 0;
    // show border
    int x = 330, y = 105;
    {
        QLabel *outLabel = new QLabel(this);
        outLabel->setGeometry(330 - x,105 - y,552,21);
        outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
    }
    {
        QLabel *outLabel = new QLabel(this);
        outLabel->setGeometry(330 - x,636 - y,552,21);
        outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
    }

    {
        QLabel *outLabel = new QLabel(this);
        outLabel->setGeometry(330 - x,126 - y,21,510);
        outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
    }
    {
        QLabel *outLabel = new QLabel(this);
        outLabel->setGeometry(861 - x,126 - y, 21, 510);
        outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
    }

    // show cells
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            cells[i][j]->cell = myGame.board.get(i, j);
            cells[i][j]->display();
        }
    }
}

MyObject::MyObject() {

}

MyObject::~MyObject() {

}

// Compute AI's next step
void MyObject::compute() {
    std::pair<game::Cell, game::Cell> next = myGame.player2->play(myGame.board);

    myGame.board.take(next.first, next.second);

    emit computeFinish();
}

void boardui::aiplay() {
    MyObject* aicompute = new MyObject();
    // creat a new thread for computing
    QThread *thread = new QThread;
    thread->start();
    aicompute->moveToThread(thread);
    // trigger compute function when new thread is started
    connect(thread, SIGNAL(started()), aicompute, SLOT(compute()));
    // trigger update UI when compute finished
    connect(aicompute, SIGNAL(computeFinish()), this, SLOT(displayslot()));
}

void boardui::displayslot() {
    this->display();
    int result = myGame.gameStatus();
    if (result != NONE) {
        showResult(result);
        return;
    }

    myGame.getNextPlayer();

    if (myGame.getCurrentPlayer()->type == PLAYER2) {
        aiplay();
    }
}

void boardui::click(cellui *current) {
    // qDebug("click (%d,%d)\n", current->cell.x, current->cell.y);
    game::Cell cell = current->cell;

    // not human turn
    if (myGame.getCurrentPlayer()->type != PLAYER1) return;

    if (pressCount == 0) {
        if (cell.status != myGame.getCurrentPlayer()->type) return;
        auto list = myGame.board.getNextLegalCells(cell);
        if (list.size() == 0) return;

        pressCount++;
        for (auto item : list) {
            cells[item.x][item.y]->setRec();
        }
        previous = cell;
    } else if (pressCount == 1) {
        // press same cell twice
        if (cell.x == previous.x && cell.y == previous.y) {             pressCount = 0;
            display();
            return;
        }
        if (cell.status == myGame.getCurrentPlayer()->type) {
            pressCount = 0;
            display();
            click(current);
            return;
        }

        auto list = myGame.board.getNextLegalCells(previous);
        std::set<game::Cell> vis(list.begin(), list.end());

        // find next step to take
        if (vis.find(cell) != vis.end()) {             
            pressCount = 0;
            myGame.board.take(previous, cell);
            display();

            // next player
            myGame.getNextPlayer();

            int result = myGame.gameStatus();
            if (result != NONE) {
                showResult(result);
                return;
            }

            // next player is AI
            if (myGame.getCurrentPlayer()->type == PLAYER2) {
                aiplay();
            }
        }

    } else {
        qDebug("!!!this is a press bug!!!");
    }
}

// show result
void boardui::showResult(int result) {
    if (result != NONE) {
        QString str = "";
        if (result == FIRSTWIN) {
            str = "human win!";
        } else if (result == SECONDWIN) {
            str = "AI win!";
        } else if (result == DRAW) {
            str = "Draw!";
        } else {
            str = "unknow result!";
        }
        QMessageBox::about(NULL, "Game end", str);
    }
}
