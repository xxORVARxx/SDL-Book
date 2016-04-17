
#ifndef STATE_MACHINE_H 
#define STATE_MACHINE_H

#include "Init.h"
#include "State.h"



// Finite State Machine (FSM):
class State_machine
{
public:
  // --- Functions ---
  void Create_at_front( const std::string _filename );
  void Create_front_of( const std::string _filename, const std::string _id );
  void Create_behind_of( const std::string _filename, const std::string _id );
  void Create_at_back( const std::string _filename );

  void Load_at_front( const std::string _filename ) {}
  void Load_front_of( const std::string _filename, const std::string _id ) {}
  void Load_behind_of( const std::string _filename, const std::string _id ) {}
  void Load_at_back( const std::string _filename ) {}

  void Move_to_front( const std::string _id );
  void Move_forward( const std::string _id );
  void Move_front_of( const std::string _id );
  void Move_behind_of( const std::string _id );
  void Move_backward( const std::string _id );
  void Move_to_back( const std::string _id );

  void Remove( const std::string _id );
  void Remove_front();
  void Remove_back();
  void Remove_all();

  void Update();
  void Render();
  void Clean();

private:
  std::vector< State >::iterator Find( const std::string _id );
  void Refresh();

  // --- Variables ---
  std::string m_changes;
  std::vector< State > m_state_vec;
};



#endif
