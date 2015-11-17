
#include "Game.h"
#include "Input_handler.h"
#include "Texture_manager.h"



// --- Constructors ---
the_Game::the_Game()
{
  m_display_ptr = nullptr;//NULL
  m_renderer_ptr = nullptr;//NULL
}



// --- Functions ---
bool the_Game::Init( std::string _title, int _w, int _h )
{
  m_width = _w;
  m_height = _h;

  // Initializing_SDL2:
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    std::cout << "GAME :: !! Failed to initialize SDL : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_display_ptr = SDL_CreateWindow( _title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				    m_width, m_height, SDL_WINDOW_RESIZABLE );
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


  // The Game State Machine:
  m_state_machine.Push_state( new Menu_state );


  return true;
}



void the_Game::Handle_events()
{
  // Inputh Handler:
  the_Input_handler::Instance().Update();
}



void the_Game::Update()
{
  // The Game State Machine:
  m_state_machine.Update();
}



void the_Game::Render()
{
  SDL_RenderClear( m_renderer_ptr );

  // The Game State Machine:
  m_state_machine.Render();

  SDL_RenderPresent( m_renderer_ptr );
}



void the_Game::Clean()
{
  // Closing the Texture Manager:
  the_Texture_manager::Instance().Clean();

  // Closing Inputh Handler:
  the_Input_handler::Instance().Clean();

  // The Game State Machine:
  m_state_machine.Clean();

  // Closing SDL:
  SDL_DestroyRenderer( m_renderer_ptr );
  m_renderer_ptr = nullptr;//NULL

  SDL_DestroyWindow( m_display_ptr );
  m_display_ptr = nullptr;//NULL

  SDL_Quit();
  std::cout << "GAME :: Clean() is Done.\n";
}


/*

void Push_P() {
  the_Game::Instance().Get_state_machine()->Push_state( new Play_state );
}
void Push_M() {
  the_Game::Instance().Get_state_machine()->Push_state( new Menu_state );
}
void Change_M_to_P() {
  the_Game::Instance().Get_state_machine()->Change_state( new Play_state );
}
void Change_P_to_M() {
  the_Game::Instance().Get_state_machine()->Change_state( new Menu_state );
}
void Pop() {
  the_Game::Instance().Get_state_machine()->Pop_state();
}

*/
