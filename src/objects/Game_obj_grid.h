
#ifndef GAME_OBJ_GRID_H
#define GAME_OBJ_GRID_H

#include "Init.h"
#include "A_Game_obj_interface.h"



class Game_obj_grid : public Game_obj_default
{
 public:
  Game_obj_grid( SDL_Color _color = { 20, 20, 20, 255 }, int _size = 50 );
  virtual ~Game_obj_grid() {}

  // --- Functions ---
  virtual void Update() {}
  virtual void Draw( Camera* _camera );
  virtual void Clean();

  // --- Variables ---
 protected:
  SDL_Color m_color;
  int m_grid_size;
};



#endif
