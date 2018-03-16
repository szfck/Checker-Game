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

    /**
     * @brief addboard add Board Widget to the gameWindow
     */
    void addboard();

    /**
     * @brief replay restart the game according to the difficulty and first or second to play in
     * the settings
     */
    void replay();

private:
    Ui::gamewindow *ui;
    boardui* board; // Board Widget

private slots:

    /**
     * @brief handleReplayButton
     */
    void handleReplayButton();
};

#endif // GAMEWINDOW_H
