
#include "Texture_manager_v2.h"
#include "Printing_manager.h"
#include "Game_world.h"
#include "Game.h"
#include "State.h"



namespace data
{
  int
  Get_functions::b_Int( std::ifstream& _file ) const
  {
    int i;
    _file >> i;
    if( *m_disabled )
      return 0;
    return i;
  }

  long int
  Get_functions::b_Long_int( std::ifstream& _file ) const
  {
    int li;
    _file >> li;
    if( *m_disabled )
      return 0;
    return li;
  }

  unsigned
  Get_functions::b_Unsigned( std::ifstream& _file ) const
  {
    unsigned u;
    _file >> u;
    if( *m_disabled )
      return 0;
    return u;
  }

  long unsigned
  Get_functions::b_Long_unsigned( std::ifstream& _file ) const
  {
    unsigned lu;
    _file >> lu;
    if( *m_disabled )
      return 0;
    return lu;
  }

  float
  Get_functions::b_Float( std::ifstream& _file ) const
  {
    float f;
    _file >> f;
    if( *m_disabled )
      return 0.0;
    return f;
  }

  double
  Get_functions::b_Double( std::ifstream& _file ) const
  {
    double d;
    _file >> d;
    if( *m_disabled )
      return 0.0;
    return d;
  }

  long double
  Get_functions::b_Long_double( std::ifstream& _file ) const
  {
    double ld;
    _file >> ld;
    if( *m_disabled )
      return 0.0;
    return ld;
  }

  bool
  Get_functions::b_Bool( std::ifstream& _file ) const
  {
    std::string str;
    _file >> str;
    if( *m_disabled )
      return false;
    for( char& c : str )
      c = std::tolower( c );
    if(( str == "0" )||( str == "0.0" )||( str == "false" )||( str == "'false'" )||( str == "\"false\"" )||
       ( str == "'0'" )||( str == "\"0\"" )||( str == "'0.0'" )||( str == "\"0.0\"" ))
      return false;
    return true;
  }

  char
  Get_functions::b_Char( std::ifstream& _file ) const
  {
    char c;
    _file >> c;
    if( *m_disabled )
      return 0;
    return c;
  }

  xx::String_cast
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


  bool
  Get_functions::c_Container_has( std::ifstream& _file, 
				  data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return false;
    return data::container.Has( name_id );
  }



  xx::String_cast 
  Get_functions::o_This_object( data::Parser* _p ) const
  {
    if( *m_disabled )
      return xx::String_cast();
    if( _p->m_this_object )
      return xx::String_cast( _p->m_this_object->Get_name_id());
    throw std::runtime_error( "(xx) Parsing ERROR! No 'THIS-OBJECT' found! " );
  }



  bool 
  Get_functions::i_Has_image_data( std::ifstream& _file, 
				   data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string image_data_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return false;
    return the_Printing_manager::Instance().Has_image_data( image_data_id );
  }



  xx::String_cast
  Get_functions::s_This_state( data::Parser* _p ) const
  {
    if( *m_disabled )
      return xx::String_cast();
    if( _p->m_this_state )
      return xx::String_cast( _p->m_this_state->Get_id());
    throw std::runtime_error( "(xx) Parsing ERROR! No 'THIS-STATE' found! " );
  }

  bool 
  Get_functions::s_Has_state( std::ifstream& _file, 
			      data::Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _file, function );
    if( *m_disabled )
      return false;
    return the_Game::Instance().Get_state_machine()->Has_state( name_id );
  }



  int
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

  int
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

  int
  Get_functions::w_Display_width() const
  {
    if( *m_disabled )
      return 0;
    return the_World::Instance().Get_display_width();
  }

  int
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
