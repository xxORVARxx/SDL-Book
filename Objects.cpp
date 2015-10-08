
#include "Objects.h"
#include "Input_handler.h"
#include "Game.h"
#include "Texture_manager.h"



// --- BUTTON ---
Button::Button( Object_load_parameters* params_ptr ) : Object_default(params_ptr)
{
  m_current_frame = 0;
  m_last_frame = 0;
  m_current_row = MOUSE_OUT;
}

void Button::Update()
{
  // Get Mouse Position/Coordinates:
  const glm::vec2 mouse_pos = the_Input_handler::Instance()->Get_mouse_position();
  // Check whether the Mouse is over the Button or not:
  if( xx::Point_in_rect( mouse_pos, glm::vec4( m_position.x, m_position.y, (float)m_w, (float)m_h )))
    {
      m_current_row = MOUSE_OVER;
      if( the_Input_handler::Instance()->Get_mouse_button( SDL_BUTTON_LEFT ))
	m_current_row = MOUSE_CLICKED;
    }
  else
    m_current_row = MOUSE_OUT;
}



// --- Player ---
void Player::Update() 
{
  Hendle_input();
  Object_default::Update();

  m_current_frame = (( SDL_GetTicks() / 50 ) % 8 );
  if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
    m_current_row = (( m_current_row + 1 ) % 3 );
  m_last_frame = m_current_frame;
}

void Player::Hendle_input()
{
  m_acceleration.x = 0;
  m_acceleration.y = 0;

  // Keyboard:
  if( the_Input_handler::Instance()->is_Key_down() )
    {
      const Uint8* keys_state = the_Input_handler::Instance()->Get_keys_state();

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
  the_Texture_manager::Instance()->Drow( the_Game::Instance()->Get_renderer(), m_texture_id, 
					 (int)m_position.x, (int)m_position.y, m_w, m_h, m_texture_flip );
}
