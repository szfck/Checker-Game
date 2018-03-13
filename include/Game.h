#ifndef LIB_GAME_GAME
#define LIB_GAME_GAME

#include "Constant.h"
#include "Strategy.h"
#include "Player.h"
#include "Board.h"

namespace game {

  class Game {
    private:
      int counter = 0;
      // control alpha beta min max alg difficulty
      // the higher the error_rate is, eaiser the game is
      double error_rate;

      Player* currentPlayer;

      Player* getNextPlayer();

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
       * Set game board
       * @param board
      */
      void setBoard(const Board& board);

      /**
       * Check if the game is finished or not
       * 
       * @param board Board instance
       * @return Game status FIRSTWIN/SECONDWIN/DRAW/NONE
      */
      int isFinished(const Board& board);

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