
#include "Data_container.h"
#include "Texture_manager_v2.h"
#include "Game.h"



namespace data
{
  void 
  Do_functions::c_Container_erase( std::ifstream& _file, Parser* _p )
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    data::container.Erase( name_id );
  }



  void
  Do_functions::o_Make_SDL_gobj( std::ifstream& _file ) 
  {
    /*
      if( _p->m_state_ptr == nullptr )
      throw std::logic_error( "(xx) Parsing ERROR! When making 'Game-Object'. No 'Game-State' has been selected!" );
      std::string filename;
      _file >> filename;
      filename = data::Check_for_comments( _file, filename );
      SDL_gobj* object_ptr = new SDL_gobj( filename );
      object_ptr->Create();
      _p->m_state_ptr->Add_object( object_ptr );
    */
  }



  void
  Do_functions::t_Swap_texture_maps() 
  {
    the_Texture_manager_v2::Instance().Swap_maps();
  }

  void
  Do_functions::t_Move_or_load_texture( std::ifstream& _file, Parser* _p ) 
  {
    std::string function = data::Next_line_from_file( _file );
    std::string id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    std::string filename = _p->Next_get_functions< xx::String_cast >( _file, function );

    the_Texture_manager_v2::Instance().Move_or_load_texture( the_Game::Instance().Get_renderer(), 
							     id, 
							     filename );
  }

  void
  Do_functions::t_Clear_texture_map() 
  {
    the_Texture_manager_v2::Instance().Clear_map();
  }

  void
  Do_functions::t_Clear_current_texture_map() 
  {
    the_Texture_manager_v2::Instance().Clear_current_map();
  }



  void
  Do_functions::s_Make_camera() 
  {
    /*
      if( _p->m_state_ptr == nullptr )
      throw std::logic_error( "(xx) Parsing ERROR! When making 'Camera'. No 'Game-State' has been selected!" );
      _camera_ptr = new Camera;
    */
  }
}//data



namespace data
{
  template< typename T > 
  void 
  Do_functions::c_Container_add( std::ifstream& _file, Parser* _p )
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    T value = _p->Next_get_functions< T >( _file, function );
    data::container.Add( name_id, value );
  }
}//data

