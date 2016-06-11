 
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



bool 
Base_SDL_game_obj::Find_hook( const std::string& _hook_name_id, 
			      event::i_Hook** _hook_dptr )
{
  auto hook_itr = m_hooks_map.find( _hook_name_id );
  if( hook_itr == m_hooks_map.end())
    return false;
  *_hook_dptr = hook_itr->second;
  return true;
}

bool 
Base_SDL_game_obj::Find_trigger( const std::string& _trigger_name_id,
				 event::i_Trigger** _trigger_dptr )
{
  auto trigger_itr = m_triggers_map.find( _trigger_name_id );
  if( trigger_itr == m_triggers_map.end())
    return false;
  *_trigger_dptr = trigger_itr->second;
  return true;
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

  m_name_id = std::string( _p->Parse_file< string_t >( _file ));
}
