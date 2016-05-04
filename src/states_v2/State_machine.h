
#ifndef STATE_MACHINE_H 
#define STATE_MACHINE_H

#include "Init.h"
#include "State.h"



enum SMF
  {
    CREATE_AT_FRONT, //  ( "filename", "", "" )
    CREATE_FRONT_OF, //  ( "filename", "", "destination_id" )
    CREATE_BEHIND_OF, // ( "filename", "", "destination_id" )
    CREATE_AT_BACK, //   ( "filename", "", "" )

    LOAD_AT_FRONT, //  ( "filename", "", "" )
    LOAD_FRONT_OF, //  ( "filename", "", "destination_id" )
    LOAD_BEHIND_OF, // ( "filename", "", "destination_id" )
    LOAD_AT_BACK, //   ( f"ilename", "", "" )

    MOVE_TO_FRONT, //  ( "", "id", "" )
    MOVE_FORWARD, //   ( "", "id", "" )
    MOVE_FRONT_OF, //  ( "", "id", "destination_id" )
    MOVE_BEHIND_OF, // ( "", "id", "destination_id" )
    MOVE_BACKWARD, //  ( "", "id", "" )
    MOVE_TO_BACK, //   ( "", "id", "" )

    REMOVE, //       ( "", "id", "" )
    REMOVE_FRONT, // ( "", "",   "" )
    REMOVE_BACK, //  ( "", "",   "" )
    REMOVE_ALL //    ( "", "",   "" )
  };



struct SMF_parameters
{
  SMF_parameters();
  SMF_parameters( SMF _f, std::string _n, std::string _i, std::string _d ) : 
    function(_f), filename(_n), id(_i), destination_id(_d) {}
  SMF function;
  std::string filename;
  std::string id;
  std::string destination_id;
};



// Finite State Machine (FSM):
class State_machine
{
public:
  // --- Functions ---
  void To_do( SMF_parameters function );
  void Flush();

  void Update();
  void Render();
  void Clean();

  bool Has_state( const std::string _id, State* _state );

  void Print()
  {
    for( auto itr = m_state_vec.begin() ; itr != m_state_vec.end() ; ++itr )
      std::cout <<"'"<< (*itr)->Get_id() <<"'    ";
    std::cout <<"\n";
  }

private:
  State* Create_state( const std::string& _filename );
  State* Load_state( const std::string& _filename );

  void Put_at_front( State* _state_ptr );
  void Put_front_of( State* _state_ptr, const std::string& _id );
  void Put_behind_of( State* _state_ptr, const std::string& _id );
  void Put_at_back( State* _state_ptr );

  void Move_to_front( const std::string& _id );
  void Move_forward( const std::string& _id );
  void Move_front_of( const std::string& _id, const std::string& _destination_id );
  void Move_behind_of( const std::string& _id, const std::string& _destination_id );
  void Move_backward( const std::string& _id );
  void Move_to_back( const std::string& _id );

  void Remove( const std::string& _id );
  void Remove_front();
  void Remove_back();
  void Remove_all();

  std::vector< State* >::iterator Find( const std::string _id );

  // --- Variables ---
  std::vector< State* > m_state_vec;
  std::vector< SMF_parameters > m_todo_list;
};



#endif
