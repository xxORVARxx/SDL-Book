 
#include "Init.h"
#include "Game_world.h"
#include "Game.h"
#include "Input_handler.h"



int main ( int argc, char* args[] )
{
  the_World::Instance().Setup( 60, true );

  if ( ! the_Game::Instance().Init( "Test", 720, 480 )) {
    std::cout << "\nMAIN :: !! the_Game.Init() Failed !!\n\n";
    return -1;
  }


  while( the_Input_handler::Instance().is_Running() )
    {
      the_World::Instance().Frame_begin();

      // GAME:
      the_Game::Instance().Handle_events();
      the_Game::Instance().Update();
      the_Game::Instance().Render();

      the_World::Instance().Frame_end();
    }


  the_Game::Instance().Clean();
  return 0;
}
