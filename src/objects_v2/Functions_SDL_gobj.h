
#ifndef FUNCTIONS_SDL_GOBJ_H
#define FUNCTIONS_SDL_GOBJ_H

#include "Init.h"
#include "Game_world.h"
#include "Texture_manager_v2.h"
#include "xx_String_cast.h"
/*
namespace sgo {
  template< typename T > T Get_value( std::ifstream& _file );
}//sgo



namespace sgo
{
  int f_Int( std::ifstream& _file ) {
    int i;
    _file >> i;
    return i;
  }
  unsigned f_Unsigned( std::ifstream& _file ) {
    unsigned u;
    _file >> u;
    return u;
  }
  float f_Float( std::ifstream& _file ) {
    float f;
    _file >> f;
    return f;
  }
  double f_Double( std::ifstream& _file ) {
    double d;
    _file >> d;
    return d;
  }
  bool f_Bool( std::ifstream& _file ) {
    bool b;
    _file >> b;
    return b;
  }
  char f_Char( std::ifstream& _file ) {
    char c;
    _file >> c;
    return c;
  }
  xx::String_cast f_String( std::ifstream& _file ) {
    std::string std_s;
    _file >> std_s;
    xx::String_cast sog_s = std_s;
    return sog_s;
  }

  template< typename T >
  T f_Add( std::ifstream& _file ) {
    T a = sgo::Get_value< T >( _file );
    T b = sgo::Get_value< T >( _file );
    return( a + b );
  }
  template< typename T >
  T f_Subtract ( std::ifstream& _file ) {
    T a = sgo::Get_value< T >( _file );
    T b = sgo::Get_value< T >( _file );
   return( a - b );
  }
  template< typename T >
  T f_Multiply  ( std::ifstream& _file ) {
    T a = sgo::Get_value< T >( _file );
    T b = sgo::Get_value< T >( _file );
   return( a * b );
  }
  template< typename T >
  T f_Divide ( std::ifstream& _file ) {
    T numerator = sgo::Get_value< T >( _file );
    T denominator = sgo::Get_value< T >( _file );
    if( denominator != 0 )
      return( numerator / denominator );
    else
      return 0;
  }

  int f_Texture_width( std::ifstream& _file ) {
    std::string id;
    _file >> id;
    SDL_Point size;
    if( the_Texture_manager_v2::Instance().Get_texture_size( id, size ))
      return size.x;
    else
      return 0;
  }
  int f_Texture_height( std::ifstream& _file ){
    std::string id;
    _file >> id;
    SDL_Point size;
    if( the_Texture_manager_v2::Instance().Get_texture_size( id, size ))
      return size.y;
    else
      return 0;
  }
  int f_Display_width() {
    return the_World::Instance().Get_display_width();
  }
  int f_Display_height() {
    return the_World::Instance().Get_display_height();
  }
  template< typename T >
  T f_Random_discrete_num( std::ifstream& _file ) {
    T min = sgo::Get_value< T >( _file );
    T max = sgo::Get_value< T >( _file );
    return xx::Get_random.Discrete_num< long int >( min, max );
  }
  template< typename T >
  T f_Random_real_num( std::ifstream& _file ) {
    T min = sgo::Get_value< T >( _file );
    T max = sgo::Get_value< T >( _file );
    return xx::Get_random.Real_num< double >( min, max );
  }
}//sgo



namespace sgo
{
  template< typename T >
  T Get_value( std::ifstream& _file )
  {
    T value;
    std::string function;
    _file >> function;

    if( function == "f_Int" )
      value = f_Int( _file );
    else if( function == "f_Unsigned" )
      value = f_Unsigned( _file );
    else if( function == "f_Float" )
      value = f_Float( _file );
    else if( function == "f_Double" )
      value = f_Double( _file );
    else if( function == "f_Bool" )
      value = f_Bool( _file );
    else if( function == "f_Char" )
      value = f_Char( _file );
    else if( function == "f_String" )
      value = f_String( _file );

    else if( function == "f_Add" )
      value = f_Add< T >( _file );
    else if( function == "f_Subtract" )
      value = f_Subtract< T >( _file );
    else if( function == "f_Multiply" )
      value = f_Multiply< T >( _file );
    else if( function == "f_Divide" )
      value = f_Divide< T >( _file );

    else if( function == "f_Texture_width" )
      value = f_Texture_width( _file );
    else if( function == "f_Texture_height" )
      value = f_Texture_height( _file );
    else if( function == "f_Display_width" )
      value = f_Display_width();
    else if( function == "f_Display_height" )
      value = f_Display_height();
    else if( function == "f_Random_discrete_num" )
      value = f_Random_discrete_num< T >( _file );
    else if( function == "f_Random_real_num" )
      value = f_Random_real_num< T >( _file );

    else
      throw std::ios::failure( "Error object's data file corrupted!" );

    return value;
  }
}//sgo
*/


std::string Make_file_name( std::string _id, std::string _name = "" )
{
  if( _name.empty() )
    _name = std::to_string( xx::Get_random.Discrete_num( 0, 9999 ));
  return ( xx::dt.Get_date_string( "_", "_" ) + '-' + 
	   xx::dt.Get_time_string( "_", "_", "_" ) + '-' + 
	   _id + '-' + _name );
}



#endif
