
#ifndef OBJECTS_H
#define OBJECTS_H

#include "Init.h"
#include "Objects_blueprint.h"

// This are the other 'Object' classes using the design of the 'Blueprint' class and
// inheritanceing from the 'Object_default' class and
// using 'Object_load_parameters' structure to get its Parameters/values.



// --- BUTTON ---
class Button : public Object_default 
{
 public:
  Button( Object_load_parameters* params_ptr );

  virtual void Update();
  virtual void Draw() { Object_default::Draw(); }
  virtual void Clean() { std::cout << "BUTTON :: Clean() is Done,  &  "; Object_default::Clean(); }

 private:
  enum button_state
  {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    MOUSE_CLICKED = 2,
    MOUSE_CLICK_RELEASED = 3
  };
};



// --- PLAYER ---
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
  virtual void Clean() { std::cout << "PLAYER :: Clean() is Done,  &  "; Object_default::Clean(); }

 private:
  void Hendle_input();

  // --- Variables ---
  Uint8 move_up_key, move_down_key, move_right_key, move_left_key;
};



// --- ENEMY ---
class Enemy : public Object_default
{
 public:
 Enemy( Object_load_parameters* params_ptr ) : Object_default(params_ptr) {}

  virtual void Update() { Object_default::Update(); }
  virtual void Draw();
  virtual void Clean() { std::cout << "ENEMY :: Clean() is Done,  &  "; Object_default::Clean(); }
};



#endif

/*
These variables are 'inherit' from the 'Object_default' class:
  SDL_RendererFlip m_texture_flip;
  glm::vec2 m_acceleration;
  glm::vec2 m_velocity;
  glm::vec2 m_position;
  int m_w;
  int m_h;
  int m_current_frame;
  int m_last_frame;
  int m_current_row;
*/
