 
#include "Init.h"
#include "Input_handler.h"

#include "Game_world.h"
#include "Game.h"



void Display_resized( int _display_width, int _display_height )
{
  the_World::Instance().Set_display_size( _display_width, _display_height );
  the_Game::Instance().on_Display_resize();
}



int main ( int argc, char* args[] )
{
  the_World::Instance().Setup();

  if ( ! the_Game::Instance().Init( "Helicopter" )) {
    std::cout << "\nMAIN :: !! the_Game.Init() Failed !!\n\n";
    return -1;
  }

  the_Input_handler::Instance().Set_callback_on_display_resize( Display_resized );


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
