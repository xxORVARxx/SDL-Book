 
#include "Init.h"
#include "Game.h"
#include "State.h"
#include "Interface_SDL_game_obj.h"



namespace data
{
  void 
  Throw_invalid_argument( std::string the_corrupted_input )
  {
    throw std::invalid_argument( "(xx) Parsing ERROR! Nothing to do with: '" + the_corrupted_input + "', corrupted input from file! " );
  }

  void 
  Throw_file_corrupted( std::string _str = " " )
  {
    throw std::ios::failure( "(xx) Parsing ERROR! file corrupted! " + _str );
  }
}//data



namespace data
{
  bool 
  Is_template( std::string& _function )
  {
    for( auto i = _function.rbegin() ; (*i) != '(' ; ++i )
      {
	if( (*i) == 'T' )
	  return true;
      }//for
    return false;
  }

  void
  Comment( std::ifstream& _file, 
	   std::string& _comment )
  {
    bool comment_found = false;
    while( _file.good())
      {
	for( size_t i = 0 ; (( ! comment_found )&&( i < _comment.size() ))  ; ++i )
	  {
	    if( _comment[i] != '#' )
	      {
		comment_found = true;
		break;
	      }
	  }//for
	if( comment_found &&( *_comment.rbegin() == '#' ))
	  return;
	_file >> _comment;
      }//while
    data::Throw_file_corrupted( " in Comment. " );
  }

  std::string 
  Check_for_comments( std::ifstream& _file, 
		      std::string& _str )
  {
    while( *_str.begin() == '#' )
      {
	data::Comment( _file, _str );
	_file >> _str;
	if( ! _file.good())
	  data::Throw_file_corrupted( " When Checking for Comments. " );
      }
    return _str;
  }

  std::string
  Next_line_from_file( std::ifstream& _file )
  {
    std::string line;
    _file >> line;
    if( ! _file.good())
      data::Throw_file_corrupted();
    line = data::Check_for_comments( _file, line );
    return line;
  }
}//data



namespace data
{
  State* 
  Get_state( std::string& _state_name_id, 
	     State* _this_state_ptr )
  {
    if( _this_state_ptr )
      if( _state_name_id == _this_state_ptr->Get_id())
	return _this_state_ptr;
    if( the_Game::Instance().Get_state_machine()->Has_state( _state_name_id, _this_state_ptr ))
      return _this_state_ptr;
    throw std::invalid_argument( "(xx) Parsing ERROR! No state with the name-id: '" + _state_name_id + "'! " );
  }

  Base_SDL_game_obj* 
  Get_object( std::string& _state_name_id, 
	      State* _this_state_ptr, 
	      std::string& _object_name_id, 
	      Base_SDL_game_obj* _this_object_ptr )
  {
    if( _this_object_ptr )   
      if( _object_name_id == _this_object_ptr->Get_name_id())
	return _this_object_ptr;
    _this_object_ptr = ( data::Get_state( _state_name_id, _this_state_ptr )->Find_object( _object_name_id ));
    if( _this_object_ptr )
      return _this_object_ptr;
    throw std::invalid_argument( "(xx) Parsing ERROR! No object with the name-id: '" + _object_name_id + "'! " );
  }
}//data
