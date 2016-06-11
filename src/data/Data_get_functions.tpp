
#include "Texture_manager_v2.h"
#include "Printing_manager.h"
#include "Game_world.h"
#include "Game.h"
#include "State.h"



namespace data
{
  byte_t
  Get_functions::b_Byte( std::ifstream& _file ) const
  {
    byte_t b;
    _file >> b;
    if( *m_disabled )
      return 0;
    return b;
  }

  integer_t
  Get_functions::b_Integer( std::ifstream& _file ) const
  {
    integer_t i;
    _file >> i;
    if( *m_disabled )
      return 0;
    return i;
  }
 
  real_t
  Get_functions::b_Real( std::ifstream& _file ) const
  {
    real_t r;
    _file >> r;
    if( *m_disabled )
      return 0.0;
    return r;
  }

  string_t
  Get_functions::b_String( std::ifstream& _file ) const
  {
    try
      {
	return xx::String_cast( xx::Read_string_from_file( _file ));
      }
    catch( const std::ios::failure& e )
      {
	std::string error_msg( e.what());
	data::Throw_file_corrupted( error_msg );
      }
  }


  byte_t
  Get_functions::c_Container_has( std::ifstream& _file, 
				  data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return false;
    return data::container.Has( name_id );
  }



  string_t
  Get_functions::s_This_state( data::Parser* _p ) const
  {
    if( *m_disabled )
      return xx::String_cast();
    if( _p->m_this_state )
      return xx::String_cast( _p->m_this_state->Get_id());
    throw std::runtime_error( "(xx) Parsing ERROR! No 'THIS-STATE' found! " );
  }

  byte_t
  Get_functions::s_Has_state( std::ifstream& _file, 
			      data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return false;
    return the_Game::Instance().Get_state_machine()->Has_state( name_id );
  }



  string_t
  Get_functions::o_This_object( data::Parser* _p ) const
  {
    if( *m_disabled )
      return xx::String_cast();
    if( _p->m_this_object )
      return xx::String_cast( _p->m_this_object->Get_name_id());
    throw std::runtime_error( "(xx) Parsing ERROR! No 'THIS-OBJECT' found! " );
  }



  integer_t
  Get_functions::t_Texture_width( std::ifstream& _file, 
				  data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return 0;
    SDL_Point size;
    if( the_Texture_manager_v2::Instance().Get_texture_size( id, size ))
      return size.x;
    throw std::invalid_argument( "(xx) Parsing ERROR! When geting texture's WIDTH. No texture with the ID: '" + id + "'! " );
  }

  integer_t
  Get_functions::t_Texture_height( std::ifstream& _file, 
				   data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return 0;
    SDL_Point size;
    if( the_Texture_manager_v2::Instance().Get_texture_size( id, size ))
      return size.y;
    else
      throw std::invalid_argument( "(xx) Parsing ERROR! When geting texture's HEIGHT. No texture with the ID: '" + id + "'! " );
  }



  byte_t
  Get_functions::i_Has_image_data( std::ifstream& _file, 
				   data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string image_data_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return false;
    return the_Printing_manager::Instance().Has_image_data( image_data_id );
  }



  integer_t
  Get_functions::w_Display_width() const
  {
    if( *m_disabled )
      return 0;
    return the_World::Instance().Get_display_width();
  }

  integer_t
  Get_functions::w_Display_height() const
  {
    if( *m_disabled )
      return 0;
    return the_World::Instance().Get_display_height();
  }
}//data



namespace data
{
  template< typename T > 
  T 
  Get_functions::m_Add( std::ifstream& _file, 
			data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _file, function );
    return( a + b );
  }

  template< typename T >
  T 
  Get_functions::m_Subtract( std::ifstream& _file, 
			     data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _file, function );
    return( a - b );
  }

  template< typename T >
  T 
  Get_functions::m_Multiply( std::ifstream& _file, 
			     data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _file, function );
    return( a * b );
  }

  template< typename T >
  T 
  Get_functions::m_Divide( std::ifstream& _file, 
			   data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T numerator = _p->Next_get_functions< T >( _file, function );
    function = data::Next_line_from_file( _file );
    T denominator = _p->Next_get_functions< T >( _file, function );
    if( denominator != 0 )
      return( numerator / denominator );
    else
      return 0;
  }

  template< typename T >
  T 
  Get_functions::f_Random_discrete_num( std::ifstream& _file ) const
  {
    /*
      data::Parser p;
      T min = p.Parse_value< T >( _file );
      T max = p.Parse_value< T >( _file );
      return xx::Get_random.Discrete_num< long int >( min, max );
    */
  }

  template< typename T >
  T 
  Get_functions::f_Random_real_num( std::ifstream& _file ) const
  {
    /*
      data::Parser p;
      T min = p.Parse_value< T >( _file );
      T max = p.Parse_value< T >( _file );
      return xx::Get_random.Real_num< double >( min, max );
    */
  }



  template< typename T >
  T 
  Get_functions::c_Container_get( std::ifstream& _file, 
				  data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return 0;
    T value;
    data::container.Get( name_id, value );
    return value;
  }

  template< typename T >
  T 
  Get_functions::c_Container_take( std::ifstream& _file, 
				   data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return 0;
    T value;
    data::container.Take( name_id, value );
    return value;
  }
}//data
