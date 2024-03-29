#ifndef LIB_GAME_GAME
#define LIB_GAME_GAME

#include "Board.h"
#include "Cell.h"
#include "Constant.h"
#include "Player.h"
#include "Strategy.h"
#include <vector>

namespace game {

class Game {
  private:
    Player *currentPlayer;

  public:
    Board board;

    // Game difficulty from 1(easy) to 3(hard) int difficulty;
    int difficulty;

    // First player to play
    Player *player1;

    // Second player to play
    Player *player2;

    Player *getNextPlayer();

    Player *getCurrentPlayer();

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
    int gameStatus();

    /**
     * Show the game result
     * @param result type of the result
     */
    void showResult(int result);

    /**
     * Main function to run the game
     */
    void run();

    /**
     * Show the board in command line
     */
    void showBoard();

    /**
     * Show information in AI algorithm
     */  
    std::string getAIInfo();
};

} // namespace game

#endif
