#ifndef LIB_GAME_PLAYER
#define LIB_GAME_PLAYER

#include "Constant.h"
#include "Strategy.h"

namespace game {

  class Player {
    public:

      int type; // User type

      Strategy* strategy; // Pointer to strategy

  };
  
}

#endif