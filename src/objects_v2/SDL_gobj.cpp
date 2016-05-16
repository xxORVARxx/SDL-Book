
#include "SDL_gobj.h"
#include "Input_handler.h"
#include "Texture_manager_v2.h"
#include "xx_String_cast.h"

#include "Game.h"
#include "Parser.h"
#include "Printer.h"
#include "State.h"



SDL_gobj::SDL_gobj( std::string _file, 
		    State* _state ) 
  : Base_SDL_game_obj( _file, _state ),
    m_trigger_flip_right( true ),
    m_trigger_flip_left( false )
{
  m_action = "0-WALK";
  m_move_up_key =    SDL_SCANCODE_W;
  m_move_down_key =  SDL_SCANCODE_S;
  m_move_right_key = SDL_SCANCODE_D;
  m_move_left_key =  SDL_SCANCODE_A;

  m_triggers_map[ "GOBJ_FLIP_RIGHT_T" ] = &m_trigger_flip_right;
  m_triggers_map[ "GOBJ_FLIP_LEFT_T" ] = &m_trigger_flip_left;
}



void 
SDL_gobj::Update()
{
  const Uint8* keys_state = the_Input_handler::Instance().Get_keys_state();

  if( keys_state[ m_move_down_key ] &&( keys_state[ m_move_left_key ] || keys_state[ m_move_right_key ] ))
    m_action = "45-WALK";
  else if( keys_state[ m_move_up_key ] &&( keys_state[ m_move_left_key ] || keys_state[ m_move_right_key ] ))
    m_action = "135-WALK";
  else if( keys_state[ m_move_down_key ] )
    m_action = "0-WALK";
  else if( keys_state[ m_move_up_key ] )
    m_action = "180-WALK";
  else if( keys_state[ m_move_left_key ] || keys_state[ m_move_right_key ] )
    m_action = "90-WALK";

  if( keys_state[ m_move_right_key ] )
    {
      m_trigger_flip_right();
    }
  else if( keys_state[ m_move_left_key ] )
    {
      m_trigger_flip_left();
    }
}



void 
SDL_gobj::Draw( Camera* _camera_ptr ) 
{
  if( m_printer_ptr &&( ! m_action.empty()))
    m_printer_ptr->Print( m_action, _camera_ptr->Get_position());
}



void 
SDL_gobj::Clean()
{
  std::cout <<"SDL_gobj.Clean() is Done.  ";
  Base_SDL_game_obj::Clean();
}



void 
SDL_gobj::Parse_data_file( std::ifstream& _file, 
			   data::Parser* _p, 
			   bool _set_p )
{
  if( _set_p )
    _p->Set_this( m_this_state_ptr, this );
  Base_SDL_game_obj::Parse_data_file( _file, _p, false );

  /*
  m_print.m_texture_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
  m_print.m_image_size.x = _p->Parse_file< float >( _file );
  m_print.m_image_size.y = _p->Parse_file< float >( _file );
  m_scale.x = _p->Parse_file< float >( _file );
  m_scale.y = _p->Parse_file< float >( _file );
  m_size.x = _p->Parse_file< float >( _file );
  m_size.y = _p->Parse_file< float >( _file );
  m_position.x = _p->Parse_file< float >( _file );
  m_position.y = _p->Parse_file< float >( _file );
  gobj::Calculate_size_and_scale( m_print.m_image_size, m_size, m_scale );
  */
}
