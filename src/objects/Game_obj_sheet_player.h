
#ifndef GAME_OBJ_SHEET_PLAYER_H
#define GAME_OBJ_SHEET_PLAYER_H

#include "Init.h"
#include "Game_obj_sheet.h"
#include "Factory_game_obj.h"



struct Game_obj_player_parameters : public Game_obj_sheet_parameters
{
 Game_obj_player_parameters( Game_obj_sheet_parameters& _sheet_params ) : 
  Game_obj_sheet_parameters(_sheet_params) {}
};



// --- PLAYER ---
class Game_obj_sheet_player : public Game_obj_sheet
{
 public:
  Game_obj_sheet_player() {}
  virtual ~Game_obj_sheet_player() {}

  // --- Functions ---
  void Load( Game_obj_player_parameters& _player_params );
  virtual void Parse( xml::parser& _p );

  virtual void Update();
  virtual void Draw( Camera* _camera );
  virtual void Clean();

 private:
  void Update_camera();
  void Hendle_input();
  void Other_forces();

  // --- Variables ---
  Uint8 move_up_key, move_down_key, move_right_key, move_left_key;
  bool move_up_key_pressed, move_down_key_pressed;

  Camera* m_camera;
  SDL_RendererFlip m_texture_flip;
  float m_delta_time;
  glm::vec2 m_mouse_pos;

  glm::vec2 m_helicopter_middle_pos;
  float m_helicopter_pitch_degrees;
  glm::vec2 m_acceleration_steering;
  glm::vec2 m_velocity;
};



class Creator_game_obj_player : public Base_creator_game_obj
{
  virtual Base_game_obj* Create_game_object() const
  {
    return new Game_obj_sheet_player;
  }
};



#endif
