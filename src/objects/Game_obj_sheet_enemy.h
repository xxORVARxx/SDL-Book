
#ifndef GAME_OBJ_SHEET_ENEMY_H
#define GAME_OBJ_SHEET_ENEMY_H

#include "Init.h"
#include "Game_obj_sheet.h"



// --- ENEMY ---
class Game_obj_sheet_enemy : public Game_obj_sheet
{
 public:
 Game_obj_sheet_enemy( Game_obj_parameters& _obj_params, Game_obj_sheet_parameters& _sheet_params ) : 
  Game_obj_sheet(_obj_params, _sheet_params) {}
  virtual ~Game_obj_sheet_enemy() {}

  virtual void Update();
  virtual void Draw() { Game_obj_sheet::Draw(); }
  virtual void Clean() { std::cout << "ENEMY :: Clean() is Done,  &  "; Game_obj_sheet::Clean(); }
};



#endif
