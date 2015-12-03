 
#include "Init.h"
#include "Input_handler.h"

#include "Game_world.h"
#include "Game.h"



int main ( int argc, char* args[] )
{
  the_World::Instance().Setup();

  if ( ! the_Game::Instance().Init( "Helicopter" )) {
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
