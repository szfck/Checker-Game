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
//    auto mock = new PlayerStrategy;
//      return std::make_pair(board.get(5, 1), board.get(4, 2));
//    return mock->play(board, type);
//       const int WIN = 1, LOSE = -1, DRAW = 0;
    printf("start using min max alg\n");

    return alpha_beta_search(board, type);

  }

  std::pair<Cell, Cell> AIStrategy::alpha_beta_search(const Board &board, int currentPlayer) {

      count = 100000;

      auto res = max_value(board, currentPlayer, -1, 1, 0).second;

      printf("find next from (%d,%d), to (%d, %d)\n", res.first.x, res.first.y, res.second.x, res.second.y);
      return res;
  }

  std::pair<int, std::pair<Cell, Cell>> AIStrategy::max_value(const Board& board, int currentPlayer, int alpha, int beta, int level) {
      count--;

      if (count <= 0) return {-1, {}};

      // printf("max function at %d!\n", level);

      if (board.terminateTest()) return {board.utility(), {}};
      int value = -1;
      Cell maxstart, maxdest;
      for (auto next : actions(board, currentPlayer)) {
          Board tmpboard = board;
          Cell start = next.first, dest = next.second;
          tmpboard.take(start, dest);
          auto result = min_value(tmpboard, currentPlayer ^ 1, alpha, beta, level + 1);
          if (result.first >= value) {
              value = result.first;
              maxstart = start;
              maxdest = dest;
          }
          if (value >= beta) {
              return {value, {maxstart, maxdest}};
          }

          alpha = std::max(alpha, value);

      }
      return {value, {maxstart, maxdest}};
  }

  std::pair<int, std::pair<Cell, Cell>> AIStrategy::min_value(const Board& board, int currentPlayer, int alpha, int beta, int level) {
      count--;

      if (count <= 0) return {-1, {}};

      // printf("min function at %d!\n", level);

      if (board.terminateTest()) return {board.utility(), {}};
      int value = 1;
      Cell minstart, mindest;
      for (auto next : actions(board, currentPlayer)) {
          Board tmpboard = board;
          Cell start = next.first, dest = next.second;
          tmpboard.take(start, dest);
          auto result = max_value(tmpboard, currentPlayer ^ 1, alpha, beta, level + 1);
          if (result.first <= value) {
              value = result.first;
              minstart = start;
              mindest = dest;
          }
          if (value <= alpha) {
              return {value, {minstart, mindest}};
          }

          beta = std::min(beta, value);

      }
      return {value, {minstart, mindest}};
  }

  std::vector<std::pair<Cell, Cell>> AIStrategy::actions(const Board &board, int currentPlayer) {
      std::vector<std::pair<Cell, Cell>> actionList;
      for (int i = 1; i <= board.row; i++) {
          for (int j = 1; j <= board.col; j++) {
              Cell start = board.get(i, j);
              if (start.status == currentPlayer) {

                  auto nextStep = board.getNextLegalCells(start);

                  for (auto next : nextStep) {
                      actionList.push_back(std::make_pair(start, next));
                  }

              }
          }
      }
      return actionList;
  }

}
