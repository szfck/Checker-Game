#include "Player.h"
#include "Constant.h"
#include <string>

namespace game {

Player::Player(std::string name, int type, Strategy *strategy) {
    this->name = name;
    this->type = type;
    this->strategy = strategy;
}

std::pair<Cell, Cell> Player::play(const Board &board) {
    return strategy->play(board, type);
}

} // namespace game