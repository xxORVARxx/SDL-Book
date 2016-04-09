
#include "SDL_gobj.h"
#include "Functions_SDL_gobj.h"



SDL_gobj::SDL_gobj( std::string _file ) : Base_SDL_game_obj( _file )
{

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

  m_texture_id = std::string( sgo::Get_value< xx::String_cast >( _file ));
  m_image_size.x = sgo::Get_value< float >( _file );
  m_image_size.y = sgo::Get_value< float >( _file );
  m_position.x = sgo::Get_value< double >( _file );
  m_position.y = sgo::Get_value< double >( _file );
  m_scale.x = sgo::Get_value< float >( _file );
  m_scale.y = sgo::Get_value< float >( _file );
  m_size.x = sgo::Get_value< float >( _file );
  m_size.y = sgo::Get_value< float >( _file );
}
