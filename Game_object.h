
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Init.h"



class Game_object
{
 public:
  void Load( std::string s_id, int s_x, int s_y, int s_w, int s_h, SDL_RendererFlip s_flip = SDL_FLIP_NONE );
  void Draw( SDL_Renderer* s_renderer_ptr );
  void Update();
  void Clean();

 protected:
  std::string m_texture_id;
  SDL_RendererFlip m_flip;

  int m_current_frame;
  int m_last_frame;
  int m_current_row;

  int m_x;
  int m_y;
  int m_w;
  int m_h;
};



class Player : public Game_object
{
 public:
  void Load( std::string s_id, int s_x, int s_y, int s_w, int s_h, SDL_RendererFlip s_flip = SDL_FLIP_NONE );
  void Draw( SDL_Renderer* s_renderer_ptr );
  void Update();
  void Clean();
};



#endif
