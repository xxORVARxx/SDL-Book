 
#include "Interface_SDL_game_obj.h"



Base_SDL_game_obj::Base_SDL_game_obj( std::string _file ) : m_file_name(_file)
{

}



void 
Base_SDL_game_obj::Create()
{
  try
    {
      std::ifstream data_file( "Data/objects/" + m_file_name + ".data" );
      if( data_file.is_open() && data_file.good())
	{
	  this->Parse_data_file( data_file );
	  data_file.close();
	}
      else 
	throw std::ios::failure( "(xx) Error opening object's data file!" );
    }
  catch( const std::exception& e )
    {
      std::cerr << e.what() <<'\n';
    }
}



void 
Base_SDL_game_obj::Clone()
{

}



void 
Base_SDL_game_obj::Save()
{

}



void 
Base_SDL_game_obj::Load()
{

}
