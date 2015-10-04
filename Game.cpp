
#include"Game.h"


Game::Game()
{
  m_running = true;
  m_display_ptr = NULL;
  m_renderer_ptr = NULL;
  m_texture_ptr = NULL;
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


  SDL_Surface* temp_surface = NULL;
  temp_surface = SDL_LoadBMP( "assets/animate_cat.bmp" );
  if ( temp_surface == NULL ) {
    std::cout << "!! Failed to load image : " << SDL_GetError() << " !!\n";  
    return false;
  }
  m_texture_ptr = SDL_CreateTextureFromSurface( m_renderer_ptr, temp_surface );
  if ( m_texture_ptr == NULL ) {
    std::cout << "!! Failed to load textur : " << SDL_GetError() << " !!\n";  
    return false;
  }
  SDL_FreeSurface( temp_surface );


  SDL_QueryTexture( m_texture_ptr, NULL, NULL, &m_sor_rec.w, &m_sor_rec.h );

  m_sor_rec.x = 0;
  m_sor_rec.y = 0;
  m_sor_rec.w = 165;
  m_sor_rec.h;


  m_des_rec.x = 0;
  m_des_rec.y = 0;
  m_des_rec.w = m_sor_rec.w;
  m_des_rec.h = m_sor_rec.h;

  std::cout << m_des_rec.w << "  " << m_des_rec.w << "\n";


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
  m_sor_rec.x = ( 165 * (int)((SDL_GetTicks() / 150 ) % 6 ));
  m_des_rec.x = (int)((SDL_GetTicks() / 5 ) % ( 480 + 165 + 165 )) - 165;
}



void Game::Render()
{
  SDL_SetRenderDrawColor( m_renderer_ptr, 0, 0, 0, 255 );
  SDL_RenderClear( m_renderer_ptr );

  SDL_RenderCopy( m_renderer_ptr, m_texture_ptr, &m_sor_rec, &m_des_rec );

  SDL_RenderPresent( m_renderer_ptr );
}



void Game::Clear()
{
  SDL_DestroyRenderer( m_renderer_ptr );
  SDL_DestroyWindow( m_display_ptr );
  SDL_Quit();
}
