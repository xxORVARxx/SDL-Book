
#include "The_xx_namespace.h"



namespace xx
{
  std::string Read_string_from_file( std::ifstream& _file, std::string _str )
  {
    if( _str.empty())
      _file >> _str;
    if( *_str.begin() != '"' )
      throw std::ios::failure( "(xx) String not starting with a double-quote: \" !" );
    if( *_str.rbegin() == '"' )
      return std::string( _str.begin() + 1, _str.end() - 1 );
    _str.erase( 0, 1 );
    while( _file.good())
      {
	char c;
        _file.get( c );
	if( c == '"' )
	  return _str;
	_str += c;
      }//while
    throw std::ios::failure( "(xx) String not ending with a double-quote: \" !" );
  }
}//xx



namespace xx
{
  void Zero_out_SDL_Rect( SDL_Rect& _r )
  {
    _r.x = _r.y = 0;
    _r.w = _r.h = 0;
  }

  void Zero_out_SDL_Point( SDL_Point& _p )
  {
    _p.x = _p.y = 0;
  }



  bool Point_in_rect( const glm::vec2& _p, const glm::vec4& _r )
  {
    return (( _p.x >= _r.x )&&( _p.x < ( _r.x + _r.z ))&&
	    ( _p.y >= _r.y )&&( _p.y < ( _r.y + _r.w ))) ? true : false;
  }

  bool Point_in_rect( const SDL_Point& _p, const SDL_Rect& _r )
  {
    return (( _p.x >= _r.x )&&( _p.x < ( _r.x + _r.w ))&&
	    ( _p.y >= _r.y )&&( _p.y < ( _r.y + _r.h ))) ? true : false;
  }



  void Clamp_degrees( float& _degrees )
  {
    while( _degrees > 360.0f )
      _degrees -= 360.0f;
    while( _degrees <= 0.0f )
      _degrees += 360.0f;
  }

  void Clamp_degrees( double& _degrees )
  {
    while( _degrees > 360.0d )
      _degrees -= 360.0d;
    while( _degrees <= 0.0d )
      _degrees += 360.0d;
  }



  float Vec_to_degrees( const glm::vec2& _vec )
  {
    if( _vec.y > 0 )
      return( std::acos( glm::normalize( _vec ).x ) * 180.0f / M_PI );
    else
      return( 360.0f - ( std::acos( glm::normalize( _vec ).x ) * 180.0f / M_PI ));
  }

  glm::vec2 Degrees_to_vec( const float& _degrees )
  {
    return glm::vec2( std::cos( _degrees * M_PI / 180.0f ), std::sin( _degrees * M_PI / 180.0f ));
  }
}//xx



namespace xx
{
  std::string Date_and_time::Get_date_string( std::string _y2m, std::string _m2d )
  {
    this->Update_date();
    std::string the_date = std::to_string( year );
    the_date += _y2m;
    the_date += ( month < 10 ) ? '0' + std::to_string( month ) : std::to_string( month );
    the_date += _m2d;
    the_date += ( day < 10 ) ? '0' + std::to_string( day ) : std::to_string( day );
    return the_date;
  }

  std::string Date_and_time::Get_time_string( std::string _h2min, std::string _min2sec, std::string _sec2ms )
  {
    this->Update_time();
    std::string the_time = ( hour < 10 ) ? '0' + std::to_string( hour ) : std::to_string( hour );
    the_time += _h2min;
    the_time += ( minute < 10 ) ? '0' + std::to_string( minute ) : std::to_string( minute );
    the_time += _min2sec;
    the_time += ( second < 10 ) ? '0' + std::to_string( second ) : std::to_string( second );
    the_time += _sec2ms;
    the_time += ( milli < 100 ) ? '0' + (( milli < 10 ) ? '0' + std::to_string( milli ) : std::to_string( milli )) : std::to_string( milli );
    return the_time;
  }

  void Date_and_time::Update_date()
  {
    time_t now = time( nullptr );
    tm* ltm = localtime( &now );
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
  }

  void Date_and_time::Update_time()
  {
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::chrono::hours h = std::chrono::duration_cast< std::chrono::hours >( tp.time_since_epoch());
    std::chrono::minutes min = std::chrono::duration_cast< std::chrono::minutes >( tp.time_since_epoch());
    std::chrono::seconds sec = std::chrono::duration_cast< std::chrono::seconds >( tp.time_since_epoch());
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >( tp.time_since_epoch());   
    ms -= sec;
    sec -= min;
    min -= h;
    milli = ms.count();
    second = sec.count();
    minute = min.count();
    hour = h.count() % 24;
  }
}//xx
