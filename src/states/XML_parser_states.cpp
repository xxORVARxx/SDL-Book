
#include "XML_parser_states.h"
#include "Input_handler.h"
#include "Texture_manager_v2.h"

#include "Game.h"
#include "Game_world.h"
#include "State_main_menu.h"
#include "State_play.h"
#include "State_pause.h"



// Get display size:
float f_display_width( float prosents, float add ) {
  return (( (float)the_World::Instance().Get_display_width() * ( prosents / 100 )) + add );
}
float f_display_height( float prosents, float add ) {
  return (( (float)the_World::Instance().Get_display_height() * ( prosents / 100 )) + add );
}
// Call back functions for 'button-objects':
void f_Menu_to_play() {
  the_Game::Instance().Get_state_machine()->Change_state( new State_play );
}
void f_Exit_from_menu() {
  the_Input_handler::Instance().Quit();
}
void f_Pause_to_main() {
  the_Game::Instance().Get_state_machine()->Pop_state();
  the_Game::Instance().Get_state_machine()->Change_state( new State_main_menu );
}
void f_Pause_to_play() {
  the_Game::Instance().Get_state_machine()->Pop_state();
}
void f_Play_to_pause() {
  the_Game::Instance().Get_state_machine()->Push_state( new State_pause );
}



// Game-Objects use this function to parse different pointers for the addresses:
void Parse_pointer( xml::parser& _p, std::string _expect, void (*&_ptr)() )
{
  _p.next_expect( xml::parser::start_element, _expect, xml::content::complex );

  switch( _p.attribute< xml::parsable_pointer >( "pointer" ))
    {
    case xml::POINTER_EXIT_FROM_MENU :
      _ptr = f_Exit_from_menu;
      break;
    case xml::POINTER_MENU_TO_PLAY :
      _ptr = f_Menu_to_play;
      break;
    case xml::POINTER_PAUSE_TO_MAIN :
      _ptr = f_Pause_to_main;
      break;
    case xml::POINTER_PAUSE_TO_PLAY :
      _ptr = f_Pause_to_play;
      break;
    case xml::POINTER_PLAY_TO_PAUSE :
      _ptr = f_Play_to_pause;
      break;
    default:
      throw xml::parsing( _p, "STATE PARSER :: Invalid parsable_pointer: '" + _expect + "'!" );
    }

  _p.next_expect( xml::parser::end_element );
}



// --- STATE PARSER ---
bool State_parser::Parse_state( const std::string _state_file, std::string _state_id, std::vector< Base_game_obj* >& _objects_vec )
{
  std::ifstream ifs( _state_file );
  if( ! ifs.good())
    {
      std::cout << "STATE PARSER :: ERROR: Fail to open file : "<< _state_file <<" !\n";
      return false;
    }
  try
    {
      std::cout <<"STATE PARSER :: Parsing Started...\n";
      std::cout <<"\tState to parse: '"<< _state_id <<"', using file: '"<< _state_file <<"'\n";

      xml::parser p( ifs, _state_id );

      p.next_expect( xml::parser::start_element, _state_id, xml::content::complex );
      for( xml::parser::event_type event( p.next ()) ; (( p.name() != _state_id )&&( event != xml::parser::eof )) ; event = p.next() )
	{
	  p.content( xml::content::complex );
	  if( event == xml::parser::end_element )
	    continue;
	  else if( event == xml::parser::start_element )
	    {
	      if( p.name() == "TEXTURES" )
		{
		  // Textures:
		  if( this->Parse_textures( p, _objects_vec ) == false )
		    return false;
		}
	      else if( p.name() == "OBJECTS" )
		{
		  // Objects:
		  if( this->Parse_objects( p, _objects_vec ) == false )
		    return false;
		}
	      else
		{
		  std::cout <<"STATE PARSER :: ERROR 2: Only expecting: 'TEXTURES' or 'OBJECTS', not: '"
			    << p.name() <<"'. fix the file: "<< _state_file <<", line nr "<< p.column() <<".\n";
		  return false;
		}
	    }
	  else
	    {
	      std::cout <<"STATE PARSER :: ERROR 1: Not expecting: '"
			<< p.name() <<"'. fix the file: "<< _state_file <<", line nr "<< p.column() <<".\n";
	      return false;
	    }
	}//for-end
    }//try-end
  catch( const xml::parsing& error )
    {
      std::cout << "STATE PARSER :: PARSING ERROR: "<< error.what() <<".\n";
      return false;
    }
  std::cout <<"STATE PARSER :: Parsing Ended Successfully.\n";
  return true;
}



bool State_parser::Parse_textures( xml::parser& _p, std::vector< Base_game_obj* >& _objects_vec )
{
  std::cout <<"\tHere we have some Textures:\n";

  _p.next_expect( xml::parser::start_element, "options" );
  bool Swap_and_clear_texture_map = _p.attribute< bool >( "Swap_and_clear_texture_map" );
  _p.next_expect( xml::parser::end_element );//options

  if( Swap_and_clear_texture_map )
    the_Texture_manager_v2::Instance().Swap_maps();   
  do
    {
      _p.next_expect( xml::parser::start_element, "texture" );

      std::cout <<"\t\tImage: '"<< _p.attribute( "filename" ) <<"',  id: '"<< _p.attribute( "id" ) <<"'.\n";
      the_Texture_manager_v2::Instance().Move_or_load_texture( the_Game::Instance().Get_renderer(), 
							       _p.attribute( "id" ), 
							       _p.attribute( "filename" ));

      _p.next_expect( xml::parser::end_element );//texture
    } while( _p.peek () == xml::parser::start_element );

  if( Swap_and_clear_texture_map )
    the_Texture_manager_v2::Instance().Clear_map();
  return true;
}



bool State_parser::Parse_objects( xml::parser& _p, std::vector< Base_game_obj* >& _objects_vec )
{
  std::cout <<"\tHere we have some objects:\n";
  do
    {
      _p.next_expect( xml::parser::start_element, "object", xml::content::complex );

      fac::game_object object_type = _p.attribute< fac::game_object >( "type" );
      Base_game_obj* the_object = the_Factory_game_obj::Instance().Create( object_type );

      std::cout <<"\t\tObject:  ";
      the_object->Parse( _p );
      std::cout <<"\n";

      _objects_vec.push_back( the_object );

      _p.next_expect( xml::parser::end_element );//object
    } while( _p.peek () == xml::parser::start_element );

  return true;
}
