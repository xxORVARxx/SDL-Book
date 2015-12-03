
#ifndef A_GAME_OBJ_INTERFACE_H
#define A_GAME_OBJ_INTERFACE_H

#include "Init.h"
#include "Camera.h"



// Polymorphism.  Abstract Base Class.
class Game_obj_interface
{
 protected:
  virtual ~Game_obj_interface() {}

 public:
  virtual void Update() = 0;
  virtual void Draw( Camera* _camera ) = 0;
  virtual void Clean() = 0;
};



// This is the default 'Game-object' class which other 'Object' classes can 'inharents' from. 
class Game_obj_default : public Game_obj_interface
{
 public:
  virtual ~Game_obj_default() {}

  // --- Functions ---
  virtual void Update() {}
  virtual void Draw( Camera* _camera ) {}
  virtual void Clean() {}
};



#endif
