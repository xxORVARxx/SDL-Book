
#ifndef STATE_PLAY_H
#define STATE_PLAY_H

#include "Init.h"
#include "A_State_interface.h"
#include "Camera.h"

class Game_obj_default;



// --- PLAY STATE ---
class State_play : public State_interface
{
 public:
  virtual ~State_play() {}
  virtual void on_Enter();
  virtual void on_Display_resize() {}
  virtual void Update();
  virtual void Render();
  virtual void on_Exit();
  virtual std::string Get_state_id() const { return sm_menu_id; };

 private:
  static const std::string sm_menu_id;

  Camera m_camera;
  std::vector< Game_obj_default* > m_objects_vec;
  // Call back functions for menu items:
  static void smf_Play_to_pause();
};



#endif
