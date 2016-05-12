 
#include "Printer.h"
#include "xx_String_cast.h"



void 
Check_for_line_comments( std::ifstream& _file )
{
  _file >> std::ws;
  while(( _file.peek() == '#' )&& _file.good())
    {
      _file.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
      _file >> std::ws;
    }
}



void 
Parse_xywh( std::ifstream& _file,
	    SDL_Rect& _xywh, 
	    std::string& _order )
{
  bool x_ok, y_ok, w_ok, h_ok;
  x_ok = y_ok = w_ok = h_ok = false;
  for( int i = 0 ; i < 4 ; ++i )
    {
      Check_for_line_comments( _file );
      switch( _order[i] )
	{
	case 'x':
	case 'X':
	  _file >> _xywh.x;
	  x_ok = true;
	  break;
	case 'y':
	case 'Y':
	  _file >> _xywh.y;
	  y_ok = true;
	  break;
	case 'w':
	case 'W':
	  _file >> _xywh.w;
	  w_ok = true;
	  break;
	case 'h':
	case 'H':
	  _file >> _xywh.h;
	  h_ok = true;
	  break;
	default:
	  throw std::invalid_argument( std::string( "(xx) Printer ERROR! Expected: Any of (but only) the following characters  x  y  w  h . But not this: '" ) + _order[i] +"'! " );
	}//switch
      if( ! _file.good())
	throw std::ios::failure( "(xx) Printer ERROR! file corrupted. When reading XYWH! " );
    }//for
  if(( ! x_ok )||( _xywh.x < 0 ))
    throw xx::Missing_argument( "(xx) Printer ERROR! Expected:  x  and then the frame's position, in pixels on the x axis, in the image. The position cannot be less than zero! " );
  if(( ! y_ok )||( _xywh.y < 0 ))
    throw xx::Missing_argument( "(xx) Printer ERROR! Expected:  y  and then the frame's position, in pixels on the y axis, in the image. The position cannot be less than zero! " );
  if(( ! w_ok )||( _xywh.w <= 0 ))
    throw xx::Missing_argument( "(xx) Printer ERROR! Expected:  w  and then the frame's WIDTH in pixels. The width has to be greater than zero! " );
  if(( ! h_ok )||( _xywh.h <= 0 ))
    throw xx::Missing_argument( "(xx) Printer ERROR! Expected:  h  and then the frame's HEIGHT in pixels. The height has to be greater than zero! " );
}



void
Parse_milliseconds( std::ifstream& _file,
		    float& _ms )
{
  char c;
  Check_for_line_comments( _file );
  _file >> c;
  if(( c != 'm' )&&( c != 'M' ))
    throw xx::Missing_argument( std::string( "(xx) Printer ERROR! Expected:  m  and then the frame display time in milliseconds. Unexpected: '" ) + c +"'! " );
  Check_for_line_comments( _file );
  _file >> _ms;
  if( _ms <= 0.0f )
    throw std::invalid_argument( xx::String_cast( "(xx) Printer ERROR! Expected: Frame display time to be more the zero milliseconds. Unexpected: '" ) + _ms +"'ms! " );
  if( ! _file.good())
    throw std::ios::failure( "(xx) Printer ERROR! file corrupted. When reading MILLISECONDS! " );
}



void
Parse_offset( std::ifstream& _file,
	      SDL_Point& _oxy, 
	      std::string& _order )
{
  bool x_ok = false;
  bool y_ok = false;
  if( _order.size() != 3 )
    throw std::invalid_argument( "(xx) Printer ERROR! Expected: Only the characters:  oxy  or:  oyx . And not this: '"+ _order +"'! " );
  for( int i = 1 ; i < 3 ; ++i )
    {
      Check_for_line_comments( _file );
      switch( _order[i] )
	{
	case 'x':
	case 'X':
	  _file >> _oxy.x;
	  x_ok = true;
	  break;
	case 'y':
	case 'Y':
	  _file >> _oxy.y;
	  y_ok = true;
	  break;
	default:
	  throw std::invalid_argument( std::string( "(xx) Printer ERROR! Expected: The following characters  x  y . But not this: '" ) + _order[i] +"'! " );
	}//switch
      if( ! _file.good())
	throw std::ios::failure( "(xx) Printer ERROR! file corrupted. when reading OFFSET! " );
    }//for
  if( ! x_ok )
    throw xx::Missing_argument( "(xx) Printer ERROR! Expected:  x  and then the frame's printing offset, in pixels on the x axis! " );
  if( ! y_ok )
    throw xx::Missing_argument( "(xx) Printer ERROR! Expected:  y  and then the frame's printing offset, in pixels on the y axis! " );
}
