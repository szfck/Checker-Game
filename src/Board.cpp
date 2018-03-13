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
          line += '*';
        }
      }
      std::cout << line << std::endl;
    }
    std::cout << std::endl;
  }
}
