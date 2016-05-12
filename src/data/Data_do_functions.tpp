
#include "Data_container.h"
#include "Texture_manager_v2.h"
#include "Printing_manager.h"
#include "Game.h"
#include "State.h"
#include "SDL_gobj.h"



namespace data
{
  State* Get_state( std::string& _state_name_id, State* _this_state_ptr );
  Base_SDL_game_obj* Get_object( std::string& _state_name_id, State* _this_state_ptr, std::string& _object_name_id, Base_SDL_game_obj* _this_object_ptr );
}//data



namespace data
{
  void 
  Do_functions::l_If( std::ifstream& _file, 
		      data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    bool is_true = _p->Next_get_functions< bool >( _file, function );
    if( *m_disabled == true || is_true == false )
      *m_disabled = true;
    else
      *m_disabled = false;
    function = data::Next_line_from_file( _file );
    _p->Next_do_functions( _file, function );
  }

  void 
  Do_functions::l_If_not( std::ifstream& _file, 
			  data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    bool is_true = _p->Next_get_functions< bool >( _file, function );
    if( *m_disabled == true || is_true == true )
      *m_disabled = true;
    else
      *m_disabled = false;
    function = data::Next_line_from_file( _file );
    _p->Next_do_functions( _file, function );
  }

  void 
  Do_functions::l_If_all( std::ifstream& _file, data::Parser* _p ) const
  {

  }

  void 
  Do_functions::l_If_none( std::ifstream& _file, data::Parser* _p ) const
  {

  }

  void 
  Do_functions::l_If_any( std::ifstream& _file, data::Parser* _p ) const
  {

  }

  void 
  Do_functions::l_If_any_not( std::ifstream& _file, data::Parser* _p ) const
  {

  }



  void 
  Do_functions::c_Container_erase( std::ifstream& _file, 
				   data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return;
    data::container.Erase( name_id );
  }



  void
  Do_functions::o_Make_SDL_gobj( std::ifstream& _file, 
				 data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string state_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    std::string filename = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return;
    SDL_gobj* object_ptr = new SDL_gobj( filename, data::Get_state( state_name_id, _p->m_this_state ));
    if( object_ptr->Create())
      _p->m_this_state->Add_object( object_ptr );
    else
      {
	object_ptr->Clean();
	delete object_ptr;
	std::cerr <<"PARSER WARNING :: Failed to create Game-Object of the type: 'SDL_gobj'. Object not created!\n";
      }
  }



  void
  Do_functions::t_Swap_texture_maps() const
  {
    if( *m_disabled )
      return;
    the_Texture_manager_v2::Instance().Swap_maps();
  }

  void
  Do_functions::t_Move_or_load_texture( std::ifstream& _file, 
					data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    std::string filename = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return;
    the_Texture_manager_v2::Instance().Move_or_load_texture( the_Game::Instance().Get_renderer(), id, filename );
  }

  void
  Do_functions::t_Clear_texture_map() const
  {
    if( *m_disabled )
      return;
    the_Texture_manager_v2::Instance().Clear_map();
  }

  void
  Do_functions::t_Clear_current_texture_map() const
  {
    if( *m_disabled )
      return;
    the_Texture_manager_v2::Instance().Clear_current_map();
  }



  void 
  Do_functions::i_Load_image_data( std::ifstream& _file, 
				   data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string image_data_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    std::string filename = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return;
    if( ! the_Printing_manager::Instance().Load_image_data( filename, image_data_id ))
      std::cerr <<"PARSER WARNING :: Failed to load 'Image Data' from file. Image data was not loaded!\n";
  }

  void 
  Do_functions::i_Erase_image_data( std::ifstream& _file, 
				    data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string image_data_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return;
    the_Printing_manager::Instance().Erase_image_data( image_data_id );
  }

  void 
  Do_functions::i_Make_simple_printer( std::ifstream& _file, 
				       data::Parser* _p ) const
  {

  }

  void 
  Do_functions::i_Make_sheet_printer( std::ifstream& _file, 
				      data::Parser* _p ) const
  {

  }

  void 
  Do_functions::i_Make_frame_printer( std::ifstream& _file, 
				      data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string state_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    std::string object_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    Printer* printer_ptr = the_Printing_manager::Instance().Make_printer( _file, _p );
    if( *m_disabled )
      return;
    data::Get_object( state_name_id, _p->m_this_state, object_name_id, _p->m_this_object )->Set_printer( printer_ptr );
  }

  void 
  Do_functions::i_Make_action( std::ifstream& _file, 
			       data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string state_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    std::string object_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    std::string image_data_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    std::string sequence_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( ! *m_disabled )
      {
	Base_SDL_game_obj* obj = data::Get_object( state_name_id, _p->m_this_state, object_name_id, _p->m_this_object );
	the_Printing_manager::Instance().Make_action( _file, _p, obj->Get_printer(), image_data_id, sequence_id );
      }
    else
      the_Printing_manager::Instance().Make_action( _file, _p, nullptr, image_data_id, sequence_id );
  }



  void
  Do_functions::s_Make_camera( std::ifstream& _file, 
			       data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string state_name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return;
    data::Get_state( state_name_id, _p->m_this_state )->Make_camera();
  }
}//data



namespace data
{
  template< typename T > 
  void 
  Do_functions::c_Container_add( std::ifstream& _file, 
				 data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    T value = _p->Next_get_functions< T >( _file, function );
    if( *m_disabled )
      return;
    data::container.Add( name_id, value );
  }

  template< typename T > 
  void 
  Do_functions::c_Container_set( std::ifstream& _file, 
				 data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    function = data::Next_line_from_file( _file );
    T value = _p->Next_get_functions< T >( _file, function );
    if( *m_disabled )
      return;
    data::container.Set( name_id, value );
  }



  template< typename T > 
  void 
  Do_functions::p_Print( std::ifstream& _file, 
			 data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T print = _p->Next_get_functions< T >( _file, function );
    if( *m_disabled )
      return;
    std::cout <<"PARSER :: Print: '"<< print <<"'\n";
  }
  template<>
  void 
  Do_functions::p_Print< bool >( std::ifstream& _file, 
				 data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    bool print = _p->Next_get_functions< bool >( _file, function );
    if( *m_disabled )
      return;
    std::cout << std::boolalpha;
    std::cout <<"PARSER :: Print: '"<< print <<"'\n";
    std::cout << std::noboolalpha;
  }
}//data

