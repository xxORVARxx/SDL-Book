
#ifndef STATE_PAUSE_H
#define STATE_PAUSE_H

#include "Init.h"
#include "A_State_interface.h"

class Game_obj_default;



// --- PAUSE STATE ---
class State_pause : public State_interface
{
 public:
  virtual ~State_pause() {}
  virtual void on_Enter();
  virtual void on_Display_resize();
  virtual void Update();
  virtual void Render();
  virtual void on_Exit();
  virtual std::string Get_state_id() const { return sm_pause_id; }

 private:
  static const std::string sm_pause_id;

  std::vector< Game_obj_default* > m_objects_vec;

  // Call back functions for pause items:
  static void smf_Pause_to_main();
  static void smf_Pause_to_play();
};



#endif
