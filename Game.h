
#ifndef GAME_H
#define GAME_H

#include "Init.h"
#include "Game_object.h"



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

  int m_color;
  int m_color_add;

  // Game Objects:
  std::vector< Game_object* > m_obj_vec;
};



#endif
