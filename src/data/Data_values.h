
#ifndef DATA_VALUES_H
#define DATA_VALUES_H

#include "Parser.h"
#include "xx_String_cast.h"



namespace data
{

  int b_Int( std::ifstream& _file );
  long int b_Long_int( std::ifstream& _file );
  unsigned b_Unsigned( std::ifstream& _file );
  long unsigned b_Long_unsigned( std::ifstream& _file );
  float b_Float( std::ifstream& _file );
  double b_Double( std::ifstream& _file );
  long double b_Long_double( std::ifstream& _file );
  bool b_Bool( std::ifstream& _file );
  char b_Char( std::ifstream& _file );
  xx::String_cast b_String( std::ifstream& _file );



  template< typename T > 
  T m_Add( std::ifstream& _file ) 
  {
    data::Parser p;
    T a = p.Parse_value< T >( _file );
    T b = p.Parse_value< T >( _file );
    return( a + b );
  }

  template< typename T >
  T m_Subtract ( std::ifstream& _file ) 
  {
    data::Parser p;
    T a = p.Parse_value< T >( _file );
    T b = p.Parse_value< T >( _file );
    return( a - b );
  }

  template< typename T >
  T m_Multiply  ( std::ifstream& _file ) 
  {
    data::Parser p;
    T a = p.Parse_value< T >( _file );
    T b = p.Parse_value< T >( _file );
    return( a * b );
  }

  template< typename T >
  T m_Divide ( std::ifstream& _file ) 
  {
    data::Parser p;
    T numerator = p.Parse_value< T >( _file );
    T denominator = p.Parse_value< T >( _file );
    if( denominator != 0 )
      return( numerator / denominator );
    else
      return 0;
  }



  int f_Texture_width( std::ifstream& _file );
  int f_Texture_height( std::ifstream& _file );
  int f_Display_width();
  int f_Display_height();

  template< typename T >
  T f_Random_discrete_num( std::ifstream& _file ) 
  {
    data::Parser p;
    T min = p.Parse_value< T >( _file );
    T max = p.Parse_value< T >( _file );
    return xx::Get_random.Discrete_num< long int >( min, max );
  }
  template< typename T >
  T f_Random_real_num( std::ifstream& _file ) 
  {
    data::Parser p;
    T min = p.Parse_value< T >( _file );
    T max = p.Parse_value< T >( _file );
    return xx::Get_random.Real_num< double >( min, max );
  }

}//data



#endif 
