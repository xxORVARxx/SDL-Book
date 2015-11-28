
#ifndef A_GAME_OBJ_INTERFACE_H
#define A_GAME_OBJ_INTERFACE_H

#include "Init.h"



// Polymorphism.  Abstract Base Class.
class Game_obj_interface
{
 protected:
  virtual ~Game_obj_interface() {}

 public:
  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual void Clean() = 0;
};



#endif
