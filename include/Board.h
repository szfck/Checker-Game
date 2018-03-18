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

      /**
       * @brief terminateTest
       * @return true if is terminated, false otherwise
       */
      bool isTerminate() const;

      /**
       * @brief utility
       * @return utility value, the higher the values is, the more possible will win
       */
      int utility(int type) const;

      /**
       * @brief boardStatus
       * @return game status FIRSTWIN/SECONDWIN/DRAW/NONE
       */
      int boardStatus() const;

      /**
       * @brief hasNextLegalStep
       * @param type player type
       * @return true if player of tpye has next move, false otherwise
       */
      bool hasNextLegalStep(int type) const;

      /**
       * @brief cellRemain
       * @param type player type
       * @return how many player of type remain on the board
       */
      int cellRemain(int type) const;

      int evaluate(int type) const;

      std::pair<long long, long long> toNum() const;
  };
  
}

#endif
