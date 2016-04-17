
#include "SDL_gobj.h"
#include "Functions_SDL_gobj.h"
#include "Texture_manager_v2.h"

#include "Game.h"



SDL_gobj::SDL_gobj( std::string _file ) : Base_SDL_game_obj( _file )
{
  std::cout <<"Obj created\n";
}



void 
SDL_gobj::Update()
{

}



void 
SDL_gobj::Draw( Camera* _camera ) 
{
  glm::vec2 display_position = glm::vec2( m_position.x, m_position.y );
  if( _camera != nullptr )
    display_position -= _camera->Get_position();

  the_Texture_manager_v2::Instance().Draw( the_Game::Instance().Get_renderer(), m_texture_id, display_position, m_size );
}



void 
SDL_gobj::Clean()
{
  std::cout << "SDL_gobj.Clean() is Done.\n";
}



void 
SDL_gobj::Parse_data_file( std::ifstream& _file )
{
  Base_SDL_game_obj::Parse_data_file( _file );

  data::Parser p;
  m_texture_id = std::string( p.Parse_value< xx::String_cast >( _file ));
  m_image_size.x = p.Parse_value< float >( _file );
  m_image_size.y = p.Parse_value< float >( _file );
  m_scale.x = p.Parse_value< float >( _file );
  m_scale.y = p.Parse_value< float >( _file );
  m_size.x = p.Parse_value< float >( _file );
  m_size.y = p.Parse_value< float >( _file );
  m_position.x = p.Parse_value< double >( _file );
  m_position.y = p.Parse_value< double >( _file );
}
