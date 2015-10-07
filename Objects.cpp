
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
  if( the_Input_handler::Instance()->Key_down() )
    {
      const Uint8* state = SDL_GetKeyboardState ( NULL ) ;
      if( state[ move_right_key ] )
	m_acceleration.x = 0.1;
      else if( state[ move_left_key ] )
	m_acceleration.x = -0.1;

      if( state[ move_down_key ] )
	m_acceleration.y = 0.1;
      else if( state[ move_up_key ] )
	m_acceleration.y = -0.1;
    }

  // Mouse:
  if( the_Input_handler::Instance()->Mouse_button_down() )
    {
      if( the_Input_handler::Instance()->Get_mouse_button( SDL_BUTTON_RIGHT ))
	m_acceleration.x = 0.1;
      else if( the_Input_handler::Instance()->Get_mouse_button( SDL_BUTTON_LEFT ))
	m_acceleration.x = -0.1;
    }

  // Joystick:
  if( the_Input_handler::Instance()->Joystick_initialised() )
    {

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
  // Mouse:
  glm::vec2 mouse_pos = the_Input_handler::Instance()->Mouse_position();
  m_velocity.x = ( mouse_pos.x - ( m_position.x + ( m_w / 2 ))) / 50.0f ;
  m_velocity.y = ( mouse_pos.y - ( m_position.y + ( m_h / 2 ))) / 50.0f ;
}
