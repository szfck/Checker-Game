#include "Strategy.h"

namespace game {

  Cell PlayerStrategy::play(const Board& board, int type) {
    // TODO get user input
    printf("human playing...\n\n");
    return Cell(1, 1, EMPTY);
  }

  Cell AIStrategy::play(const Board& board, int type) {
    // TODO using error_rate to implement alpha beta alg 
    printf("AI playing...\n\n");
    return Cell(2, 2, EMPTY);
  }

}