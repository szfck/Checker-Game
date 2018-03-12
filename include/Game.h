#ifndef LIB_GAME_GAME
#define LIB_GAME_GAME

#include "Constant.h"
#include "Strategy.h"
#include "Player.h"
#include "Board.h"

namespace game {

  class Game {

    public:

      int difficulty; // Game difficulty from 1(easy) to 3(hard)

      Player player1; // First player to play

      Player player2; // Second player to play

      /**
       * To set human player play first or second
       * 
       * @param humanFirst true human play first, otherwise play second
      */
      void setHumanFirst(bool humanFirst);

      /**
       * Check if the game is finished or not
       * 
       * @param board Board instance
       * @return true if game is end, false otherwise
      */
      bool isFinished(const Board& board);

      /**
       * Main function to run the game
      */
      void run();

  };
  
}

#endif