#include "Game.h"

int main() {
  game::Game game;

  game.setDifficulty(1);
  game.setHumanFirst(false);

  game.run();

  return 0;
}