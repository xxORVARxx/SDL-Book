
#ifndef FUNCTIONS_SDL_GOBJ_H
#define FUNCTIONS_SDL_GOBJ_H

#include "Init.h"



std::string Make_file_name( std::string _id, std::string _name = "" )
{
  if( _name.empty() )
    _name = std::to_string( xx::Get_random.Discrete_num( 0, 9999 ));
  return ( xx::dt.Get_date_string( "_", "_" ) + '-' + 
	   xx::dt.Get_time_string( "_", "_", "_" ) + '-' + 
	   _id + '-' + _name );
}



#endif
