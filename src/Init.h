
/* To compile use: 
 *   $ g++ -std=c++11 -o test *.cpp -lSDL2 -lSDL2_image
 *
 * To check if packages/liberys are installed:  
 *   $ dpkg -l | grep THE-PACKAGE-NAME
 * To see available packages/liberys:  
 *   $ apt-cache search THE-PACKAGE-NAME
 *
 * Needed Liberys:
 *   libsdl2-dev
 *   libsdl2-image-dev
 *   libglm-dev
 *  
 * Other good Liberys:
 *   libglew-dev
 *   libsdl2-ttf-dev
 *   libsdl2-mixer-dev
 *   libsdl2-net-dev
 *   libsdl2-gfx-dev
 *   libfreetype6-dev
 */

#ifndef INIT_H
#define INIT_H


#define GLM_FORCE_CXX11 
#include <glm/glm.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <algorithm>

#include <string>
#include <vector>
#include <map>

#include <chrono>
#include <random>



namespace xx
{
  bool Point_in_rect( const glm::vec2& _p, const glm::vec4& _r );
  bool Point_in_rect( const SDL_Point& _p, const SDL_Rect& _r );

  void Clamp_degrees( float& _degrees );
  void Clamp_degrees( double& _degrees );

  float Vec_to_degrees( const glm::vec2& _vec );
  glm::vec2 Degrees_to_vec( const float& _degrees );
};



namespace xx
{
  class Random
  {
  public:
  Random( bool _use_seed = false, int _seed = 0 ) : m_seed(_seed)
    {
      if( _use_seed )  m_engine.seed( _seed );
      else  m_engine.seed( m_true_random_devic() );
    }
    template< typename T >
      T Discrete_num( T _a, T _b )
      {
	std::uniform_int_distribution< T > discrete_dist( _a, _b );
	return discrete_dist( m_engine );
      }
    template< typename T >
      T Real_num( T _a, T _b )
      {
	std::uniform_real_distribution< T > real_dist( _a, _b );
	return real_dist( m_engine );
      }
  private:
    // --- Variables ---
    int m_seed;
    std::random_device m_true_random_devic;
    std::mt19937 m_engine;
  } static Get_random;
};



#endif

/* Open GL:
GLboolean   1+

GLbyte      8
GLubyte     8

GLshort     16
GLushort    16

GLint       32
GLuint      32

GLint64     64
GLuint64    64
*/

/* SDL:
Uint8
Uint16
Uint32

Sint32
*/
