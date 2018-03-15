#ifndef LIB_GAME_STRATEGY
#define LIB_GAME_STRATEGY

#include "Constant.h"
#include "Cell.h"
#include "Board.h"

namespace game {

  // Base class
  class Strategy {

    public:

      /**
       * virtual interface, need to be implemented by derived class
       * 
       * @param board The given Board instance
       * @param type The user type
       * @return The next cell to take
      */
      virtual std::pair<Cell, Cell> play(const Board& board, int type) = 0;
  };

  // Human strategy
  class PlayerStrategy: public Strategy {

    public:

      /** 
       * Human play strategy method
       * 
       * @param board The given Board instance
       * @param type The user type
       * @return The next cell to take
      */
      std::pair<Cell, Cell> play(const Board& board, int type);

  };

  // AI strategy
  class AIStrategy: public Strategy {
    private:
    
      int count = 0;

      std::pair<Cell, Cell> alpha_beta_search(const Board& board, int currentPlayer);

      std::vector<std::pair<Cell, Cell>> actions(const Board& board, int currentPlayer);

      std::pair<int, std::pair<Cell, Cell>> max_value(const Board& board, int currentPlayer, int alpha, int beta, int level);

      std::pair<int, std::pair<Cell, Cell>> min_value(const Board& board, int currentPlayer, int alpha, int beta, int level);

    public:

      // control alpha beta min max alg difficulty
      // the higher the error_rate is, eaiser the game is
      double error_rate;

      /** 
       * AI paly strategy method
       * 
       * @param board The given Board instance
       * @param type The user type
       * @return The next cell to take
      */
      std::pair<Cell, Cell> play(const Board& board, int type);

  }; 
}

#endif
