#include "Board.h"
#include "Constant.h"
#include <cassert>
#include <iostream>
#include <QDebug>

namespace game {

  Board::Board() {

  }
  
  Board::Board(int row, int col) {
    init(row, col);
  }

  void Board::init(int row, int col) {
    this->row = row;
    this->col = col;
    board.resize(row + 1, std::vector<Cell>(col + 1));
    for (int i = 1; i <= row; i++) {
      for (int j = 1; j <= col; j++) {
        board[i][j] = Cell(i, j, EMPTY);
      }
    }
    
    //TODO set init player1 and player2
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

    int dir[2][2][2] = {
      { // player1
        {1, 1}, // y axis
        {1, -1} // x axis
      }, 
      { // player2
        {-1, -1}, // y axis
        {1, -1} // x axis
      }
    };
    
    std::vector<Cell> legalCells;

    // no jump
    for (int i = 0; i < 2; i++) {
      int dx = dir[cell.status][0][i] + cell.x;
      int dy = dir[cell.status][1][i] + cell.y;

      if (isValidType(dx, dy, EMPTY)) {
        legalCells.push_back(get(dx, dy));
      }
    }

    // jump over
    for (int i = 0; i < 2; i++) {
      int mx = dir[cell.status][0][i] + cell.x;
      int my = dir[cell.status][1][i] + cell.y;

      int dx = dir[cell.status][0][i] + mx;
      int dy = dir[cell.status][1][i] + my;

      // if jump over the enemy to an empty cell
      if (isValidType(dx, dy, EMPTY) && isValidType(mx, my, cell.status ^ 1)) {
        legalCells.push_back(get(dx, dy));
      }
    }

    return legalCells;

  }
  

  void Board::take(Cell start, Cell dest) {
    if (abs(start.x - dest.x) != 1) {
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
          if (get(i, j).status == type
              && !getNextLegalCells(get(i, j)).empty()) {
                return true;
              }
        }
      }
      return false;
  }

  int Board::evaluate(int type) const {
      int stable = 0;
      int nxt = 0;
      int v1 = cellRemain(PLAYER2) - cellRemain(PLAYER1);
      int w1 = 10;
      int v2 = 0, w2 = 3;
      int v3 = 0, w3 = 2;

      for (int i = 1; i <= row; i++) {
          for (int j = 1; j <= col; j++) {
              if (get(i, j).status == PLAYER1) {
                  if (j == 1 || j == col) v2++;
              } else if (get(i, j).status == PLAYER2) {
                  if (j == 1 || j == col) v2--;
              }
          }
      }

      return v1 * w1 + v2 * w2;
  }

  std::pair<long long, long long> Board::toNum() const {
      long long res1 = 0, res2 = 0;
      int bit = 0;
      for (int i = 1, k = 1; i <= row; i++, k = 3 - k) {
          for (int j = k; j <= col; j += 2, bit++) {
              if (get(i, j).status == PLAYER1) {
                  res1 += (1ll << bit);
              } else if (get(i, j).status == PLAYER2) {
                  res2 += (1ll << bit);
              }
          }
      }
      return {res1, res2};
  }

  int Board::utility(int type) const {
      int result = boardStatus();
      if (result == DRAW) return 0;
      else if (result == SECONDWIN) return Inf;
      else if (result == FIRSTWIN) return -Inf;
      else {
           return evaluate(PLAYER2);
      }

  }


  bool Board::isTerminate() const {
      return boardStatus() != NONE;
  }

  int Board::boardStatus() const {
      int player1CellNumber = cellRemain(PLAYER1);
      int player2CellNumber = cellRemain(PLAYER2);

      if (player1CellNumber == 0) return SECONDWIN;
      else if (player2CellNumber == 0) return FIRSTWIN;
      else if (!hasNextLegalStep(PLAYER1) && !hasNextLegalStep(PLAYER2)) {
        if (player1CellNumber > player2CellNumber) return FIRSTWIN;
        else if (player1CellNumber < player2CellNumber) return SECONDWIN;
        else return DRAW;
      } else {
        return NONE;
      }
  }

}
