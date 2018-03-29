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

    if (currentPlayer->type == PLAYER1) {
      currentPlayer = player2;
    } else {
      currentPlayer = player1;
    }

    if (!board.hasNextLegalStep(currentPlayer->type)) {
     if (currentPlayer->type == PLAYER1) {
        currentPlayer = player2;
      } else {
        currentPlayer = player1;
      }
    }

    return currentPlayer;

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
    if (difficulty == 1) { // easy
      static_cast<AIStrategy*>(player2->strategy)->maxLevel = 3;
    } else if (difficulty == 2) { // medium
      static_cast<AIStrategy*>(player2->strategy)->maxLevel = 6;
    } else { // hard
      static_cast<AIStrategy*>(player2->strategy)->maxLevel = 9;
    }
  }

  void Game::run() {

    while (true) {
      printf("please input the difficulty from 1(easy) to 3(hard)\n\n");
      int diff = -1;
      scanf("%d", &diff);
      if (diff >= 1 && diff <= 3) {
        setDifficulty(diff);
        break;
      }
    }

    while (true) {
      printf("please input first or second you want to play\n first is 0, second is 1\n\n");
      int first;
      scanf("%d", &first);
      if (first == 0) {
        setHumanFirst(true);
        break;
      } else if (first == 1) {
        setHumanFirst(false);
        break;
      }
    }

    printf("game start!\n\n");
    showBoard();

    while (!board.isTerminate()) {
      Player* tmp = getCurrentPlayer();

      if (getCurrentPlayer()->type == PLAYER1) {
        printf("It's your turn, you can start from \n");
        for (int i = 1; i <= board.row; i++) {
          for (int j = 1; j <= board.col; j++) {
            if (board.get(i, j).status != PLAYER1) continue;
            if (!board.getNextLegalCells(board.get(i, j)).empty()) {
              printf("(%d, %d) ", i, j);
            }
          }
        }
        printf("\n\n");
      }

      std::pair<Cell, Cell> cells = tmp->play(board);

      board.take(cells.first, cells.second);

      if (getCurrentPlayer()->type == PLAYER2) {
        printf("AI playing...\n");
      } else {
        printf("Human playing...\n");
      }

      showBoard();

      getNextPlayer();

    }

    showResult(board.gameStatus());

    showBoard();

  }

  // For the command line part (UI use another part)
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

  int Game::gameStatus() {
      return board.gameStatus();
  }

  // For the command line part (UI use another part)
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
