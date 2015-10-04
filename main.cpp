 
#include"Game.h"



Game* the_game = NULL;

int main ( int argc, char* args[] )
{
  the_game = new Game();

  the_game->Init( "Test", 480, 320 );

  while( the_game->m_running )
    {
      the_game->Handle_events();
      the_game->Update();
      the_game->Render();
      SDL_Delay( 16 );
    }

  the_game->Clear();
  return 1;
}
