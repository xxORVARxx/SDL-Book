
#include "Game.h"
#include "Input_handler.h"



// --- Static Variables ---
Game* Game::sm_instance_ptr = NULL;



// --- Constructors ---
Game::Game()
{
  m_display_ptr = NULL;
  m_renderer_ptr = NULL;
}



// --- Functions ---
bool Game::Init( std::string s_title, int s_w, int s_h )
{
  // Initializing_SDL2:
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    std::cout << "GAME :: !! Failed to initialize SDL : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_display_ptr = SDL_CreateWindow( s_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				    s_w, s_h, SDL_WINDOW_RESIZABLE );
  if ( m_display_ptr == NULL ) {
    std::cout << "GAME :: !! Failed to create window : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_renderer_ptr = SDL_CreateRenderer( m_display_ptr, -1, SDL_RENDERER_ACCELERATED );
  if ( m_renderer_ptr == NULL ) {
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
  the_Input_handler::Instance()->Initialise_joysticks();


  // The Game State Machine:
  m_state_machine.Change_state( new Menu_state() );


  return true;
}



void Game::Handle_events()
{
  // Inputh Handler:
  the_Input_handler::Instance()->Update();


  // Change Game State between 'Menu_state' and 'Play_state':
  if( the_Input_handler::Instance()->is_Key_down() )
    {
      const Uint8* keys_state = the_Input_handler::Instance()->Get_keys_state();
      // Press 'P' for Play_state:
      if ( keys_state[ SDL_SCANCODE_P ] )
	m_state_machine.Change_state( new Play_state() );
      // Press 'M' for Menu_state:
      if ( keys_state[ SDL_SCANCODE_M ] )
	m_state_machine.Change_state( new Menu_state() );
    }
}



void Game::Update()
{
  // The Game State Machine:
  m_state_machine.Update();
}



void Game::Render()
{
  SDL_RenderClear( m_renderer_ptr );

  // The Game State Machine:
  m_state_machine.Render();

  SDL_RenderPresent( m_renderer_ptr );
}



void Game::Clean()
{
  // Closing Inputh Handler:
  the_Input_handler::Instance()->Clean();

  // The Game State Machine:
  m_state_machine.Clean();

  // Closing SDL:
  SDL_DestroyRenderer( m_renderer_ptr );
  SDL_DestroyWindow( m_display_ptr );
  SDL_Quit();
  std::cout << "GAME :: Clean() is Done.\n";
}
