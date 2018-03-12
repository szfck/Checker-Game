#ifndef LIB_GAME_BOARD
#define LIB_GAME_BOARD

#include "Cell.h"
#include <vector>

namespace game {

  class Board {
    private:

      /** 
       * initialization
       * 
       * @param row
       * @param col
      */ 
      void init(int row, int col);

    public:

      std::vector<std::vector<Cell>> board;

      int row, col;

      Board();

      Board(int row, int col);

      Cell get(int x, int y) const;

      void set(int x, int y, Cell cell);

  };
  
}

#endif