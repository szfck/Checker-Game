#include "Board.h"
#include "Constant.h"
#include <cassert>
#include <iostream>

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
  
  void Board::show() {
    for (int i = row; i >= 1; i--) {
      std::string line = "";
      for (int j = 1; j <= col; j++) {
        if (get(i, j).status == PLAYER2) {
          line += '2';
        } else if (get(i, j).status == PLAYER1) {
          line += '1';
        } else {
          line += '_';
        }
      }
      std::cout << line << std::endl;
    }
    std::cout << std::endl;
  }

  bool Board::isValidType(int x, int y, int type) const {
    // printf("row :%d, col:%d\n", row, col);
    // printf("get status : %d\n", get(x,y).status);
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

}
