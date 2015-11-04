
#include "Init.h"
#include "Input_handler.h"
#include "Game.h"



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
};

