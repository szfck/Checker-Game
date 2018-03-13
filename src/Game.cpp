#include "Game.h"
#include "Strategy.h"
#include "Board.h"
#include <iostream>
#include <time.h>

namespace game {

  Game::Game() {

    srand(time(NULL));

    player1 = new Player("Human player", PLAYER1, new PlayerStrategy);

    player2 = new Player("AI Player", PLAYER2, new AIStrategy);

    board.init(6, 6);
  }

  bool Game::hasNextLegalStep(Player* player) {
    for (int i = 1; i <= board.row; i++) {
      for (int j = 1; j <= board.col; j++) {
        if (board.get(i, j).status == player->type 
            && !board.getNextLegalCells(board.get(i, j)).empty()) {
              return true;
            }
      }
    }
    return false;
  }

  int Game::cellRemain(Player* player) {
    int count = 0;
    for (int i = 1; i <= board.row; i++) {
      for (int j = 1; j <= board.col; j++) {
        if (board.get(i, j).status == player->type) {
          count++;
        }
      }
    }
    return count;
  }

  Player* Game::getNextPlayer() {

    if (!hasNextLegalStep(currentPlayer)) {
     if (currentPlayer->type == PLAYER1) {
        currentPlayer = player2;
      } else {
        currentPlayer = player1;
      } 
    }

    Player* tmp = currentPlayer;

    if (currentPlayer->type == PLAYER1) {
      currentPlayer = player2;
    } else {
      currentPlayer = player1;
    }
    return tmp;

  }

  Player* Game::getCurrentPlayer() {
    return currentPlayer;
  }
  
  void Game::setHumanFirst (bool humanFirst) {

    if (humanFirst) {
      currentPlayer = player1;
    } else {
      currentPlayer = player2;
    }

  }

  void Game::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
    if (difficulty == 1) { // easy, 67% error rate
      static_cast<AIStrategy*>(player2->strategy)->error_rate = 0.67;
    } else if (difficulty == 2) { // medium, 33% error rate
      static_cast<AIStrategy*>(player2->strategy)->error_rate = 0.33;
    } else { // hard, no error
      static_cast<AIStrategy*>(player2->strategy)->error_rate = 0.0;
    }
  }

  void Game::run() {

    int result;

    while ((result = isFinished()) == NONE) {

      showBoard();

      Player* tmp = getNextPlayer();

      printf("player: %d\n", tmp->type);

      std::pair<Cell, Cell> cells = tmp->play(board);

      board.take(cells.first, cells.second);

    }

    showResult(result);

    showBoard();

  }

  // TODO change to UI part
  void Game::showResult(int result) {
    if (result == FIRSTWIN) {
      printf("%s wins\n", player1->name.c_str());
    } else if (result == SECONDWIN) {
      printf("%s wins\n", player2->name.c_str());
    } else if (result == DRAW) {
      printf("draw\n");
    } else {
      printf("bug!!!!!!!\n");
    }
  }

  int Game::isFinished() {
    int res;

    int player1CellNumber = cellRemain(player1);
    int player2CellNumber = cellRemain(player2);
    if (player1CellNumber == 0) return SECONDWIN;
    else if (player2CellNumber == 0) return FIRSTWIN;
    else if (!hasNextLegalStep(player1) && !hasNextLegalStep(player2)) {
      if (player1CellNumber > player2CellNumber) return FIRSTWIN;
      else if (player1CellNumber < player2CellNumber) return SECONDWIN;
      else return DRAW;
    } else {
      return NONE;
    }
    return res;
  }

  // TODO change to UI show
  void Game::showBoard() {
    for (int i = board.row; i >= 1; i--) {
      std::string line = "";
      for (int j = 1; j <= board.col; j++) {
        if (board.get(i, j).status == PLAYER2) {
          line += '2';
        } else if (board.get(i, j).status == PLAYER1) {
          line += '1';
        } else {
          line += '_';
        }
      }
      std::cout << line << std::endl;
    }
    std::cout << std::endl;
  }
}
