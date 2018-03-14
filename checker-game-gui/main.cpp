#include "mainwindow.h"
#include <QApplication>
#include "Game.h"
#include "Board.h"
#include <QLabel>
#include <QMessageBox>

class Border
{
public:
    Border();
    void outline(QWidget *baseWidget, int xPos, int yPos, int Pos)
    {
         QLabel *outLabel = new QLabel(baseWidget);

        if(!Pos)
            outLabel->setGeometry(xPos,yPos,552,21);        //Horizontal Borders

        else
            outLabel->setGeometry(xPos,yPos,21,510);        //Vertical Borders

        outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
    }
};

class Tile;
void press(Tile *tile);

class Tile: public QLabel {
public:
    game::Cell cell;

    int count;

    Tile(QWidget* pParent = 0, Qt::WindowFlags f=0) : QLabel(pParent, f) {
        count = 0;
    }


    void display() {

        if (cell.status == PLAYER1) {
            setOne();
        } else if (cell.status == PLAYER2) {
            setTwo();
        }

        if((cell.x + cell.y) % 2) {
            this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
        } else {
            this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
        }


    }

    void setOne() {
        this->setPixmap(QPixmap(":/assets/pawn_white.svg"));
    }

    void setTwo() {
        this->setPixmap(QPixmap(":/assets/pawn_black.svg"));
    }

    void setRec() {
        this->setStyleSheet("QLabel {background-color: rgb(0, 255, 0);}:hover{background-color: rgb(170,85,127);}");
    }

    void setEmpty() {
        if((cell.x + cell.y) % 2) {
            this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
        } else {
            this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
        }
    }

    void mousePressEvent(QMouseEvent *event) {
        press(this);
    }

};

Tile *tiles[8][8] = { { NULL } };

void chessBoard(QWidget* baseWidget, const game::Board& board) {
    Border *border[4]={ NULL };

    //borderDisplay
    {
        border[0]->outline(baseWidget,330,105,0);
        border[1]->outline(baseWidget,330,636,0);
        border[2]->outline(baseWidget,330,126,1);
        border[2]->outline(baseWidget,861,126,1);
    }

    int ver=126 + 85 * 5;
    for(int i=1;i<=6;i++)
    {
        int hor=351;
        for(int j=1;j<=6;j++)
        {
            tiles[i][j] = new Tile(baseWidget, 0);
            tiles[i][j]->cell = board.get(i, j);
            tiles[i][j]->setGeometry(hor,ver,85,85);
            tiles[i][j]->display();
            hor+=85;
        }
        ver-=85;
    }
}

game::Game myGame;

void updateBoard() {
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            tiles[i][j]->cell = myGame.board.get(i, j);
            tiles[i][j]->clear();
            tiles[i][j]->display();
        }
    }
}

game::Cell previous;
std::vector<game::Cell> vis;

void press(Tile* tile) {
    if (tile->cell.status == myGame.getCurrentPlayer()->type) {
        for (auto cell : vis) {
            tiles[cell.x][cell.y]->setEmpty();
        }
        vis.clear();

        if (tile->cell.x == previous.x && tile->cell.y == previous.y) {
            previous = game::Cell(-1, -1, EMPTY);
        } else {
            vis.clear();
            auto list = myGame.board.getNextLegalCells(tile->cell);
            for (auto cell : list) {
                tiles[cell.x][cell.y]->setRec();
            }
            vis = list;
            previous = tile->cell;
        }
    } else if (previous.status != EMPTY){
        game::Cell next = game::Cell(-1, -1, EMPTY);
        for (auto cell : vis) {
            qDebug("%d %d", cell.x, cell.y);
            if (cell.x == tile->cell.x && cell.y == tile->cell.y) {
                next = tile->cell;
            }
        }
        if (next.x != -1) {
            myGame.board.take(previous, next);
            updateBoard();
            myGame.getNextPlayer();
            previous = game::Cell(-1, -1, EMPTY);
            vis.clear();

            int result = myGame.isFinished();
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
    }


}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    // TODO show diff pane
    myGame.setDifficulty(1);

    // TODO show first pane
    myGame.setHumanFirst(true);


    QWidget *myWidget = new QWidget();

    myWidget->setGeometry(0, 0, 1370, 1370);
    // TODO main pane
//    game.run();
//    accessories(myWidget);
    chessBoard(myWidget, myGame.board);
    myWidget->show();

    return a.exec();
}
