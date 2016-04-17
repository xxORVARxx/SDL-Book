
#include "Game.h"
#include "Input_handler.h"
#include "Texture_manager_v2.h"

#include "Game_world.h"
/*
#include "State_main_menu.h"
#include "Factory_game_obj.h"

#include "Game.h"
#include "Game_obj_grid.h"
#include "Game_obj_sheet_button.h"
#include "Game_obj_sheet_enemy.h"
#include "Game_obj_sheet_player.h"
*/



// --- Constructors ---
the_Game::the_Game()
{
  m_display_ptr = nullptr;//NULL
  m_renderer_ptr = nullptr;//NULL
}



// --- Functions ---
bool the_Game::Init( std::string _title )
{
  // Initializing_SDL2:
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    std::cout << "GAME :: !! Failed to initialize SDL : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_display_ptr = SDL_CreateWindow( _title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				    the_World::Instance().Get_display_width(), 
				    the_World::Instance().Get_display_height(), 
				    SDL_WINDOW_RESIZABLE );
  if ( m_display_ptr == nullptr ) {
    std::cout << "GAME :: !! Failed to create window : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_renderer_ptr = SDL_CreateRenderer( m_display_ptr, -1, SDL_RENDERER_ACCELERATED );
  if ( m_renderer_ptr == nullptr ) {
    std::cout << "GAME :: !! Failed to create renderer : " << SDL_GetError() << " !!\n";  
    return false;
  }

  // SDL Version:
  SDL_version compiled, linked;
  SDL_VERSION( &compiled );
  SDL_GetVersion( &linked );
  std::cout <<"GAME :: We compiled against SDL version: "
	    << (int)compiled.major <<"."<< (int)compiled.minor <<"."<< (int)compiled.patch <<"\n";
  std::cout <<"GAME :: But we are linking against SDL version: " 
	    << (int)linked.major <<"."<< (int)linked.minor <<"."<< (int)linked.patch << "\n";

  // Opening Inputh Handler:
  the_Input_handler::Instance().Initialise_joysticks();

  /*
  // Register all Game-objects:
  the_Factory_game_obj::Instance().Register_creator( fac::GAME_OBJ, new Creator_game_obj );
  the_Factory_game_obj::Instance().Register_creator( fac::GAME_OBJ_GRID, new Creator_game_obj_grid );
  the_Factory_game_obj::Instance().Register_creator( fac::GAME_OBJ_SHEET, new Creator_game_obj_sheet );
  the_Factory_game_obj::Instance().Register_creator( fac::GAME_OBJ_SHEET_BUTTON, new Creator_game_obj_button );
  the_Factory_game_obj::Instance().Register_creator( fac::GAME_OBJ_SHEET_ENEMY, new Creator_game_obj_enemy );
  the_Factory_game_obj::Instance().Register_creator( fac::GAME_OBJ_SHEET_PLAYER, new Creator_game_obj_player );

  // The Game State Machine:
  m_state_machine.Push_state( new State_main_menu );
  */



  // FOR TESTING:
  m_state_ptr = new State( "State1" );
  m_state_ptr->Create();



  return true;
}



void the_Game::on_Display_resize()
{
  //m_state_machine.on_Display_resize();
}



void the_Game::Handle_events()
{
  // Inputh Handler:
  the_Input_handler::Instance().Update();
}



void the_Game::Update()
{



  // The Game State Machine:
  //m_state_machine.Update();
  m_state_ptr->Update();



}



void the_Game::Render()
{
  SDL_RenderClear( m_renderer_ptr );



  // The Game State Machine:
  //m_state_machine.Render();
  m_state_ptr->Render();



  /*
  glm::vec2 display( the_World::Instance().Get_display_size());
  glm::vec2 mouse_pos = the_Input_handler::Instance().Get_mouse_position();
  glm::vec2 display_middle(( display.x / 2 ), ( display.y / 2 ));

  SDL_SetRenderDrawColor( the_Game::Instance().Get_renderer(), 50, 50, 255, 255 );
  SDL_RenderDrawLine( the_Game::Instance().Get_renderer(), 0, ( display.y / 2 ), display.x, ( display.y / 2 ));
  SDL_RenderDrawLine( the_Game::Instance().Get_renderer(), ( display.x / 2 ), 0, ( display.x / 2 ), display.y );
  SDL_SetRenderDrawColor( the_Game::Instance().Get_renderer(), 0, 0, 0, 255 );
  */

  SDL_RenderPresent( m_renderer_ptr );
}



void the_Game::Clean()
{
  // Closing the Texture Manager:
  the_Texture_manager_v2::Instance().Clean();

  // Closing Inputh Handler:
  the_Input_handler::Instance().Clean();

  // Closing Factory:
  //the_Factory_game_obj::Instance().Clean();



  // The Game State Machine:
  //m_state_machine.Clean();
  m_state_ptr->Clean();
  delete m_state_ptr;



  // Closing SDL:
  SDL_DestroyRenderer( m_renderer_ptr );
  m_renderer_ptr = nullptr;//NULL

  SDL_DestroyWindow( m_display_ptr );
  m_display_ptr = nullptr;//NULL

  SDL_Quit();
  std::cout << "GAME :: Clean() is Done.\n";
}
