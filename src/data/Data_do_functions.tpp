
#include "Data_container.h"
#include "Texture_manager_v2.h"
#include "Game.h"
#include "State.h"
#include "SDL_gobj.h"



namespace data
{
  State* Get_state( std::string& _state_name_id, State* _this_state_ptr );
}//data



namespace data
{
  void 
  Do_functions::l_If( bool _disabled, 
		      std::ifstream& _file, 
		      Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    bool is_true = _p->Next_get_functions< bool >( _disabled, _file, function );
    if( _disabled == true || is_true == false )
      _disabled = true;
    else
      _disabled = false;
    function = data::Next_line_from_file( _file );
    _p->Next_do_functions( _disabled, _file, function );
  }

  void 
  Do_functions::l_If_not( bool _disabled, 
			  std::ifstream& _file, 
			  Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    bool is_true = _p->Next_get_functions< bool >( _disabled, _file, function );
    if( _disabled == true || is_true == true )
      _disabled = true;
    else
      _disabled = false;
    function = data::Next_line_from_file( _file );
    _p->Next_do_functions( _disabled, _file, function );
  }

  void 
  Do_functions::l_If_all( bool _disabled, std::ifstream& _file, Parser* _p ) const
  {

  }

  void 
  Do_functions::l_If_none( bool _disabled, std::ifstream& _file, Parser* _p ) const
  {

  }

  void 
  Do_functions::l_If_any( bool _disabled, std::ifstream& _file, Parser* _p ) const
  {

  }

  void 
  Do_functions::l_If_any_not( bool _disabled, std::ifstream& _file, Parser* _p ) const
  {

  }



  void 
  Do_functions::c_Container_erase( bool _disabled, 
				   std::ifstream& _file, 
				   Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return;
    data::container.Erase( name_id );
  }



  void
  Do_functions::o_Make_SDL_gobj( bool _disabled, 
				 std::ifstream& _file, 
				 Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string state_name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    function = data::Next_line_from_file( _file );
    std::string filename = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return;
    SDL_gobj* object_ptr = new SDL_gobj( filename, data::Get_state( state_name_id, _p->m_this_state ));
    object_ptr->Create();
    _p->m_this_state->Add_object( object_ptr );
  }



  void
  Do_functions::t_Swap_texture_maps( bool _disabled ) const
  {
    if( _disabled )
      return;
    the_Texture_manager_v2::Instance().Swap_maps();
  }

  void
  Do_functions::t_Move_or_load_texture( bool _disabled, 
					std::ifstream& _file, 
					Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    function = data::Next_line_from_file( _file );
    std::string filename = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return;
    the_Texture_manager_v2::Instance().Move_or_load_texture( the_Game::Instance().Get_renderer(), 
							     id, 
							     filename );
  }

  void
  Do_functions::t_Clear_texture_map( bool _disabled ) const
  {
    if( _disabled )
      return;
    the_Texture_manager_v2::Instance().Clear_map();
  }

  void
  Do_functions::t_Clear_current_texture_map( bool _disabled ) const
  {
    if( _disabled )
      return;
    the_Texture_manager_v2::Instance().Clear_current_map();
  }



  void
  Do_functions::s_Make_camera( bool _disabled, 
			       std::ifstream& _file, 
			       Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string state_name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return;
    data::Get_state( state_name_id, _p->m_this_state )->Make_camera();
  }
}//data



namespace data
{
  template< typename T > 
  void 
  Do_functions::c_Container_add( bool _disabled, 
				 std::ifstream& _file, 
				 Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    function = data::Next_line_from_file( _file );
    T value = _p->Next_get_functions< T >( _disabled, _file, function );
    if( _disabled )
      return;
    data::container.Add( name_id, value );
  }

  template< typename T > 
  void 
  Do_functions::c_Container_set( bool _disabled, 
				 std::ifstream& _file, 
				 Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    function = data::Next_line_from_file( _file );
    T value = _p->Next_get_functions< T >( _disabled, _file, function );
    if( _disabled )
      return;
    data::container.Set( name_id, value );
  }



  template< typename T > 
  void 
  Do_functions::p_Print( bool _disabled, 
			 std::ifstream& _file, 
			 Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T print = _p->Next_get_functions< T >( _disabled, _file, function );
    if( _disabled )
      return;
    std::cout <<"Parser-Print: '"<< print <<"'\n";
  }
  template<>
  void 
  Do_functions::p_Print< bool >( bool _disabled, 
				 std::ifstream& _file, 
				 Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    bool print = _p->Next_get_functions< bool >( _disabled, _file, function );
    if( _disabled )
      return;
    std::cout << std::boolalpha;
    std::cout <<"Parser-Print: '"<< print <<"'\n";
    std::cout << std::noboolalpha;
  }
}//data

