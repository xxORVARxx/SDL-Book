
#include "Init.h"



namespace xx
{
  bool Point_in_rect( const glm::vec2& p, const glm::vec4& r )
  {
    return ( (p.x >= r.x) && (p.x < (r.x + r.z)) &&
	     (p.y >= r.y) && (p.y < (r.y + r.w)) ) ? true : false;
  }

  bool Point_in_rect( const SDL_Point& p, const SDL_Rect& r )
  {
    return ( (p.x >= r.x) && (p.x < (r.x + r.w)) &&
	     (p.y >= r.y) && (p.y < (r.y + r.h)) ) ? true : false;
  }



  float Vec_to_degrees( glm::vec2 _vec )
  {
    if( _vec.y > 0 )
      return( std::acos( glm::normalize( _vec ).x ) * 180.0f / M_PI );
    else
      return( 360.0f - ( std::acos( glm::normalize( _vec ).x ) * 180.0f / M_PI ));
  }

  glm::vec2 Degrees_to_vec( float _degrees )
  {
    return glm::vec2( std::cos( _degrees * M_PI / 180.0f ), std::sin( _degrees * M_PI / 180.0f ));
  }
};
