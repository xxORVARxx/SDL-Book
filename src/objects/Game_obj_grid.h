
#ifndef GAME_OBJ_GRID_H
#define GAME_OBJ_GRID_H

#include "Init.h"
#include "A_Game_obj_interface.h"



struct Game_obj_grid_parameters : public Base_game_obj_parameters
{
 Game_obj_grid_parameters( SDL_Color _color = { 20, 20, 20, 255 }, int _grid_size = 50 ) : 
  color(_color), grid_size(_grid_size) {}

  SDL_Color color;// <- Default = 20, 20, 20, 255
  int grid_size;// <- Default = 50
};



class Game_obj_grid : public Base_game_obj
{
 public:
  Game_obj_grid() {}
  virtual ~Game_obj_grid() {}

  // --- Functions ---
  void Load( Game_obj_grid_parameters& _grid_params );
  virtual void Parse( xml::parser& _p );

  virtual void Update() {}
  virtual void Draw( Camera* _camera );
  virtual void Clean();

  // --- Variables ---
 protected:
  SDL_Color m_color;
  int m_grid_size;
};



class Creator_game_obj_grid : public Base_creator_game_obj
{
  virtual Base_game_obj* Create_game_object() const
  {
    return new Game_obj_grid;
  }
};



#endif
