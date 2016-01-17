
#ifndef A_GAME_OBJ_INTERFACE_H
#define A_GAME_OBJ_INTERFACE_H

#include "Init.h"
#include "Camera.h"



// This holds the 'Parameters' to pass through the 'Object' classes.
struct Base_game_obj_parameters
{
  virtual ~Base_game_obj_parameters() {}
};



// Polymorphism.  Abstract Base Class.
class Game_obj_interface
{
 protected:
  virtual ~Game_obj_interface() {}

 public:
  virtual void Load( Base_game_obj_parameters& _obj_params ) = 0;

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
  virtual void Load( Base_game_obj_parameters& _obj_params ) {}

  virtual void Update() {}
  virtual void Draw( Camera* _camera ) {}
  virtual void Clean() {}
};



#endif
