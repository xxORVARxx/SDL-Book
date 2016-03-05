
#include "Init.h"



namespace xx
{
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
