#include "Board.h"
#include "Constant.h"

namespace game {

  Board::Board() {

  }
  
  Board::Board(int row, int col): row(row), col(col) {
    board.init(row, col);
  }

  void Board::init(int row, int col) {
    board.resize(row + 1, std::vector<Cell>(col + 1));
    for (int i = 1; i <= row; i++) {
      for (int j = 1; j <= col; j++) {
        board[i][j] = Cell(i, j, EMPTY);
      }
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
  
}
