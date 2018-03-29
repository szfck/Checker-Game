#include "Strategy.h"
#include <cassert>
#include <set>

namespace game {

// For the command line interaction
std::pair<Cell, Cell> PlayerStrategy::play(const Board &board, int type) {
    // printf("human playing...\n\n");

    int sx, sy, dx, dy;
    while (true) {
        printf("please input the start (x, y)coordinate to take...\n\n");

        scanf("%d%d", &sx, &sy);
        if (board.isValidType(sx, sy, type) &&
            !board.getNextLegalCells(board.get(sx, sy)).empty()) {
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

std::pair<Cell, Cell> AIStrategy::play(const Board &board, int type) {

    return alpha_beta_search(board, type);
}

std::pair<Cell, Cell> AIStrategy::alpha_beta_search(const Board &board,
                                                    int currentPlayer) {
    assert(currentPlayer == PLAYER2);

    searchLevel = 0;
    nodeGen = 0;
    maxPrune = minPrune = 0;

    auto ans = max_value(board, currentPlayer, -Inf, Inf, 0);
    auto res = ans.second;
    return res;
}

std::pair<int, std::pair<Cell, Cell>> AIStrategy::max_value(const Board &board,
                                                            int currentPlayer,
                                                            int alpha, int beta,
                                                            int level) {
    searchLevel = std::max(level, searchLevel);
    nodeGen++;
    if (board.isTerminate() || level >= maxLevel) {
        return {board.utility(currentPlayer), {}};
    }
    int value = -Inf;
    Cell maxstart, maxdest;
    for (auto next : actions(board, currentPlayer)) {
        Board tmpboard = board;
        Cell start = next.first, dest = next.second;
        tmpboard.take(start, dest);
        auto result =
            min_value(tmpboard, currentPlayer ^ 1, alpha, beta, level + 1);

        if (result.first >= value) {
            value = result.first;
            maxstart = start;
            maxdest = dest;
        }
        assert(value >= -Inf && value <= Inf);
        if (value >= beta) {
            return {value, {maxstart, maxdest}};
        }

        alpha = std::max(alpha, value);
    }
    return {value, {maxstart, maxdest}};
}

std::pair<int, std::pair<Cell, Cell>> AIStrategy::min_value(const Board &board,
                                                            int currentPlayer,
                                                            int alpha, int beta,
                                                            int level) {
    searchLevel = std::max(level, searchLevel);
    nodeGen++;
    if (board.isTerminate() || level >= maxLevel) {
        return {board.utility(currentPlayer), {}};
    }
    int value = Inf;
    Cell minstart, mindest;
    for (auto next : actions(board, currentPlayer)) {
        Board tmpboard = board;
        Cell start = next.first, dest = next.second;
        tmpboard.take(start, dest);
        auto result =
            max_value(tmpboard, currentPlayer ^ 1, alpha, beta, level + 1);
        if (result.first <= value) {
            value = result.first;
            minstart = start;
            mindest = dest;
        }
        assert(value >= -Inf && value <= Inf);
        if (value <= alpha) {
            return {value, {minstart, mindest}};
        }

        beta = std::min(beta, value);
    }
    return {value, {minstart, mindest}};
}

std::vector<std::pair<Cell, Cell>> AIStrategy::actions(const Board &board,
                                                       int currentPlayer) {
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
} // namespace game
