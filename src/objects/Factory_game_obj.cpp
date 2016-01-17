
#include "Factory_game_obj.h"



bool Factory_game_obj::Register_type( std::string type_id, Base_creator* ptr_creater )
{
  // if the type is already registered, do nothing:
  std::map< std::string, Base_creator* >::iterator itr = m_creators.find( type_id );
  if( itr != m_creators.end())
    {
      delete ptr_creater;
      return false;
    }
  m_creators[ type_id ] = ptr_creater;
  return true;
}



Game_obj_default* Factory_game_obj::Create( std::string type_id )
{
  std::map< std::string, Base_creator* >::iterator itr = m_creators.find( type_id );
  if( itr != m_creators.end())
    {
      std::cout << "FACTORY :: Failed to create Game Object, could not find type : " << type_id << " !!\n";  
      return nullptr;
    }
  Base_creator* ptr_creater = (*itr).second;
  return ptr_creater->Create_game_object();
}
