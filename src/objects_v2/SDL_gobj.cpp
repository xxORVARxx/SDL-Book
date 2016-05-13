
#include "SDL_gobj.h"
#include "Input_handler.h"
#include "Texture_manager_v2.h"
#include "xx_String_cast.h"

#include "Game.h"
#include "Parser.h"
#include "Printer.h"
#include "State.h"

namespace gobj
{
  void Calculate_size_and_scale( const glm::vec2& _image_size, glm::vec2& _size, glm::vec2& _scale );
}//gobj



SDL_gobj::SDL_gobj( std::string _file, 
		    State* _state ) : 
  Base_SDL_game_obj( _file, _state )
{
  m_action = "0-WALK";
  move_up_key =    SDL_SCANCODE_W;
  move_down_key =  SDL_SCANCODE_S;
  move_right_key = SDL_SCANCODE_D;
  move_left_key =  SDL_SCANCODE_A;
}



void 
SDL_gobj::Update()
{
  const Uint8* keys_state = the_Input_handler::Instance().Get_keys_state();

  if( keys_state[ move_down_key ] &&( keys_state[ move_left_key ] || keys_state[ move_right_key ] ))
    m_action = "45-WALK";
  else if( keys_state[ move_up_key ] &&( keys_state[ move_left_key ] || keys_state[ move_right_key ] ))
    m_action = "135-WALK";
  else if( keys_state[ move_down_key ] )
    m_action = "0-WALK";
  else if( keys_state[ move_up_key ] )
    m_action = "180-WALK";
  else if( keys_state[ move_left_key ] || keys_state[ move_right_key ] )
    m_action = "90-WALK";

  if( keys_state[ move_right_key ] ) 
    m_printer_ptr->Flip_horizontally( true );
  else if( keys_state[ move_left_key ] )
    m_printer_ptr->Flip_horizontally( false );
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
  std::cout << "SDL_gobj.Clean() is Done.  ";
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
