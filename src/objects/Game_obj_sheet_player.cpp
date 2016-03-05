
#include "Game_obj_sheet_player.h"
#include "Input_handler.h"
#include "Texture_manager_v2.h"

#include "Game_world.h"
#include "Game.h"
#include "XML_parser_states.h"



// --- PLAYER ---
void Game_obj_sheet_player::Load( Game_obj_player_parameters& _player_params )
{
  Game_obj_sheet::Load( _player_params );

  m_camera = nullptr;
  // Seting keys:
  move_up_key =    SDL_SCANCODE_W ;
  move_down_key =  SDL_SCANCODE_S ;
  move_right_key = SDL_SCANCODE_D ;
  move_left_key =  SDL_SCANCODE_A ;
  move_up_key_pressed = false;
  move_down_key_pressed = false;

  m_texture_flip = SDL_FLIP_NONE;
}

void Game_obj_sheet_player::Parse( xml::parser& _p )
{
  std::cout <<"Game-Object-Sheet-Player.  ";
  Game_obj_sheet::Parse( _p );

  _p.next_expect( xml::parser::start_element, "game_obj_player_parameters", xml::content::complex );
  _p.next_expect( xml::parser::end_element );//game_obj_player_parameters

  m_camera = nullptr;
  // Seting keys:
  move_up_key =    SDL_SCANCODE_W ;
  move_down_key =  SDL_SCANCODE_S ;
  move_right_key = SDL_SCANCODE_D ;
  move_left_key =  SDL_SCANCODE_A ;
  move_up_key_pressed = false;
  move_down_key_pressed = false;

  m_texture_flip = SDL_FLIP_NONE;
}



void Game_obj_sheet_player::Update() 
{
  m_delta_time = (float)the_World::Instance().Get_delta_time();
  m_helicopter_middle_pos.x = ( m_position.x + ( m_size.x / 2.0f ));
  m_helicopter_middle_pos.y = ( m_position.y + ( m_size.y / 4.0f ));

  if( m_camera )
    this->Update_camera();
  this->Hendle_input();
  this->Other_forces();
  m_position += (( m_velocity + m_velocity ) * m_delta_time );

  if( move_up_key_pressed )
    m_frame_time = 11.11f;
  else if( move_down_key_pressed )
    m_frame_time = 50.0f;
  else
    m_frame_time = 33.33f;
  Game_obj_sheet::Update();
}



void Game_obj_sheet_player::Draw( Camera* _camera )
{
  m_camera = _camera;

  if( ! (( m_helicopter_pitch_degrees > 10.0f )&&( m_helicopter_pitch_degrees < 350.0f )))
    {
      if(( m_velocity.x > 0.0f )&&( m_mouse_pos.x > m_helicopter_middle_pos.x ))  
	m_texture_flip = SDL_FLIP_NONE;
      if(( m_velocity.x < 0.0f )&&( m_mouse_pos.x < m_helicopter_middle_pos.x ))  
	m_texture_flip = SDL_FLIP_HORIZONTAL;
    }

  glm::vec2 display_position = ( m_position - m_camera->Get_position());
  the_Texture_manager_v2::Instance().Draw_frame_rot( the_Game::Instance().Get_renderer(), m_texture_id, display_position, 
						     m_size, m_frame_width, m_frame_height, m_frame_number, m_row_number, 
						     m_helicopter_pitch_degrees, 2.0d, 4.0d, m_texture_flip );
}



void Game_obj_sheet_player::Clean()
{
  std::cout << "Game_obj_player.Clean() is Done  &  ";
  Game_obj_sheet::Clean();
}



void Game_obj_sheet_player::Update_camera()
{
  m_camera->Set_position( m_helicopter_middle_pos - ( the_World::Instance().Get_display_size() / 2.0f ));
  m_mouse_pos = ( m_camera->Get_position() + the_Input_handler::Instance().Get_mouse_position());
}



void Game_obj_sheet_player::Hendle_input()
{
  // THE STEERING CONTROL:
  move_up_key_pressed = false;
  move_down_key_pressed = false;
  m_acceleration_steering.x = 0.0f;
  m_acceleration_steering.y = 0.0f;
  float steering_speed = ( 50.0f * m_delta_time );

  // Mouse:
  glm::vec2 helicopter_pitch_point;
  if( m_texture_flip == SDL_FLIP_NONE )
    {
      helicopter_pitch_point = ( m_mouse_pos - m_helicopter_middle_pos );
      if( m_mouse_pos.x < m_helicopter_middle_pos.x )
	helicopter_pitch_point.x = -helicopter_pitch_point.x;
    }
  else
    {
      helicopter_pitch_point = ( m_helicopter_middle_pos - m_mouse_pos );
      if( m_helicopter_middle_pos.x < m_mouse_pos.x )
	helicopter_pitch_point.x = -helicopter_pitch_point.x;
    }
  m_helicopter_pitch_degrees = xx::Vec_to_degrees( helicopter_pitch_point );

  // Keyboard:
  const Uint8* keys_state = the_Input_handler::Instance().Get_keys_state();
  if( keys_state[ move_left_key ] )// Left:
    m_acceleration_steering.x += xx::Degrees_to_vec( m_helicopter_pitch_degrees + 180.0f ).x;
  if( keys_state[ move_right_key ] )// Right:
    m_acceleration_steering.x += xx::Degrees_to_vec( m_helicopter_pitch_degrees ).x;
  if( keys_state[ move_up_key ] )// Up:
    {
      move_up_key_pressed = true;
      m_acceleration_steering += xx::Degrees_to_vec( m_helicopter_pitch_degrees + 270.0f );
      steering_speed *= 2.0f;
    }
  else if( keys_state[ move_down_key ] )// Down:
    {
      move_down_key_pressed = true;
      m_acceleration_steering.y += 1.0f;
    }

  if( m_acceleration_steering.x || m_acceleration_steering.y  )
    {
      m_acceleration_steering = glm::normalize( m_acceleration_steering );
      m_acceleration_steering *= steering_speed;

      m_velocity += m_acceleration_steering;
    }
}



void Game_obj_sheet_player::Other_forces()
{
  // THE GRAVITY:
  float m_gravity_forces = ( 9.8f * 2.0f * m_delta_time );
  glm::vec2 acceleration_gravity( 0.0f, m_gravity_forces );
  m_velocity -= ( 0.05f * m_velocity * m_delta_time  );// 5% Air-Resistans.
  m_velocity += ( acceleration_gravity * 1.5f );

  // THE MAIN ROTOR BLADES:
  float m_blades_torque = m_gravity_forces;
  glm::vec2 acceleration_blades= xx::Degrees_to_vec( m_helicopter_pitch_degrees + 270.0f );
  acceleration_blades *= m_gravity_forces;
  m_velocity += acceleration_blades;
}
