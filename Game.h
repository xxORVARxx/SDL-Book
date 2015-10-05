
#ifndef GAME_H
#define GAME_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<string>

#include"Texture_manager.h"



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

  int m_current_frame;
  int m_last_frame;
  int m_current_row;

  int m_color;
  int m_color_add;
};



#endif
