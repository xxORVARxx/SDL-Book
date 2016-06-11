
#include "Events_manager.h"
#include "Parser.h"
#include "Interface_SDL_game_obj.h"

namespace data 
{ 
  std::string Next_line_from_file( std::ifstream& _file );
  Base_SDL_game_obj* Get_object( std::string& _state_name_id, State* _this_state_ptr, std::string& _object_name_id, Base_SDL_game_obj* _this_object_ptr );
}//data



namespace event
{ 
  Events_manager::Events_manager() : m_hook_ptr(nullptr), m_trigger_ptr(nullptr) {}
}//event



namespace event
{ 
  void 
  Events_manager::Parse( std::ifstream& _file, 
			 data::Parser* _p )
  {
    this->Parse_get_trigger( _file, _p );
    this->Parse_get_hook( _file, _p );

    event::i_Link* link_ptr = nullptr;
    try
      {
	link_ptr = m_hook_ptr->Make_link();
	link_ptr->Parse( m_trigger_ptr, _file, _p );
	m_trigger_ptr->Add_link( link_ptr );
      }
    catch( const std::exception& e )
      {
	delete link_ptr;
	throw xx::Parsing_error( std::string( "(xx) Event ERROR! When creating Link!\n\t" ) + e.what());
      }



    if( _p->m_disabled )
      return;
  }
}//event



namespace event
{ 
  void 
  Events_manager::Parse_get_hook( std::ifstream& _file, 
				  data::Parser* _p )
  {
    // Object, State, State machine, World.
    std::string hook_location = std::string( _p->Parse_file< xx::String_cast >( _file ));
    std::string hook_name_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
    if( hook_location == "Object" )
      {
	std::string function = data::Next_line_from_file( _file );
	std::string state_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
	function = data::Next_line_from_file( _file );
	std::string object_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );

	Base_SDL_game_obj* obj = data::Get_object( state_name_id, _p->m_this_state, object_name_id, _p->m_this_object );
	m_hook_ptr = nullptr;
	if( ! obj->Find_hook( hook_name_id, &m_hook_ptr ))
	  throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. The Object Hook: '"+ hook_name_id +"' could not be found! " );
      }
    else if( hook_location == "State" )
      {
	throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. The State Hook: '"+ hook_name_id +"' could not be found! " );
      }
    else if( hook_location == "Global" )
      {
	throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. The Global Hook: '"+ hook_name_id +"' could not be found! " );
      }
    else
      throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. Unexpected: '"+ hook_location +"'. Expected Hook's location: 'Object', 'State' or 'Global'." );
  }
}//event



namespace event
{ 
  void
  Events_manager::Parse_get_trigger( std::ifstream& _file,
				     data::Parser* _p )
  {
    // Object, State, State machine, World.
    std::string trigger_location = std::string( _p->Parse_file< xx::String_cast >( _file ));
    std::string trigger_name_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
    if( trigger_location == "Object" )
      {
	std::string function = data::Next_line_from_file( _file );
	std::string state_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
	function = data::Next_line_from_file( _file );
	std::string object_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );

	Base_SDL_game_obj* obj = data::Get_object( state_name_id, _p->m_this_state, object_name_id, _p->m_this_object );
	m_trigger_ptr = nullptr;
	if( ! obj->Find_trigger( trigger_name_id, &m_trigger_ptr ))
	  throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. A Object Trigger: '"+ trigger_name_id +"' could not be found! " );
      }
    else if( trigger_location == "State" )
      {
	throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. A State Trigger: '"+ trigger_name_id +"' could not be found! " );
      }
    else if( trigger_location == "Global" )
      {
	throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. A Global Trigger: '"+ trigger_name_id +"' could not be found! " );
      }
    else
      throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. Unexpected: '"+ trigger_location +"'. Expected Trigger's location: 'Object', 'State' or 'Global'." );
  }
}//event
