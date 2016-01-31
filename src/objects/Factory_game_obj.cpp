
#include "Factory_game_obj.h"



bool the_Factory_game_obj::Register_creator( std::string _object_id, Base_creator_game_obj* _creater_ptr )
{
  // if the type is already registered, do nothing:
  std::map< const std::string, Base_creator_game_obj* >::iterator itr = m_creators_map.find( _object_id );
  if( itr != m_creators_map.end())
    {
      delete _creater_ptr;
      return false;
    }
  m_creators_map[ _object_id ] = _creater_ptr;
  return true;
}



Base_game_obj* the_Factory_game_obj::Create( std::string _object_id )
{
  std::map< const std::string, Base_creator_game_obj* >::iterator itr = m_creators_map.find( _object_id );
  if( itr == m_creators_map.end())
    {
      std::cout << "FACTORY :: Failed to create Game Object, could not find type : " << _object_id << " !!\n";  
      return nullptr;
    }
  Base_creator_game_obj* creater_ptr = (*itr).second;
  return creater_ptr->Create_game_object();
}



void the_Factory_game_obj::Clean()
{
  // Deleting creators:
  std::for_each( m_creators_map.begin(), m_creators_map.end(), 
		 []( std::pair< const std::string, Base_creator_game_obj* >& i ){ delete i.second; } );
  m_creators_map.clear();

  std::cout << "FACTORY :: Clean() is Done.\n";
}
