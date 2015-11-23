
#include "Objects.h"
#include "Input_handler.h"
#include "Game.h"
#include "Texture_manager.h"



// --- BUTTON ---
Button::Button( Object_load_parameters& _params, void (*f_Callback)()) : Object_default(_params),  mf_Callback(f_Callback)
{
  m_current_frame = 0;
  m_last_frame = 0;
  m_current_row = MOUSE_OUT;
  m_clicked = false;
}

void Button::Update()
{
  // Get Mouse Position/Coordinates:
  const glm::vec2 mouse_pos = the_Input_handler::Instance().Get_mouse_position();
  // Check whether the Mouse is over the Button or not:
  if( xx::Point_in_rect( mouse_pos, glm::vec4( m_position.x, m_position.y, (float)m_w, (float)m_h )))
    {
      if( m_clicked &&( ! the_Input_handler::Instance().Get_mouse_button( SDL_BUTTON_LEFT )))
	{
	  mf_Callback(); // Calling the function pointer.
	  m_clicked = false;
	}
      else if( the_Input_handler::Instance().Get_mouse_button( SDL_BUTTON_LEFT ))
	{
	  m_current_row = MOUSE_CLICKED;
	  m_clicked = true;
	}
      else
	{
	  m_current_row = MOUSE_OVER;
	  m_clicked = false;
	}
    }
  else
    {
      m_current_row = MOUSE_OUT;
      m_clicked = false;
    }
}



// --- Player ---
Player::Player( Object_load_parameters& _params ) : Object_default(_params) 
{
  // Seting keys:
  move_up_key =    SDL_SCANCODE_W ;
  move_down_key =  SDL_SCANCODE_S ;
  move_right_key = SDL_SCANCODE_D ;
  move_left_key =  SDL_SCANCODE_A ;
}

void Player::Update() 
{
  Hendle_input();

  m_frame_speed = 30;
  if( m_acceleration.y > 0 )  m_frame_speed = 45;
  if( m_acceleration.y < 0 )  m_frame_speed = 15;

  Object_default::Update();
}

void Player::Hendle_input()
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



// --- Enemy ---
void Enemy::Draw()
{
  the_Texture_manager::Instance().Drow( the_Game::Instance().Get_renderer(), m_texture_id, 
					(int)m_position.x, (int)m_position.y, m_w, m_h, m_texture_flip );
}
