
#ifndef GAME_OBJ_SHEET_ENEMY_H
#define GAME_OBJ_SHEET_ENEMY_H

#include "Init.h"
#include "Game_obj_sheet.h"
#include "Factory_game_obj.h"



struct Game_obj_enemy_parameters : public Game_obj_sheet_parameters
{
 Game_obj_enemy_parameters( Game_obj_sheet_parameters& _sheet_params, int _enemy_type ) : 
  Game_obj_sheet_parameters(_sheet_params), m_enemy_type(_enemy_type) {}

  int m_enemy_type;
};



// --- ENEMY ---
class Game_obj_sheet_enemy : public Game_obj_sheet
{
 public:
  Game_obj_sheet_enemy() {}
  virtual ~Game_obj_sheet_enemy() {}

  // --- Functions ---
  void Load( Game_obj_enemy_parameters& _enemy_params );
  virtual void Parse( xml::parser& _p );

  virtual void Update();
  virtual void Draw( Camera* _camera );
  virtual void Clean();

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



class Creator_game_obj_enemy : public Base_creator_game_obj
{
  virtual Base_game_obj* Create_game_object() const
  {
    return new Game_obj_sheet_enemy;
  }
};



#endif
