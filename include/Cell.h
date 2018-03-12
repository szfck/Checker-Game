#ifndef LIB_GAME_CELL
#define LIB_GAME_CELL

namespace game {

  class Cell {

    public:

      int x, y;

      int status;

      Cell();

      Cell(int x, int y, int status);
  };
  
}

#endif