
#include "Texture_manager_v2.h"
#include "Game_world.h"



namespace data
{
  int
  Get_functions::b_Int( std::ifstream& _file ) 
  {
    int i;
    _file >> i;
    return i;
  }

  long int
  Get_functions::b_Long_int( std::ifstream& _file ) 
  {
    int li;
    _file >> li;
    return li;
  }

  unsigned
  Get_functions::b_Unsigned( std::ifstream& _file ) 
  {
    unsigned u;
    _file >> u;
    return u;
  }
  long unsigned
  Get_functions::b_Long_unsigned( std::ifstream& _file ) 
  {
    unsigned lu;
    _file >> lu;
    return lu;
  }

  float
  Get_functions::b_Float( std::ifstream& _file ) 
  {
    float f;
    _file >> f;
    return f;
  }

  double
  Get_functions::b_Double( std::ifstream& _file ) 
  {
    double d;
    _file >> d;
    return d;
  }

  long double
  Get_functions::b_Long_double( std::ifstream& _file ) 
  {
    double ld;
    _file >> ld;
    return ld;
  }

  bool
  Get_functions::b_Bool( std::ifstream& _file ) 
  {
    bool b;
    _file >> b;
    return b;
  }

  char
  Get_functions::b_Char( std::ifstream& _file ) 
  {
    char c;
    _file >> c;
    return c;
  }

  xx::String_cast
  Get_functions::b_String( std::ifstream& _file ) 
  {
    std::string str;
    _file >> str;
    if( *str.begin() != '"' )
      data::Throw_file_corrupted( " String not starting with a double-quote: \" ." );
    if( *str.rbegin() == '"' )
      return xx::String_cast( std::string( str.begin() + 1, str.end() - 1 ));
    str.erase( 0, 1 );
    while( _file.good())
      {
	char c;
        _file.get( c );
	if( c == '"' )
	  return xx::String_cast( str );
	str += c;
      }//while
    data::Throw_file_corrupted( " String not ending with a double-quote: \" ." );
  }



  int
  Get_functions::t_Texture_width( std::ifstream& _file ) 
  {
    std::string id;
    _file >> id;
    SDL_Point size;
    if( the_Texture_manager_v2::Instance().Get_texture_size( id, size ))
      return size.x;
    else
      return 0;
  }

  int
  Get_functions::t_Texture_height( std::ifstream& _file )
  {
    std::string id;
    _file >> id;
    SDL_Point size;
    if( the_Texture_manager_v2::Instance().Get_texture_size( id, size ))
      return size.y;
    else
      return 0;
  }

  int
  Get_functions::w_Display_width() 
  {
    return the_World::Instance().Get_display_width();
  }

  int
  Get_functions::w_Display_height() 
  {
    return the_World::Instance().Get_display_height();
  }
}//data



namespace data
{
  template< typename T > 
  T 
  Get_functions::m_Add( std::ifstream& _file, Parser* _p ) 
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _file, function );
    return( a + b );
  }

  template< typename T >
  T 
  Get_functions::m_Subtract ( std::ifstream& _file, Parser* _p ) 
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _file, function );
    return( a - b );
  }

  template< typename T >
  T 
  Get_functions::m_Multiply  ( std::ifstream& _file, Parser* _p ) 
  {
    std::string function = data::Next_line_from_file( _file );
    T a = _p->Next_get_functions< T >( _file, function );
    function = data::Next_line_from_file( _file );
    T b = _p->Next_get_functions< T >( _file, function );
    return( a * b );
  }

  template< typename T >
  T 
  Get_functions::m_Divide ( std::ifstream& _file, Parser* _p ) 
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
  Get_functions::f_Random_discrete_num( std::ifstream& _file ) 
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
  Get_functions::f_Random_real_num( std::ifstream& _file ) 
  {
    /*
      data::Parser p;
      T min = p.Parse_value< T >( _file );
      T max = p.Parse_value< T >( _file );
      return xx::Get_random.Real_num< double >( min, max );
    */
  }
}//data
