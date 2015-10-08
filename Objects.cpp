
#include "Objects_blueprint.h"
#include "Objects.h"
#include "Input_handler.h"



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
void Enemy::Update() 
{
  Object_default::Update();
  Hendle_input();

  m_current_frame = (( SDL_GetTicks() / 150 ) % 8 );
  if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
    m_current_row = (( m_current_row + 1 ) % 3 );
  m_last_frame = m_current_frame;
}



void Enemy::Hendle_input()
{

}
