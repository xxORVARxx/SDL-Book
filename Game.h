
#ifndef GAME_H
#define GAME_H

#include<SDL2/SDL.h>
#include<iostream>
#include<string>



class Game
{
 public:
  Game();
  ~Game();

  bool Init( std::string title, int w, int h );

  void Handle_events();
  void Update();
  void Render();

  void Clear();

  //private:
  bool m_running;

  SDL_Window* m_display_ptr;
  SDL_Renderer* m_renderer_ptr;
};


#endif
