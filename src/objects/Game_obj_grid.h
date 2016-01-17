
#ifndef GAME_OBJ_GRID_H
#define GAME_OBJ_GRID_H

#include "Init.h"
#include "A_Game_obj_interface.h"
#include "Factory_game_obj.h"



struct Game_obj_grid_parameters : public Base_game_obj_parameters
{
 Game_obj_grid_parameters( SDL_Color _color = { 20, 20, 20, 255 }, int _grid_size = 50 ) : 
  m_color(_color), m_grid_size(_grid_size) {}
  SDL_Color m_color;
  int m_grid_size;
};



class Game_obj_grid : public Game_obj_default
{
 public:
  Game_obj_grid() {}
  virtual ~Game_obj_grid() {}

  // --- Functions ---
  virtual void Load( Game_obj_grid_parameters& _grid_params );

  virtual void Update() {}
  virtual void Draw( Camera* _camera );
  virtual void Clean();

  // --- Variables ---
 protected:
  SDL_Color m_color;
  int m_grid_size;
};



class Grid_creator : public Base_creator
{
  Game_obj_default* Create_game_object() const
  {
    return new Game_obj_grid;
  }
};



#endif
