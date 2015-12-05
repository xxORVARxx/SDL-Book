 
#include "Game_world.h"

#include "Input_handler.h"



void the_World::Setup( int _display_width, int _display_height, double _fps, bool print_fps )
{
  m_display_width = _display_width;
  m_display_height = _display_height;
  m_preferred_fps = _fps;
  m_time_period_per_frame = std::chrono::seconds( 1 );
  m_time_period_per_frame /= m_preferred_fps;
  m_missing_microseconds = std::chrono::steady_clock::duration::zero();
  m_print_fps = print_fps;
  m_frame_counter = 0;
  m_time_counter_tp = ( std::chrono::steady_clock::now() + std::chrono::seconds( 1 ));
}



std::chrono::duration< long int, std::nano > the_World::Get_delta_time_duration()
{
  return m_delta_time_duration;
}

double the_World::Get_delta_time()
{
  return( (double)m_delta_time_duration.count() / 1000000000 );
}



void the_World::Frame_begin()
{
  // FOR DELTA TIME:
  m_previous_frame_tp = m_frame_begin_tp;
  m_frame_begin_tp = std::chrono::steady_clock::now();

  m_delta_time_duration = ( m_frame_begin_tp - m_previous_frame_tp );
  //std::cout <<"DELTA TIME: "<< (double)m_delta_time_duration.count()/1000000000 <<"\n";

  // FOR PRINTING FPS:
  if( m_print_fps )
    this->Print_fps();
}



// FOR KEEPING THE 'FRAMES-PER-SECOND' STEADY:
void the_World::Frame_end()
{
  // This is how long this frame took:
  std::chrono::duration< long int, std::nano > frame_duration( std::chrono::steady_clock::now() - m_frame_begin_tp );

  // If there is any time left to burn: (if the FPS is 60, every frame should take 0.016667 seconds)
  if( frame_duration < m_time_period_per_frame )
    {
      // This is how much time is left of the time we want this frame to take: (to keep the FPS right)
      // And we are adding the 'missing_nanoseconds' from the previous frame:
      std::chrono::nanoseconds frame_time_to_burn = ( m_time_period_per_frame - frame_duration + m_missing_microseconds );
      // Casting from 'nano' to 'milli' for the 'SDL_Delay', but this will truncate and we'll lose some 'nanoseconds':
      std::chrono::milliseconds delay_time = std::chrono::duration_cast< std::chrono::milliseconds >( frame_time_to_burn );
      // Store the 'missing_nanoseconds' so we can add it to the next frame:
      m_missing_microseconds = ( frame_time_to_burn - delay_time );

      SDL_Delay( delay_time.count() );
      /*
      std::cout <<"FPS: "<< m_preferred_fps <<"    "
		<<"Frame-Time: "<< (double)m_time_period_per_frame.count()/1000000 <<"    "
		<<"Time-Used + Missing-ns: "<< (double)frame_duration.count()/1000000 <<"   \t "
		<<"To-Burn: "<< (double)frame_time_to_burn.count()/1000000 <<" \t "
		<<"Delay: "<< delay_time.count() <<" \t "
		<<"Missing-ns: "<< (double)m_missing_microseconds.count()/1000000 <<" (ms)\n";
      */
    }
}



void the_World::Print_fps()
{
  if( m_time_counter_tp < m_frame_begin_tp )
    {
      std::cout <<"WORLD :: Frames-Per-Second: "<< m_frame_counter <<"   "
		<<"DELTA-TIME: "<< this->Get_delta_time() <<" sec\n";
      m_time_counter_tp = ( m_frame_begin_tp + std::chrono::seconds( 1 ));
      m_frame_counter = 0;
    }
  m_frame_counter++;
}
