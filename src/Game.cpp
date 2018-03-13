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

  Player* Game::getNextPlayer() {

    Player* tmp = currentPlayer;

    if (currentPlayer->type == PLAYER1) {
      currentPlayer = player2;
    } else {
      currentPlayer = player1;
    }
    return tmp;
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

    while ((result = isFinished(board)) == NONE) {

      Cell cell = getNextPlayer()->play(board);
      board.set(cell.x, cell.y, cell);

      board.show();
    }

    showResult(result);

  }

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

  int Game::isFinished(const Board& board) {
    // TODO check board status
    int res;
    if (rand() % 10 > 6) {
      res = rand() % (NONE - FIRSTWIN) + FIRSTWIN;
    } else {
      res = NONE;
    }
    return res;
  }
}