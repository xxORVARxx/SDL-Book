
#ifndef STATE_PLAY_H
#define STATE_PLAY_H

#include "Init.h"
#include "A_State_interface.h"



// --- PLAY STATE ---
class State_play : public Base_state
{
 public:
  virtual ~State_play() {}
  virtual void on_Enter();
  virtual void on_Display_resize() {}
  virtual void Update();
  virtual void Render();
  virtual void on_Exit();
  virtual std::string Get_state_id() const { return sm_state_id; };

 private:
  static const std::string sm_state_id;
};



#endif
