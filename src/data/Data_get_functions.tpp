
#include "Texture_manager_v2.h"
#include "Game_world.h"
#include "Game.h"
#include "State.h"



namespace data
{
  int
  Get_functions::b_Int( bool _disabled, 
			std::ifstream& _file ) const
  {
    int i;
    _file >> i;
    if( _disabled )
      return 0;
    return i;
  }

  long int
  Get_functions::b_Long_int( bool _disabled, 
			     std::ifstream& _file ) const
  {
    int li;
    _file >> li;
    if( _disabled )
      return 0;
    return li;
  }

  unsigned
  Get_functions::b_Unsigned( bool _disabled, 
			     std::ifstream& _file ) const
  {
    unsigned u;
    _file >> u;
    if( _disabled )
      return 0;
    return u;
  }

  long unsigned
  Get_functions::b_Long_unsigned( bool _disabled, 
				  std::ifstream& _file ) const
  {
    unsigned lu;
    _file >> lu;
    if( _disabled )
      return 0;
    return lu;
  }

  float
  Get_functions::b_Float( bool _disabled, 
			  std::ifstream& _file ) const
  {
    float f;
    _file >> f;
    if( _disabled )
      return 0.0;
    return f;
  }

  double
  Get_functions::b_Double( bool _disabled, 
			   std::ifstream& _file ) const
  {
    double d;
    _file >> d;
    if( _disabled )
      return 0.0;
    return d;
  }

  long double
  Get_functions::b_Long_double( bool _disabled, 
				std::ifstream& _file ) const
  {
    double ld;
    _file >> ld;
    if( _disabled )
      return 0.0;
    return ld;
  }

  bool
  Get_functions::b_Bool( bool _disabled, 
			 std::ifstream& _file ) const
  {
    std::string str;
    _file >> str;
    if( _disabled )
      return false;
    for( char& c : str )
      c = std::tolower( c );
    if(( str == "0" )||( str == "0.0" )||( str == "false" )||( str == "'false'" )||( str == "\"false\"" )||
       ( str == "'0'" )||( str == "\"0\"" )||( str == "'0.0'" )||( str == "\"0.0\"" ))
      return false;
    return true;
  }

  char
  Get_functions::b_Char( bool _disabled, 
			 std::ifstream& _file ) const
  {
    char c;
    _file >> c;
    if( _disabled )
      return 0;
    return c;
  }

  xx::String_cast
  Get_functions::b_String( bool _disabled, 
			   std::ifstream& _file ) const
  {
    std::string str;
    _file >> str;
    if( *str.begin() != '"' )
      data::Throw_file_corrupted( " String not starting with a double-quote: \" ." );
    if( *str.rbegin() == '"' )
      {
	if( _disabled )
	  return xx::String_cast();
	return xx::String_cast( std::string( str.begin() + 1, str.end() - 1 ));
      }
    str.erase( 0, 1 );
    while( _file.good())
      {
	char c;
        _file.get( c );
	if( c == '"' )
	  {
	    if( _disabled )
	      return xx::String_cast();
	    return xx::String_cast( str );
	  }
	str += c;
      }//while
    data::Throw_file_corrupted( " String not ending with a double-quote: \" ." );
  }


  bool
  Get_functions::c_Container_has( bool _disabled, 
				  std::ifstream& _file, 
				  Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return false;
    return data::container.Has( name_id );
  }



  xx::String_cast
  Get_functions::s_This_state( bool _disabled, 
			       Parser* _p ) const
  {
    if( _disabled )
      return xx::String_cast();
    if( _p->m_this_state )
      return xx::String_cast( _p->m_this_state->Get_id());
    throw std::runtime_error( "(xx) Parsing ERROR! No 'THIS-STATE' found!" );
  }

  bool 
  Get_functions::s_Has_state( bool _disabled, 
			      std::ifstream& _file, 
			      Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return false;
    return the_Game::Instance().Get_state_machine()->Has_state( name_id );
  }



  int
  Get_functions::t_Texture_width( bool _disabled, 
				  std::ifstream& _file, 
				  Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return 0;
    SDL_Point size;
    if( the_Texture_manager_v2::Instance().Get_texture_size( id, size ))
      return size.x;
    throw std::invalid_argument( "(xx) Parsing ERROR! When geting texture's WIDTH. No texture with the ID: '" + id + "'!" );
  }

  int
  Get_functions::t_Texture_height( bool _disabled, 
				   std::ifstream& _file, 
				   Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return 0;
    SDL_Point size;
    if( the_Texture_manager_v2::Instance().Get_texture_size( id, size ))
      return size.y;
    else
      throw std::invalid_argument( "(xx) Parsing ERROR! When geting texture's HEIGHT. No texture with the ID: '" + id + "'!" );
  }

  int
  Get_functions::w_Display_width( bool _disabled ) const
  {
    if( _disabled )
      return 0;
    return the_World::Instance().Get_display_width();
  }

  int
  Get_functions::w_Display_height( bool _disabled ) const
  {
    if( _disabled )
      return 0;
    return the_World::Instance().Get_display_height();
  }
}//data



namespace data
{
  template< typename T > 
  T 
  Get_functions::m_Add( bool _disabled, 
			std::ifstream& _file, 
			Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _disabled, _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _disabled, _file, function );
    return( a + b );
  }

  template< typename T >
  T 
  Get_functions::m_Subtract( bool _disabled, 
			     std::ifstream& _file, 
			     Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _disabled, _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _disabled, _file, function );
    return( a - b );
  }

  template< typename T >
  T 
  Get_functions::m_Multiply( bool _disabled, 
			     std::ifstream& _file, 
			     Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _disabled, _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _disabled, _file, function );
    return( a * b );
  }

  template< typename T >
  T 
  Get_functions::m_Divide( bool _disabled, 
			   std::ifstream& _file, 
			   Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    T numerator = _p->Next_get_functions< T >( _disabled, _file, function );
    function = data::Next_line_from_file( _file );
    T denominator = _p->Next_get_functions< T >( _disabled, _file, function );
    if( denominator != 0 )
      return( numerator / denominator );
    else
      return 0;
  }

  template< typename T >
  T 
  Get_functions::f_Random_discrete_num( bool _disabled, 
					std::ifstream& _file ) const
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
  Get_functions::f_Random_real_num( bool _disabled, 
				    std::ifstream& _file ) const
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
  Get_functions::c_Container_get( bool _disabled, 
				  std::ifstream& _file, 
				  Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return 0;
    T value;
    data::container.Get( name_id, value );
    return value;
  }

  template< typename T >
  T 
  Get_functions::c_Container_take( bool _disabled, 
				   std::ifstream& _file, 
				   Parser* _p ) const
  {
    std::string function = data::Next_line_from_file( _file );
    std::string name_id = _p->Next_get_functions< xx::String_cast >( _disabled, _file, function );
    if( _disabled )
      return 0;
    T value;
    data::container.Take( name_id, value );
    return value;
  }
}//data
