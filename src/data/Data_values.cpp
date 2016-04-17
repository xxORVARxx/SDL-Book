
#include "Data_values.h"
#include "Texture_manager_v2.h"

#include "Game_world.h"



namespace data
{

  int
  b_Int( std::ifstream& _file ) 
  {
    int i;
    _file >> i;
    return i;
  }

  long int
  b_Long_int( std::ifstream& _file ) 
  {
    int li;
    _file >> li;
    return li;
  }

  unsigned
  b_Unsigned( std::ifstream& _file ) 
  {
    unsigned u;
    _file >> u;
    return u;
  }
  long unsigned
  b_Long_unsigned( std::ifstream& _file ) 
  {
    unsigned lu;
    _file >> lu;
    return lu;
  }

  float
  b_Float( std::ifstream& _file ) 
  {
    float f;
    _file >> f;
    return f;
  }

  double
  b_Double( std::ifstream& _file ) 
  {
    double d;
    _file >> d;
    return d;
  }

  long double
  b_Long_double( std::ifstream& _file ) 
  {
    double ld;
    _file >> ld;
    return ld;
  }

  bool
  b_Bool( std::ifstream& _file ) 
  {
    bool b;
    _file >> b;
    return b;
  }

  char
  b_Char( std::ifstream& _file ) 
  {
    char c;
    _file >> c;
    return c;
  }

  xx::String_cast
  b_String( std::ifstream& _file ) 
  {
    std::string std_s;
    _file >> std_s;
    xx::String_cast sog_s = std_s;
    return sog_s;
  }



  int
  f_Texture_width( std::ifstream& _file ) 
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
  f_Texture_height( std::ifstream& _file )
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
  f_Display_width() 
  {
    return the_World::Instance().Get_display_width();
  }

  int
  f_Display_height() 
  {
    return the_World::Instance().Get_display_height();
  }

}//data
