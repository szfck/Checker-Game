#ifndef LIB_GAME_STRATEGY
#define LIB_GAME_STRATEGY

#include "Board.h"
#include "Cell.h"
#include "Constant.h"

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
    virtual std::pair<Cell, Cell> play(const Board &board, int type) = 0;
};

// Human strategy
class PlayerStrategy : public Strategy {

  public:
    /**
     * Human play strategy method
     *
     * @param board The given Board instance
     * @param type The user type
     * @return The next cell to take
     */
    std::pair<Cell, Cell> play(const Board &board, int type);
};

// AI strategy
class AIStrategy : public Strategy {
  private:
    /**
     * @brief alpha_beta_search algorithm entry
     * @param board
     * @param currentPlayer
     * @return best action from start cell to dest cell for next step
     */
    std::pair<Cell, Cell> alpha_beta_search(const Board &board,
                                            int currentPlayer);

    /**
     * @brief actions
     * @param board
     * @param currentPlayer
     * @return all the possibilies to move for the currentPlayer
     */
    std::vector<std::pair<Cell, Cell> > actions(const Board &board,
                                               int currentPlayer);

    /**
     * @brief max_value function in alpha-beta algorithm
     * @param board
     * @param currentPlayer
     * @param alpha
     * @param beta
     * @param level
     * @return best action from start cell to dest cell for max player
     */
    std::pair<int, std::pair<Cell, Cell> > max_value(const Board &board,
                                                    int currentPlayer,
                                                    int alpha, int beta,
                                                    int level);

    /**
     * @brief min_value function in alpha-beta algorithm
     * @param board
     * @param currentPlayer
     * @param alpha
     * @param beta
     * @param level
     * @return best action from start cell to dest cell for min player
     */
    std::pair<int, std::pair<Cell, Cell> > min_value(const Board &board,
                                                    int currentPlayer,
                                                    int alpha, int beta,
                                                    int level);

  public:
    // control alpha beta min max alg difficulty
    // define search max level, if search reach maxlevel, heuristic function
    // will be used the higher the maxLevel is, harder the game is
    int maxLevel;

    // search level
    int searchLevel;

    // number of node generated
    int nodeGen;

    // number of times MAX-VALUE function prune
    int maxPrune;

    // number of times MIN-VALUE function prune
    int minPrune;

    /**
     * AI play strategy method
     *
     * @param board The given Board instance
     * @param type The user type
     * @return The next cell to take
     */
    std::pair<Cell, Cell> play(const Board &board, int type);
};
} // namespace game

#endif
