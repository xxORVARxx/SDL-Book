
#include "State.h"
#include "Functions_state.h"
#include "Interface_SDL_game_obj.h"
#include "Parser.h"



State::State( std::string _file ) : m_file_name(_file), 
				    m_camera_ptr(nullptr),
				    disable_logic(false),
				    disable_render(false)
{
  std::cout <<"State created\n";
}



State::~State()
{
  if( m_camera_ptr )
    delete m_camera_ptr;
}



void
State::Create()
{
  try
    {
      std::ifstream data_file( "Data/states/" + m_file_name + ".data" );
      if( data_file.is_open() && data_file.good())
	{
	  data::Parser p;

	  m_name_id = std::string( p.Parse_file< xx::String_cast >( data_file ));
	  p.Parse_file( data_file );

	  data_file.close();
	}
      else 
	throw std::ios::failure( "(xx) STATE ERROR :: When opening state's data file!" );
    }
  catch( const std::exception& e )
    {
      std::cerr << e.what() <<'\n';
    }
  if( m_name_id.empty())
    throw std::logic_error( "(xx) STATE ERROR :: The state's 'name_id' cannot be an empty string!" );
}



void State::Update() const
{
  if( disable_logic )
    return;
  for( const auto& i: m_objects_vec )
    i->Update();
}



void State::Render() const
{
  if( disable_render )
    return;
  for( const auto& i: m_objects_vec )
    i->Draw( m_camera_ptr );
}



void 
State::Clean()
{
  for( const auto& i: m_objects_vec )
    {
      i->Clean();
      delete i;
    }
  m_objects_vec.clear();
  std::cout << "STATE :: '"<< m_name_id <<"'.Clean() is Done.\n";
}
