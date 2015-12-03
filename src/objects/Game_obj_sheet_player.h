
#ifndef GAME_OBJ_SHEET_PLAYER_H
#define GAME_OBJ_SHEET_PLAYER_H

#include "Init.h"
#include "Game_obj_sheet.h"



// --- PLAYER ---
class Game_obj_sheet_player : public Game_obj_sheet
{
 public:
  Game_obj_sheet_player( Game_obj_parameters& _obj_params, Game_obj_sheet_parameters& _sheet_params );
  virtual ~Game_obj_sheet_player() {}

  virtual void Update();
  virtual void Draw();
  virtual void Clean() { std::cout << "PLAYER :: Clean() is Done,  &  "; Game_obj_sheet::Clean(); }

 private:
  void Hendle_input();
  void Other_forces();

  // --- Variables ---
  Uint8 move_up_key, move_down_key, move_right_key, move_left_key;
  SDL_RendererFlip m_texture_flip;
  double m_delta_time;
  glm::vec2 m_mouse_pos;

  glm::vec2 m_helicopter_middle_pos;
  float m_helicopter_pitch_degrees;
  glm::vec2 m_acceleration_steering;
  glm::vec2 m_velocity;
};



#endif
