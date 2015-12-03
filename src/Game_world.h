
#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Init.h"



// Singleton Class:
class the_World
{
 private:
  the_World() = default;
  the_World( const the_World& ) = delete;
  the_World& operator=( const the_World& ) = delete;

 public:
  ~the_World() = default;

  static the_World& Instance()
  {
    static the_World instance;
    return instance;
  }

  void Setup( int _display_width = 720, int _display_height = 480, double _fps = 60.0d, bool print_fps = false );

  glm::vec2 Get_display_size() { return glm::vec2( m_display_width, m_display_height ); }
  int Get_display_width() { return m_display_width; }
  int Get_display_height() { return m_display_height; }

  std::chrono::duration< long int, std::nano > Get_delta_time_duration();
  double Get_delta_time();

  void Frame_begin();
  void Frame_end();
 private:
  void Print_fps();

  // --- Variables ---
  int m_display_width;
  int m_display_height;
  // For keeping the 'Frames-Per-Second' steady:
  double m_preferred_fps;
  std::chrono::nanoseconds m_time_period_per_frame;
  std::chrono::steady_clock::time_point m_frame_begin_tp;
  std::chrono::nanoseconds m_missing_microseconds;
  // For Delta Time:
  std::chrono::steady_clock::time_point m_previous_frame_tp;
  std::chrono::duration< long int, std::nano > m_delta_time_duration;
  // For Printing the FPS:
  bool m_print_fps;
  int m_frame_counter;
  std::chrono::steady_clock::time_point m_time_counter_tp;
};



#endif

// Good fps-goles: 120, 100, 80, 75, 60, 50, 40, 30, 25, 20, 15
