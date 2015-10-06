 
#include "Init.h"
#include "Game.h"



int main ( int argc, char* args[] )
{
  if ( ! Game::Instance()->Init( "Test", 720, 480 )) {
    std::cout << "\n!! the_Game.Init() Failed !!\n\n";
    return -1;
  }

  while( Game::Instance()->m_running )
    {
      Game::Instance()->Handle_events();
      Game::Instance()->Update();
      Game::Instance()->Render();
      SDL_Delay( 16 );
    }

  Game::Instance()->Clean();
  return 0;
}
