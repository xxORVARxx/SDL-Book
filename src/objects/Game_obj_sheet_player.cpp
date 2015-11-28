
#include "Game_obj_sheet_player.h"
#include "Texture_manager.h"
#include "Game.h"
#include "Input_handler.h"



// --- Player ---
Game_obj_sheet_player::Game_obj_sheet_player( Game_obj_parameters& _obj_params, Game_obj_sheet_parameters& _sheet_params ) : 
  Game_obj_sheet(_obj_params, _sheet_params) 
{
  // Seting keys:
  move_up_key =    SDL_SCANCODE_W ;
  move_down_key =  SDL_SCANCODE_S ;
  move_right_key = SDL_SCANCODE_D ;
  move_left_key =  SDL_SCANCODE_A ;
}



void Game_obj_sheet_player::Update() 
{
  Hendle_input();

  m_velocity += m_acceleration;
  m_position += m_velocity;

  m_frame_speed = 33.33;
  if( m_acceleration.y > 0 )  m_frame_speed = 50;
  if( m_acceleration.y < 0 )  m_frame_speed = 16.67;

  Game_obj_sheet::Update();
}

void Game_obj_sheet_player::Draw()
{
  if( m_velocity.x > 0 )  m_texture_flip = SDL_FLIP_NONE;
  if( m_velocity.x < 0 )  m_texture_flip = SDL_FLIP_HORIZONTAL;
  the_Texture_manager::Instance().Draw_frame( the_Game::Instance().Get_renderer(), m_texture_id, m_position, m_size,
					      m_frame_width, m_frame_height, m_frame_number, m_row_number, m_texture_flip );
}



void Game_obj_sheet_player::Hendle_input()
{
  m_acceleration.x = 0;
  m_acceleration.y = 0;

  // Keyboard:
  if( the_Input_handler::Instance().is_Key_down() )
    {
      const Uint8* keys_state = the_Input_handler::Instance().Get_keys_state();

      if( keys_state[ move_right_key ] )
	m_acceleration.x = 0.1;
      else if( keys_state[ move_left_key ] )
	m_acceleration.x = -0.1;

      if( keys_state[ move_down_key ] )
	m_acceleration.y = 0.1;
      else if( keys_state[ move_up_key ] )
	m_acceleration.y = -0.1;
    }
}
