#include "Strategy.h"
#include <set>

namespace game {

  // TODO receive UI click
  std::pair<Cell, Cell> PlayerStrategy::play(const Board& board, int type) {
    printf("human playing...\n\n");

    int sx, sy, dx, dy;
    while (true) {
      printf("please input the start (x, y)coordinate to take...\n\n");

      scanf("%d%d", &sx, &sy);
      // printf("sx :%d, sy:%d\n", sx, sy);
      // printf("type: %d\n", type);
      // printf("isvalid : %d\n", board.isValidType(sx, sy, type));
      if (board.isValidType(sx, sy, type) && !board.getNextLegalCells(board.get(sx, sy)).empty()) {
        printf("Select start (%d, %d)\n\n", sx, sy);
        break;
      } else {
        printf("Not a valid position, please input again\n\n");
      }

    }

    auto nextList = board.getNextLegalCells(board.get(sx, sy));

    printf("please select dest in the list below\n");
    std::set<std::pair<int, int>> choose;
    for (auto cell : nextList) {
      choose.insert(std::make_pair(cell.x, cell.y));
      printf("(%d, %d)\n", cell.x, cell.y);
    }

    while (true) {
      scanf("%d%d", &dx, &dy);
      if (choose.find(std::make_pair(dx, dy)) == choose.end()) {
        printf("Not a valid position, please input again\n\n");
      } else {
        printf("Select dest (%d, %d)\n\n", dx, dy);
        break;
      }
    }

    return std::make_pair(board.get(sx, sy), board.get(dx, dy));
  }

  std::pair<Cell, Cell> AIStrategy::play(const Board& board, int type) {
    // TODO using error_rate to implement alpha beta alg 
    // printf("AI playing...\n\n");
    auto mock = new PlayerStrategy;
    return mock->play(board, type);
  }

}