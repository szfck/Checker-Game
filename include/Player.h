#ifndef LIB_GAME_PLAYER
#define LIB_GAME_PLAYER

#include "Constant.h"
#include "Strategy.h"
#include <string>

namespace game {

class Player {
  public:
    std::string name;

    int type;

    Strategy *strategy; // Pointer to strategy

    Player(std::string name, int type, Strategy *strategy);

    /**
     * @brief play
     * @param board
     * @return next pair of start and dest position of cell after playing
     */
    std::pair<Cell, Cell> play(const Board &board);
};

} // namespace game

#endif
