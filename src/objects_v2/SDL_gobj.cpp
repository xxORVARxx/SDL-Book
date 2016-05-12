
#include "SDL_gobj.h"
#include "Texture_manager_v2.h"
#include "xx_String_cast.h"

#include "Game.h"
#include "Parser.h"
#include "State.h"
#include "Printer.h"

namespace gobj
{
  void Calculate_size_and_scale( const glm::vec2& _image_size, glm::vec2& _size, glm::vec2& _scale );
}//gobj



SDL_gobj::SDL_gobj( std::string _file, 
		    State* _state ) : 
  Base_SDL_game_obj( _file, _state )
{

}



void 
SDL_gobj::Update()
{

}



void 
SDL_gobj::Draw( Camera* _camera ) 
{
  // FOR TESTING:
  if( m_printer )
    m_printer->Print( "ATTACK" );
  /*
  glm::vec2 display_position = glm::vec2( m_position.x, m_position.y );
  if( _camera != nullptr )
    display_position -= _camera->Get_position();

  the_Texture_manager_v2::Instance().Draw( the_Game::Instance().Get_renderer(), m_print.m_texture_id, display_position, m_size );
  */
}



void 
SDL_gobj::Clean()
{
  std::cout << "SDL_gobj.Clean() is Done.\n";
}



void 
SDL_gobj::Parse_data_file( std::ifstream& _file, 
			   data::Parser* _p, 
			   bool _set_p )
{
  if( _set_p )
    _p->Set_this( m_this_state, this );
  Base_SDL_game_obj::Parse_data_file( _file, _p, false );

  m_print.m_texture_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
  m_print.m_image_size.x = _p->Parse_file< float >( _file );
  m_print.m_image_size.y = _p->Parse_file< float >( _file );
  m_scale.x = _p->Parse_file< float >( _file );
  m_scale.y = _p->Parse_file< float >( _file );
  m_size.x = _p->Parse_file< float >( _file );
  m_size.y = _p->Parse_file< float >( _file );
  m_position.x = _p->Parse_file< double >( _file );
  m_position.y = _p->Parse_file< double >( _file );

  gobj::Calculate_size_and_scale( m_print.m_image_size, m_size, m_scale );
}
