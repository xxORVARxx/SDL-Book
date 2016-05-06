 
#include "Interface_SDL_game_obj.h"
#include "Parser.h"



Base_SDL_game_obj::Base_SDL_game_obj( std::string _file, 
				      State* _state ) : 
  m_file_name(_file), m_this_state(_state)
{

}



void 
Base_SDL_game_obj::Create()
{
  std::string prefix = "Data/objects/";
  std::string suffix = ".data";
  try
    {
      std::ifstream data_file( prefix + m_file_name + suffix );
      if( data_file.is_open() && data_file.good())
	{
	  data::Parser p;

	  this->Parse_data_file( data_file, &p, true );
	  p.Parse_file( data_file );

	  data_file.close();
	}
      else 
	throw std::ios::failure( "(xx) Parsing ERROR! When opening object's data-file: '" + prefix + m_file_name + suffix + "'!" );
    }
  catch( const std::exception& e )
    {
      std::cout <<"PARSER ERROR :: When parsing the object's data-file: '"<< prefix << m_file_name << suffix <<"'!\n";
      std::cerr <<"\t"<< e.what() <<'\n';
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



void 
Base_SDL_game_obj::Parse_data_file( std::ifstream& _file, data::Parser* _p, bool _set_p )
{
  if( _set_p )
    _p->Set_this( m_this_state, this );

  m_name_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
}
