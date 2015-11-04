 
#include "Init.h"
#include "Input_handler.h"
#include "Game.h"



const Uint32 FPS = 60;
const Uint32 DELAY_TIME = 1000.0f / FPS;

int main ( int argc, char* args[] )
{
  Uint32 frame_start, frame_time;

  if ( ! the_Game::Instance().Init( "Test", 720, 480 )) {
    std::cout << "\nMAIN :: !! the_Game.Init() Failed !!\n\n";
    return -1;
  }


  //for( int i = 0 ; i < 10 ; ++i )
  while( the_Input_handler::Instance().is_Running() )
    {
      frame_start = SDL_GetTicks();

      // GAME:
      the_Game::Instance().Handle_events();
      the_Game::Instance().Update();
      the_Game::Instance().Render();

      // FPS:
      frame_time = SDL_GetTicks() - frame_start;
      //std::cout << "Loop Time : " << frame_time << " ms  \t";
      if( frame_time < DELAY_TIME ) {
	SDL_Delay( (int)( DELAY_TIME - frame_time ));
	//std::cout << "Delay : " << (int)( DELAY_TIME - frame_time ) << " ms  \t";
      }
      //std::cout << "Frame Time : " << SDL_GetTicks() - frame_start << " ms\n";
    }


  the_Game::Instance().Clean();
  return 0;
}
