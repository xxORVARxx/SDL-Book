 
#include "Interface_SDL_game_obj.h"
#include "Parser.h"
#include "Printer.h"



Base_SDL_game_obj::Base_SDL_game_obj( std::string _file, 
				      State* _state )
  : m_file_name(_file), 
    m_this_state_ptr(_state), 
    m_printer_ptr(nullptr)
{
}



bool 
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
	throw std::ios::failure( "(xx) Parsing ERROR! When opening object's data-file: '" + prefix + m_file_name + suffix + "'! " );
    }
  catch( const std::exception& e )
    {
      std::cerr <<"PARSER ERROR :: When parsing the object's data-file: '"<< prefix << m_file_name << suffix <<"'!\n";
      std::cerr <<"\t"<< e.what() <<'\n';
      return false;
    }
  return true;
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
Base_SDL_game_obj::Clean()
{
  if( m_printer_ptr )
    delete m_printer_ptr;
  std::cout <<"Base_SDL_game_obj.Clean() is Done.\n";
}



void 
Base_SDL_game_obj::Make_event( std::ifstream& _file, 
			       data::Parser* _p, 
			       std::string& _trigger, 
			       std::string& _hook, 
			       char _one,
			       char _two )
{
  auto t_itr = m_triggers_map.find( _trigger );
  if( t_itr == m_triggers_map.end())
    throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. The Trigger: '"+ _trigger +"' could not be found! " );

  auto h_itr = m_hooks_map.find( _hook );
  if( h_itr == m_hooks_map.end())
    throw std::invalid_argument( "(xx) Event ERROR! When MAKING event. The Hook: '"+ _hook +"' could not be found! " );

  t_itr->second->Set_hook( h_itr->second );
  h_itr->second->Set_parameter_1( t_itr->second->Get_variable_A());
}



void 
Base_SDL_game_obj::Set_printer( Printer* _printer_ptr )
{ 
  m_printer_ptr = _printer_ptr;
  the_Printing_manager::Instance().Harvest_triggers( m_printer_ptr, m_triggers_map );
  the_Printing_manager::Instance().Harvest_hooks( m_printer_ptr, m_hooks_map );
}


  
Printer* 
Base_SDL_game_obj::Get_printer() const 
{ 
  return m_printer_ptr; 
}



void 
Base_SDL_game_obj::Parse_data_file( std::ifstream& _file, 
				    data::Parser* _p, 
				    bool _set_p )
{
  if( _set_p )
    _p->Set_this( m_this_state_ptr, this );

  m_name_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
}
