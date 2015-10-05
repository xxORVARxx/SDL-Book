
#include "Game.h"


Game::Game()
{
  m_running = true;
  m_display_ptr = NULL;
  m_renderer_ptr = NULL;

  m_color = 0;
  m_color_add = 2;
}
Game::~Game()
{
  Clear();
}



bool Game::Init( std::string s_title, int s_w, int s_h )
{
  // Initializing_SDL2:
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    std::cout << "!! Failed to initialize SDL : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_display_ptr = SDL_CreateWindow( s_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				    s_w, s_h, SDL_WINDOW_RESIZABLE );
  if ( m_display_ptr == NULL ) {
    std::cout << "!! Failed to create window : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_renderer_ptr = SDL_CreateRenderer( m_display_ptr, -1, SDL_RENDERER_ACCELERATED );
  if ( m_renderer_ptr == NULL ) {
    std::cout << "!! Failed to create renderer : " << SDL_GetError() << " !!\n";  
    return false;
  }


  // Loading Texture with the "Singleton Class":
  Texture_manager::Instance()->Load( m_renderer_ptr, "Alien", "assets/Alien_sprite_sheet.png" );

  // Make 'Game Object' and 'Player':
  m_go.Load( "Alien", 0, 0, ( 2096/8 ), ( 786/3 ));
  m_player.Load( "Alien", 200, 200, ( 2096/8 ), ( 786/3 ), SDL_FLIP_HORIZONTAL );


  return true;
}



void Game::Handle_events()
{
  SDL_Event event;
  while ( SDL_PollEvent( &event ))
    {
      switch (event.type) 
	{
	  // --- QUIT ---
	case SDL_QUIT : 
	  m_running = false;
	  break;
	}
    }
}



void Game::Update()
{
  // Updating the Game Objects:
  m_go.Update();
  m_player.Update();


  m_color += m_color_add;
  if (( m_color >= 150 )||( m_color <= 0  ))
    m_color_add *= -1;
}



void Game::Render()
{
  SDL_SetRenderDrawColor( m_renderer_ptr, m_color, 0, 0, 255 );
  SDL_RenderClear( m_renderer_ptr );

  // Rendering the Game Objects:
  m_go.Draw( m_renderer_ptr );
  m_player.Draw( m_renderer_ptr );


  SDL_RenderPresent( m_renderer_ptr );
}



void Game::Clear()
{
  SDL_DestroyRenderer( m_renderer_ptr );
  SDL_DestroyWindow( m_display_ptr );
  SDL_Quit();
}
