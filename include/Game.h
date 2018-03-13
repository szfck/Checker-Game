#ifndef LIB_GAME_GAME
#define LIB_GAME_GAME

#include "Constant.h"
#include "Strategy.h"
#include "Player.h"
#include "Board.h"
#include "Cell.h"
#include <vector>

namespace game {

  class Game {
    private:

      Player* currentPlayer;

      Player* getNextPlayer();

      bool hasNextLegalStep(Player* player);

      int cellRemain(Player* player);
      
      Board board;

    public:

      // Game difficulty from 1(easy) to 3(hard)
      int difficulty; 

      // First player to play
      Player* player1; 

      // Second player to play
      Player* player2; 

      /**
       * Construct
       * 
       * Create instance of player1(User) and player2(AI)
      */
      Game();

      /**
       * To set human player play first or second
       * 
       * @param humanFirst true human play first, otherwise play second
      */
      void setHumanFirst(bool humanFirst);

      /**
       * To set game difficulty, from 1(easy) to 3(hard)
       * @param difficulty
      */ 
      void setDifficulty(int difficulty);

      /**
       * Check if the game is finished or not
       * 
       * @return Game status FIRSTWIN/SECONDWIN/DRAW/NONE
      */
      int isFinished();

      /**
       * Show the game result
       * @param result type of the result
      */
      void showResult(int result);

      /**
       * Main function to run the game
      */
      void run();

  };
  
}

#endif