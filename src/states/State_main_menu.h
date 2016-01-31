
#ifndef STATE_MAIN_MENU_H
#define STATE_MAIN_MENU_H

#include "Init.h"
#include "A_State_interface.h"

class Base_game_obj;



// --- MAIN MENU STATE ---
class State_main_menu : public State_interface
{
 public:
  virtual ~State_main_menu() {}
  virtual void on_Enter();
  virtual void on_Display_resize();
  virtual void Update();
  virtual void Render();
  virtual void on_Exit();
  virtual std::string Get_state_id() const { return sm_main_menu_id; }

 private:
  static const std::string sm_main_menu_id;

  std::vector< Base_game_obj* > m_objects_vec;

  // Call back functions for menu items:
  static void smf_Menu_to_play();
  static void smf_Exit_from_menu();
};



#endif
