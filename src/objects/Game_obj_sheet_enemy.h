
#ifndef GAME_OBJ_SHEET_ENEMY_H
#define GAME_OBJ_SHEET_ENEMY_H

#include "Init.h"
#include "Game_obj_sheet.h"



// --- ENEMY ---
class Game_obj_sheet_enemy : public Game_obj_sheet
{
 public:
  Game_obj_sheet_enemy( Game_obj_parameters& _obj_params, Game_obj_sheet_parameters& _sheet_params, int _enemy_type );
  virtual ~Game_obj_sheet_enemy() {}

  virtual void Update();
  virtual void Draw( Camera* _camera );
  virtual void Clean() { std::cout << "ENEMY :: Clean() is Done,  &  "; Game_obj_sheet::Clean(); }

 private:
  void Update_frame();
  void Movement();

  // --- Variables ---
  int m_enemy_type;
  float m_delta_time;
  glm::vec2 m_velocity;
  float m_direction_degrees;

  float turning_speed;
  float fly_speed;
};



#endif
