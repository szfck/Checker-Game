#ifndef BOARDUI_H
#define BOARDUI_H

#include "Cell.h"
#include "Game.h"
#include <QLabel>
#include <QObject>
#include <QThread>
#include <QTextEdit>

// global instance of Game
extern game::Game myGame;

// Cell UI
class cellui : public QLabel {
  public:
    int count;
    cellui(QWidget *parent);
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

/**
 * AI Algorithm Compute Object in another thread
 * to avoid UI refresh bock
 * Since this algorithm may take a lot of CPU resources
 */
class MyObject : public QObject {
    Q_OBJECT

  public:
    MyObject();

    ~MyObject();

  public slots:
    void compute();

  signals:
    void computeFinish();
};

// Board UI
class boardui : public QWidget {
    Q_OBJECT
  private:
    int pressCount;
    game::Cell previous;
    QTextEdit* information;

  public:
    boardui(QWidget *parent = 0, QTextEdit* information = 0);
    ~boardui();
    cellui *cells[7][7] = {{nullptr}};

    void display();

    void aiplay();

    void newgame();

    void click(cellui *current);

    void showResult(int result);
  public slots:

    void displayslot();
};

#endif // BOARDUI_H
