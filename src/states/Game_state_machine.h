
#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "Init.h"
#include "Game_states.h"



// Finite State Machine (FSM):
class Game_state_machine
{
 public:
 Game_state_machine() : m_refresh(false) {}

  void Push_state( Game_states_blueprint* _state_ptr );
  void Change_state( Game_states_blueprint* _state_ptr );
  void Pop_state();

  void Update();
  void Render();
  void Clean();

 private:
  void Delete_and_remove_state();
  void Add_and_begin_state( Game_states_blueprint* _state_ptr );
  void Refresh();

  bool m_refresh;
  std::vector< Game_states_blueprint* > m_states_vec;
  std::vector< Game_states_blueprint* > m_state_change_vec;
};



#endif
