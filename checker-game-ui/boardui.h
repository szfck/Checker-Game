#ifndef BOARDUI_H
#define BOARDUI_H

#include "Game.h"
#include "Cell.h"
#include <QLabel>

extern game::Game myGame;

class cellui : public QLabel {
public:
    int count;
    cellui(QWidget* parent);
    game::Cell cell;

    void display();

    void setOne();
    void setTwo();
    void setRec();
    void setEmpty();
    void displayBackground();
    void mousePressEvent(QMouseEvent *e);

    ~cellui();
};

class boardui : public QWidget {
private:
    int pressCount;
    game::Cell previous;
public:
    boardui(QWidget* parent = 0);
    ~boardui();
    cellui* cells[7][7] = { { nullptr } };

    void display();

    void aiplay();

    void newgame();

    void click(cellui* current);

    void showResult(int result);

};

#endif // BOARDUI_H
