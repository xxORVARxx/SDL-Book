
#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "Init.h"
#include "Game_states.h"



// Finite State Machine (FSM):
class Game_state_machine
{
 public:
  void Push_state( State_blueprint* state_ptr );
  void Change_state( State_blueprint* state_ptr );
  void Pop_state();

 private:
  std::vector< State_blueprint* > m_states_vec;
};



#endif
