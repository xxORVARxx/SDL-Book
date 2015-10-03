 
#include<SDL2/SDL.h>
#include<iostream>
#include<string>

bool g_running = false;

SDL_Window* g_window_ptr = NULL;
SDL_Renderer* g_renderer_ptr = NULL;

bool Init( std::string s_title, SDL_Rect s_xywh, int s_flags  )
{
  // Initializing_SDL2:
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    std::cout << "!! Failed to initialize SDL : " << SDL_GetError() << " !!\n";  
    return false;
  }

  g_window_ptr = SDL_CreateWindow( s_title.c_str(), s_xywh.x, s_xywh.y, s_xywh.w, s_xywh.h, s_flags );
  if ( g_window_ptr == NULL ) {
    std::cout << "!! Failed to create window : " << SDL_GetError() << " !!\n";  
    return false;
  }

  g_renderer_ptr = SDL_CreateRenderer( g_window_ptr, -1, SDL_RENDERER_ACCELERATED );
  if ( g_renderer_ptr == NULL ) {
    std::cout << "!! Failed to create renderer : " << SDL_GetError() << " !!\n";  
    return false;
  }
  return true;
}

void Render()
{
  SDL_SetRenderDrawColor( g_renderer_ptr, 0, 0, 0, 255 );
  SDL_RenderClear( g_renderer_ptr );
  SDL_RenderPresent( g_renderer_ptr );
}

int main ( int argc, char* args[] )
{
  if ( Init( "SDL", SDL_Rect{ SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480 }, 0 ))
    g_running = true;
  else
    return -1;

  while( g_running )
    {
      Render();
      SDL_Delay( 16 );
    }


  SDL_Quit();
  return 1;
}
