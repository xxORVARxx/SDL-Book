
#include "Game_obj.h"
#include "Texture_manager.h"

#include "Game.h"
#include "XML_parser_states.h"



// --- Game Object ---
void Game_obj::Load( Game_obj_parameters& _obj_params )
{
  m_texture_id = _obj_params.texture_id;
  m_image_size = _obj_params.image_size;
  m_position = _obj_params.position;
  m_scale = _obj_params.scale;
  m_size = _obj_params.size;

  if( m_size.x == 0 )  
    m_size.x = m_image_size.x;
  if( m_size.y == 0 )  
    m_size.y = m_image_size.y;

  m_size *= m_scale;
}

void Game_obj::Parse( xml::parser& _p )
{
  std::cout <<"Game-Object.  ";
  _p.next_expect( xml::parser::start_element, "game_obj_parameters", xml::content::complex );

  m_texture_id = _p.element( "texture" );
  m_image_size.x = Parse_type< float >( _p, "image_size_x" );
  m_image_size.y = Parse_type< float >( _p, "image_size_y" );
  m_position.x = Parse_type< float >( _p, "position_x" );
  m_position.y = Parse_type< float >( _p, "position_y" );
  m_scale.x = Parse_type< float >( _p, "scale_x" );
  m_scale.y = Parse_type< float >( _p, "scale_y" );
  m_size.x = Parse_type< float >( _p, "size_x" );
  m_size.y = Parse_type< float >( _p, "size_y" );

  _p.next_expect( xml::parser::end_element );//game_obj_parameters

  if( m_size.x == 0 )  
    m_size.x = m_image_size.x;
  if( m_size.y == 0 )  
    m_size.y = m_image_size.y;

  m_size *= m_scale;
}



void Game_obj::Draw( Camera* _camera )
{
  glm::vec2 display_position = m_position;
  if( _camera != nullptr )
    display_position -= _camera->Get_position();

  the_Texture_manager::Instance().Draw( the_Game::Instance().Get_renderer(), m_texture_id, display_position, m_size );
}



void Game_obj::Clean()
{
  std::cout << "Game_obj.Clean() is Done.\n";
}
