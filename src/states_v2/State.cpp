
#include "State.h"
#include "Functions_state.h"
#include "Interface_SDL_game_obj.h"
#include "Parser.h"
#include "Camera.h"



State::State( std::string _file ) : m_file_name(_file), 
				    m_camera_ptr(nullptr),
				    disable_logic(false),
				    disable_render(false)
{

}



State::~State()
{
  if( m_camera_ptr )
    delete m_camera_ptr;
}



void
State::Create()
{
  std::string prefix = "Data/states/";
  std::string suffix = ".data";
  try
    {
      std::ifstream data_file( prefix + m_file_name + suffix );
      if( data_file.is_open() && data_file.good())
	{
	  data::Parser p;
	  p.Set_this( this );

	  m_name_id = std::string( p.Parse_file< xx::String_cast >( data_file ));
	  p.Parse_file( data_file );

	  data_file.close();
	}
      else 
	throw std::ios::failure( "(xx) Parsing ERROR! When opening state's data-file: '" + prefix + m_file_name + suffix + "'! " );
    }
  catch( const std::exception& e )
    {
      std::cerr <<"PARSER ERROR :: When parsing the state's data-file: '"<< prefix << m_file_name << suffix <<"'!\n";
      std::cerr <<"\t"<< e.what() <<'\n';
    }
  if( m_name_id.empty())
    throw std::logic_error( "(xx) State ERROR! The state's 'name_id' cannot be an empty string! " );
}



Base_SDL_game_obj* 
State::Find_object( std::string& object_name_id )
{
  for( auto& i: m_objects_vec )
    if( i->Get_name_id() == object_name_id )
      return i;
  return nullptr;
}



void 
State::Update() const
{
  if( disable_logic )
    return;
  for( const auto& i: m_objects_vec )
    i->Update();
}



void 
State::Render() const
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



void 
State::Make_camera() 
{
  m_camera_ptr = new Camera;
}
