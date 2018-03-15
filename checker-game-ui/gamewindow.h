#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "boardui.h"

namespace Ui {
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = 0);
    ~gamewindow();
    void addboard();
    void replay();

private:
    Ui::gamewindow *ui;
    boardui* board;
private slots:
    void handleButton();
};

#endif // GAMEWINDOW_H
