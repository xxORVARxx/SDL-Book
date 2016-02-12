
#ifndef A_STATE_INTERFACE_H
#define A_STATE_INTERFACE_H

#include "Init.h"
#include "Camera.h"
#include "A_Game_obj_interface.h"



// Abstract Interface Class:
class State_interface
{
 public:
  virtual ~State_interface() {}
  virtual void on_Enter() = 0;
  virtual void on_Display_resize() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void on_Exit() = 0;
  virtual std::string Get_state_id() const = 0;
};



// Base Class: 
class Base_state : public State_interface
{
 public:
  virtual ~Base_state() {}
  virtual void on_Enter() {}
  virtual void on_Display_resize() {}
  virtual void Update() {}
  virtual void Render() {}
  virtual void on_Exit() 
  {
    // Deleting Oblects:
    std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Base_game_obj* i ){ i->Clean(); delete i; } );
    m_objects_vec.clear();
  }
  virtual std::string Get_state_id() { return sm_state_id; }

 protected:
  const std::string sm_state_id = "BASE";

  Camera m_camera;
  std::vector< Base_game_obj* > m_objects_vec;
};



#endif
