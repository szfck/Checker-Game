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
      virtual Cell play(const Board& board, int type) = 0;
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
      Cell play(const Board& board, int type);

  };

  // AI strategy
  class AIStrategy: public Strategy {

    public:

      /** 
       * AI paly strategy method
       * 
       * @param board The given Board instance
       * @param type The user type
       * @return The next cell to take
      */
      Cell play(const Board& board, int type);

  }; 
}

#endif