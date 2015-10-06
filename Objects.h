
#ifndef OBJECTS_H
#define OBJECTS_H

#include "Init.h"

// This are the other 'Object' classes using the design of the 'Blueprint' class and
// inheritanceing from the 'Object_default' class and
// using 'Object_load_parameters' structure to get its Parameters/values.


class Object_player : public Object_default 
{
 public:
 Object_player( Object_load_parameters* params_ptr ) : Object_default(params_ptr) {}

  virtual void Update() 
  {
    Object_default::Update() ;

    // Player Moving:
    m_acceleration.y = 0.1;
    if (( m_position.y > 400 )) {
      m_velocity.y *= -1;
    }

    m_current_frame = (( SDL_GetTicks() / 15 ) % 8 );
    if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
      m_current_row = (( m_current_row + 1 ) % 3 );
    m_last_frame = m_current_frame;
  }

  virtual void Draw() 
  {
    Object_default::Draw();
  }

  virtual void Clean() 
  {
    Object_default::Clean();
  }
};



class Object_enemy : public Object_default
{
 public:
 Object_enemy( Object_load_parameters* params_ptr ) : Object_default(params_ptr) {}

  virtual void Update() 
  {
    Object_default::Update() ;

    m_current_frame = (( SDL_GetTicks() / 150 ) % 8 );
    if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
      m_current_row = (( m_current_row + 1 ) % 3 );
    m_last_frame = m_current_frame;
  }

  virtual void Draw() 
  {
    Object_default::Draw();
  }

  virtual void Clean() 
  {
    Object_default::Clean();
  }
};



#endif
