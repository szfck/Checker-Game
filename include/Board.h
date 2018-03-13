#ifndef LIB_GAME_BOARD
#define LIB_GAME_BOARD

#include "Cell.h"
#include <vector>

namespace game {

  class Board {

    public:

      std::vector<std::vector<Cell>> board;

      int row, col;

      Board();

      Board(int row, int col);

      /** 
       * initialization
       * 
       * @param row
       * @param col
      */ 
      void init(int row, int col);

      Cell get(int x, int y) const;

      void set(int x, int y, Cell cell);

      /**
       * Show the board in command line
      */
      void show();

      /**
       * Take the cell from start to dest
       * Update the board status
       * 
       * @param start 
       * @param dest
      */
      void take(Cell start, Cell dest);

      /**
       * Check the cell is in board and has the correct type
      */ 
      bool isValidType(int x, int y, int type) const;

      /**
       * Get the next legal cell choice list
       * 
       * @param cell the position to put
       * @return list of Cells could choose
      */ 
      std::vector<Cell> getNextLegalCells(Cell cell) const;

  };
  
}

#endif