#include "Game.h"

int main() {
  game::Game game;

  game.setDifficulty(1);
  game.setHumanFirst(true);

  game.run();

  return 0;
}