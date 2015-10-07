
#ifndef OBJECTS_H
#define OBJECTS_H

#include "Init.h"

// This are the other 'Object' classes using the design of the 'Blueprint' class and
// inheritanceing from the 'Object_default' class and
// using 'Object_load_parameters' structure to get its Parameters/values.



class Player : public Object_default 
{
 public:
 Player( Object_load_parameters* params_ptr ) : Object_default(params_ptr) {
    // Seting keys:
    move_up_key =    SDL_SCANCODE_W ;
    move_down_key =  SDL_SCANCODE_S ;
    move_right_key = SDL_SCANCODE_D ;
    move_left_key =  SDL_SCANCODE_A ;
  }

  virtual void Update();
  virtual void Draw() { Object_default::Draw(); }
  virtual void Clean() { Object_default::Clean(); }

 private:
  void Hendle_input();

  // --- Variables ---
  Uint8 move_up_key, move_down_key, move_right_key, move_left_key;
};



class Enemy : public Object_default
{
 public:
 Enemy( Object_load_parameters* params_ptr ) : Object_default(params_ptr) {}

  virtual void Update();
  virtual void Draw() { Object_default::Draw(); }
  virtual void Clean() { Object_default::Clean(); }

 private:
  void Hendle_input();
};



#endif
