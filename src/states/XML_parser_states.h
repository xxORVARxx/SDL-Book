 
#ifndef XML_PARSER_STATES_H
#define XML_PARSER_STATES_H

#include "Init.h"
#include "A_Game_obj_interface.h"
#include "Factory_game_obj.h"



// These are all the 'types', 'functions' and 'pointers'
// that can be used in the XML-files to parse the states:
namespace xml
{
  enum parsable_type
  {
    INT,
    UINT,
    FLOAT,
    DOUBLE,

    RANDOM_INT,
    RANDOM_UINT,
    RANDOM_FLOAT,
    RANDOM_DOUBLE,

    FUNCTION_DISPLAY_WIDTH,
    FUNCTION_DISPLAY_HEIGHT
  };

  enum parsable_pointer
  {
    POINTER_EXIT_FROM_MENU,
    POINTER_MENU_TO_PLAY,
    POINTER_PAUSE_TO_MAIN,
    POINTER_PAUSE_TO_PLAY,
    POINTER_PLAY_TO_PAUSE
  };
}


// Make the 'Parser' convert from 'String/Text' to 'enum', to enforces type-checking & type-safety.
namespace xml
{
  template <>
    struct value_traits< xml::parsable_type >
    {
      static xml::parsable_type parse( std::string _str, const parser& _p )
      {
	if( _str == "INT" )
	  return xml::INT;
	else if( _str == "UINT" )
	  return xml::UINT;
	else if( _str == "FLOAT" )
	  return xml::FLOAT;
	else if( _str == "DOUBLE" )
	  return xml::DOUBLE;

	else if( _str == "RANDOM_INT" )
	  return xml::RANDOM_INT;
	else if( _str == "RANDOM_UINT" )
	  return xml::RANDOM_UINT;
	else if( _str == "RANDOM_FLOAT" )
	  return xml::RANDOM_FLOAT;
	else if( _str == "RANDOM_DOUBLE" )
	  return xml::RANDOM_DOUBLE;

	else if( _str == "FUNCTION_DISPLAY_WIDTH" )
	  return xml::FUNCTION_DISPLAY_WIDTH;
	else if( _str == "FUNCTION_DISPLAY_HEIGHT" )
	  return xml::FUNCTION_DISPLAY_HEIGHT;
	else
	  throw xml::parsing( _p, "STATE PARSER :: Invalid parsable_type: '" + _str + "'!" );
      }
    };

  template <>
    struct value_traits< xml::parsable_pointer >
    {
      static xml::parsable_pointer parse( std::string _str, const parser& _p )
      {
        if( _str == "POINTER_EXIT_FROM_MENU" )
	  return xml::POINTER_EXIT_FROM_MENU;
	else if( _str == "POINTER_MENU_TO_PLAY" )
	  return xml::POINTER_MENU_TO_PLAY;
	else if( _str == "POINTER_PAUSE_TO_MAIN" )
	  return xml::POINTER_PAUSE_TO_MAIN;
	else if( _str == "POINTER_PAUSE_TO_PLAY" )
	  return xml::POINTER_PAUSE_TO_PLAY;
	else if( _str == "POINTER_PLAY_TO_PAUSE" )
	  return xml::POINTER_PLAY_TO_PAUSE;
	else
	  throw xml::parsing( _p, "STATE PARSER :: Invalid parsable_pointer: '" + _str + "'!" );
      }
    };

  template <>
    struct value_traits< fac::game_object >
    {
      static fac::game_object parse( std::string _str, const parser& _p )
      {
	if( _str == "GAME_OBJ" )
	  return fac::GAME_OBJ;
	else if( _str == "GAME_OBJ_GRID" )
	  return fac::GAME_OBJ_GRID;
	else if( _str == "GAME_OBJ_SHEET" )
	  return fac::GAME_OBJ_SHEET;
	else if( _str == "GAME_OBJ_SHEET_BUTTON" )
	  return fac::GAME_OBJ_SHEET_BUTTON;
	else if( _str == "GAME_OBJ_SHEET_ENEMY" )
	  return fac::GAME_OBJ_SHEET_ENEMY;
	else if( _str == "GAME_OBJ_SHEET_PLAYER" )
	  return fac::GAME_OBJ_SHEET_PLAYER;
	else
	  throw xml::parsing( _p, "STATE PARSER :: Invalid parsable fac::game_object: '" + _str + "'!" );
      }
    };
}



// Functions used by the parser to get values/addresses at parsing time:
// Get display size:
float f_display_width( float prosents, float add );
float f_display_height( float prosents, float add );
// Call back functions for 'button-objects':
void f_Exit_from_menu();
void f_Menu_to_play();
void f_Pause_to_main();
void f_Pause_to_play();
void f_Play_to_pause();



// Game-Objects use this template-function to parse different types for their values:
template< typename T >
T Parse_type( xml::parser& _p, std::string _expect )
{
  T value;
  _p.next_expect( xml::parser::start_element, _expect, xml::content::complex );

  switch( _p.attribute< xml::parsable_type >( "type" ))
    {
    case xml::INT :
      value = _p.attribute< int >( "value" );
      break;
    case xml::UINT :
      value = _p.attribute< unsigned int >( "value" );
      break;
    case xml::FLOAT :
      value = _p.attribute< float >( "value" );
      break;
    case xml::DOUBLE :
      value = _p.attribute< double >( "value" );
      break;

    case xml::RANDOM_INT :
      value = xx::Get_random.Discrete_num< int >( _p.attribute< int >( "min" ), 
						  _p.attribute< int >( "max" ));
      break;
    case xml::RANDOM_UINT :
      value = xx::Get_random.Discrete_num< unsigned int >( _p.attribute< unsigned int >( "min" ), 
							   _p.attribute< unsigned int >( "max" ));
      break;
    case xml::RANDOM_FLOAT :
      value = xx::Get_random.Real_num< float >( _p.attribute< float >( "min" ), 
						_p.attribute< float >( "max" ));
      break;
    case xml::RANDOM_DOUBLE :
      value = xx::Get_random.Real_num< double >( _p.attribute< double >( "min" ), 
						 _p.attribute< double >( "max" ));
      break;

    case xml::FUNCTION_DISPLAY_WIDTH :
      value = f_display_width( _p.attribute< float >( "prosents" ), 
			       _p.attribute< float >( "add" ));
      break;
    case xml::FUNCTION_DISPLAY_HEIGHT :
      value = f_display_height( _p.attribute< float >( "prosents" ), 
				_p.attribute< float >( "add" ));
      break;
    default:
      throw xml::parsing( _p, "STATE PARSER :: Invalid parsable_type: '" + _expect + "'!" );
    }

  _p.next_expect( xml::parser::end_element );
  return value;
}



// Game-Objects use this function to parse different pointers for the addresses:
void Parse_pointer( xml::parser& _p, std::string _expect, void (*&_ptr)() );



// --- STATE PARSER ---
class State_parser
{
 public:
  bool Parse_state( const std::string _state_file, std::string _state_id, std::vector< Base_game_obj* >& _objects_vec );

 private:
  bool Parse_textures( xml::parser& _p, std::vector< Base_game_obj* >& _objects_vec );
  bool Parse_objects( xml::parser& _p, std::vector< Base_game_obj* >& _objects_vec );
};



#endif
