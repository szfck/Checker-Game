#include "Board.h"
#include "Constant.h"
#include <cassert>
#include <iostream>
#include <cmath>

namespace game {

Board::Board() {}

Board::Board(int row, int col) { init(row, col); }

void Board::init(int row, int col) {
    this->row = row;
    this->col = col;
    board.resize(row + 1, std::vector<Cell>(col + 1));
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            board[i][j] = Cell(i, j, EMPTY);
        }
    }

    // init player1 and player2
    for (int j = 1; j <= 5; j += 2) {
        set(1, j, Cell(1, j, PLAYER1));
        set(5, j, Cell(5, j, PLAYER2));
    }

    for (int j = 2; j <= 6; j += 2) {
        set(2, j, Cell(2, j, PLAYER1));
        set(6, j, Cell(6, j, PLAYER2));
    }
}

Cell Board::get(int x, int y) const {
    assert(x >= 1 && x <= row && y >= 1 && y <= col);
    return board[x][y];
}

void Board::set(int x, int y, Cell cell) {
    assert(x >= 1 && x <= row && y >= 1 && y <= col);
    board[x][y] = cell;
}

bool Board::isValidType(int x, int y, int type) const {
    return x >= 1 && x <= row && y >= 1 && y <= col && get(x, y).status == type;
}

std::vector<Cell> Board::getNextLegalCells(Cell cell) const {

    assert(cell.status != EMPTY);

    int dir[2][2][2] = {{
                            // player1
                            {1, 1}, // y axis
                            {1, -1} // x axis
                        },
                        {
                            // player2
                            {-1, -1}, // y axis
                            {1, -1}   // x axis
                        }};

    std::vector<Cell> legalCells;

    // check if player has any legal capture move
    bool hasCaptureMove = false;
    for (int i = 1; i <= row && !hasCaptureMove; i++) {
        for (int j = 1; j <= col && !hasCaptureMove; j++) {
            if (get(i, j).status != cell.status)
                continue;
            for (int k = 0; k < 2; k++) {
                int mx = dir[cell.status][0][k] + i;
                int my = dir[cell.status][1][k] + j;

                int dx = dir[cell.status][0][k] + mx;
                int dy = dir[cell.status][1][k] + my;

                if (isValidType(dx, dy, EMPTY) &&
                    isValidType(mx, my, cell.status ^ 1)) {
                    hasCaptureMove = true;
                }
            }
        }
    }

    // jump over, capture move
    for (int i = 0; i < 2; i++) {
        int mx = dir[cell.status][0][i] + cell.x;
        int my = dir[cell.status][1][i] + cell.y;

        int dx = dir[cell.status][0][i] + mx;
        int dy = dir[cell.status][1][i] + my;

        // if jump over the enemy to an empty cell
        if (isValidType(dx, dy, EMPTY) &&
            isValidType(mx, my, cell.status ^ 1)) {
            legalCells.push_back(get(dx, dy));
        }
    }

    // if has capture move, then not consider regular move
    if (hasCaptureMove)
        return legalCells;

    // no jump, regular move
    for (int i = 0; i < 2; i++) {
        int dx = dir[cell.status][0][i] + cell.x;
        int dy = dir[cell.status][1][i] + cell.y;

        if (isValidType(dx, dy, EMPTY)) {
            legalCells.push_back(get(dx, dy));
        }
    }

    return legalCells;
}

void Board::take(Cell start, Cell dest) {
    // jumpr over a cell
    if (std::abs(start.x - dest.x) != 1) {
        int x = (start.x + dest.x) / 2;
        int y = (start.y + dest.y) / 2;
        set(x, y, Cell(x, y, EMPTY));
    }

    set(start.x, start.y, Cell(start.x, start.y, EMPTY));
    set(dest.x, dest.y, Cell(dest.x, dest.y, start.status));
}

int Board::cellRemain(int type) const {
    int count = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (get(i, j).status == type) {
                count++;
            }
        }
    }
    return count;
}

bool Board::hasNextLegalStep(int type) const {
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (get(i, j).status == type &&
                !getNextLegalCells(get(i, j)).empty()) {
                return true;
            }
        }
    }
    return false;
}

int Board::evaluate(int type) const {
    int stable = 0;
    int nxt = 0;

    // first, consdier how many left
    int v1 = cellRemain(PLAYER2) - cellRemain(PLAYER1);

    // weight1 is 10
    int w1 = 10;

    // second, consider the position at leftmost or rightmose
    // since these cells can not be eaten
    int v2 = 0;

    // weight2 is 3
    int w2 = 3;

    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (get(i, j).status == PLAYER1) {
                if (j == 1 || j == col)
                    v2++;
            } else if (get(i, j).status == PLAYER2) {
                if (j == 1 || j == col)
                    v2--;
            }
        }
    }

    // a weighted function for evaluation
    return v1 * w1 + v2 * w2;
}

int Board::utility(int type) const {
    int result = gameStatus();
    if (result == DRAW)
        return 0;
    else if (result == SECONDWIN)
        return Inf;
    else if (result == FIRSTWIN)
        return -Inf;
    else {
        return evaluate(PLAYER2);
    }
}

bool Board::isTerminate() const { return gameStatus() != NONE; }

int Board::gameStatus() const {
    int player1CellNumber = cellRemain(PLAYER1);
    int player2CellNumber = cellRemain(PLAYER2);

    if (player1CellNumber == 0)
        return SECONDWIN;
    else if (player2CellNumber == 0)
        return FIRSTWIN;
    else if (!hasNextLegalStep(PLAYER1) && !hasNextLegalStep(PLAYER2)) {
        if (player1CellNumber > player2CellNumber)
            return FIRSTWIN;
        else if (player1CellNumber < player2CellNumber)
            return SECONDWIN;
        else
            return DRAW;
    } else {
        return NONE;
    }
}

} // namespace game
