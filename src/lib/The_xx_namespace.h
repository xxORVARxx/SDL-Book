
#ifndef THE_XX_NAMESPACE_H
#define THE_XX_NAMESPACE_H

#define GLM_FORCE_CXX11 
#include <glm/glm.hpp>

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include <ctime>
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
}//xx



namespace xx
{
  class Random
  {
  public:
  Random( bool _use_seed = false, int _seed = 0 ) : m_seed(_seed)
    {
      if( _use_seed == false ) 
	_seed = std::chrono::system_clock::now().time_since_epoch().count(); 
      m_engine.seed( _seed );
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
    int Get_seed() { return m_seed; }
  private:
    // --- Variables ---
    int m_seed;
    std::mt19937 m_engine;
  } static Get_random;
}//xx



namespace xx
{
  class Date_and_time
  {
  public:
    std::string Get_date_string( std::string _y2m = " ", std::string _m2d = " " );
    std::string Get_time_string( std::string _h2min = " ", std::string _min2sec = " ", std::string _sec2ms = " " );
  private:
    void Update_date();
    void Update_time();
    // --- Variables ---
    unsigned year;
    unsigned month;
    unsigned day;
    unsigned hour;
    unsigned minute;
    unsigned second;
    unsigned milli;
  } static dt;
}//xx



#endif
