
#include "Game_obj_sheet_enemy.h"
#include "Texture_manager.h"

#include "Game_world.h"
#include "Game.h"
#include "XML_parser_states.h"



// --- ENEMY ----
void Game_obj_sheet_enemy::Load( Game_obj_enemy_parameters& _enemy_params )
{
  Game_obj_sheet::Load( _enemy_params );
  m_enemy_type = _enemy_params.m_enemy_type;

  m_frame_counter = m_enemy_type;
  m_direction_degrees = xx::Get_random.Discrete_num( 1, 360 );

  if( xx::Get_random.Discrete_num( 0, 1 ))
    turning_speed = xx::Get_random.Real_num( 2.0f, 20.0f );
  else
    turning_speed = xx::Get_random.Real_num( -2.0f, -20.0f );
  fly_speed = xx::Get_random.Real_num( 10000.0f, 500.0f );
}

void Game_obj_sheet_enemy::Parse( xml::parser& _p )
{
  std::cout <<"Game-Object-Sheet-Enemy.  ";
  Game_obj_sheet::Parse( _p );

  _p.next_expect( xml::parser::start_element, "game_obj_enemy_parameters", xml::content::complex );
  m_enemy_type = Parse_type< int >( _p, "enemy_type" );
  _p.next_expect( xml::parser::end_element );//game_obj_enemy_parameters

  m_frame_counter = m_enemy_type;
  m_direction_degrees = xx::Get_random.Discrete_num( 1, 360 );

  if( xx::Get_random.Discrete_num( 0, 1 ))
    turning_speed = xx::Get_random.Real_num( 2.0f, 20.0f );
  else
    turning_speed = xx::Get_random.Real_num( -2.0f, -20.0f );
  fly_speed = xx::Get_random.Real_num( 10000.0f, 500.0f );
}



void Game_obj_sheet_enemy::Update() 
{
  m_delta_time = (float)the_World::Instance().Get_delta_time();
  m_velocity.x = 0.0f;
  m_velocity.y = 0.0f;

  this->Movement();
  this->Update_frame();

  m_position += ( m_velocity * m_delta_time );
}



void Game_obj_sheet_enemy::Draw( Camera* _camera )
{
  xx::Clamp_degrees( m_direction_degrees );

  glm::vec2 display_position = m_position;
  if( _camera != nullptr )
    display_position -= _camera->Get_position();

  the_Texture_manager::Instance().Draw_frame_rot( the_Game::Instance().Get_renderer(), m_texture_id, display_position, 
						  m_size, m_frame_width, m_frame_height, m_frame_number, m_row_number, 
						  m_direction_degrees, 2.0d, 2.0d );
}



void Game_obj_sheet_enemy::Clean()
{
  std::cout << "Game_obj_enemy.Clean() is Done  &  ";
  Game_obj_sheet::Clean();
}



void Game_obj_sheet_enemy::Update_frame()
{
  int m_number_of_enemy_types = 17;
  // If current frame is too old:
  if( (float)SDL_GetTicks() > m_frame_time_out )
    {
      m_frame_counter += m_number_of_enemy_types;
      m_frame_time_out = SDL_GetTicks() + m_frame_time;
    }
  // If the current frame is the last frame:
  if( m_frame_counter > m_total_num_of_frames )
    m_frame_counter = m_enemy_type;

  // Finding the frame: (the first frame/row is number '1' not '0')
  if( m_frame_counter % m_frames_in_a_row )
    m_row_number = (( m_frame_counter / m_frames_in_a_row ) + 1 );
  else
    m_row_number = ( m_frame_counter / m_frames_in_a_row );
  m_frame_number = (( m_frame_counter - (( m_row_number - 1 ) * m_frames_in_a_row )));
}



void Game_obj_sheet_enemy::Movement()
{
  m_direction_degrees += ( turning_speed * m_delta_time );
  m_velocity += ( xx::Degrees_to_vec( m_direction_degrees ) * fly_speed * m_delta_time );
}
