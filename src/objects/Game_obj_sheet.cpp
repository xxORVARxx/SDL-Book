
#include "Game_obj_sheet.h"
#include "Texture_manager.h"

#include "Game.h"



// --- Sprite-Sheet Game object ---
Game_obj_sheet::Game_obj_sheet( Game_obj_parameters& _obj_params, Game_obj_sheet_parameters& _sheet_params ) : 
  Game_obj( _obj_params, true )
{
  m_total_num_of_frames = _sheet_params.total_num_of_frames;
  m_frames_in_a_row = _sheet_params.frames_in_a_row;
  m_frame_speed = _sheet_params.frame_speed;

  m_frame_counter = 0;
  m_frame_time = 0;
  m_frame_number = 1;
  m_row_number = 1;
  // Calculate the frame size:
  m_frame_width = ( (int)m_image_size.x / m_frames_in_a_row );
  if( m_total_num_of_frames % m_frames_in_a_row )
    m_frame_height = ( (int)m_image_size.y / (( m_total_num_of_frames / m_frames_in_a_row ) + 1 ));
  else
    m_frame_height = ( (int)m_image_size.y / ( m_total_num_of_frames / m_frames_in_a_row ));

  // If there is no 'size' requested ('size' is 0), then the 'frame_size' is used:
  if( m_size.x == 0 )  m_size.x = m_frame_width;
  if( m_size.y == 0 )  m_size.y = m_frame_height;
  m_size *= m_scale;
}



void Game_obj_sheet::Update()
{
  // If current frame is too old:
  if( (float)SDL_GetTicks() > m_frame_time )
    {
      m_frame_counter++;
      m_frame_time = SDL_GetTicks() + m_frame_speed;
    }
  // If the current frame is the last frame:
  if( m_frame_counter > m_total_num_of_frames )
    m_frame_counter = 1;

  // Finding the frame: (the first frame/row is number '1' not '0')
  if( m_frame_counter % m_frames_in_a_row )
    m_row_number = (( m_frame_counter / m_frames_in_a_row ) + 1 );
  else
    m_row_number = ( m_frame_counter / m_frames_in_a_row );
  m_frame_number = (( m_frame_counter - (( m_row_number - 1 ) * m_frames_in_a_row )));
}



void Game_obj_sheet::Draw( Camera* _camera )
{
  glm::vec2 display_position = m_position;
  if( _camera != nullptr )
    display_position -= _camera->Get_position();

  the_Texture_manager::Instance().Draw_frame( the_Game::Instance().Get_renderer(), m_texture_id, display_position, 
					      m_size, m_frame_width, m_frame_height, m_frame_number, m_row_number );
}



void Game_obj_sheet::Clean()
{
  std::cout << "Game_obj_sheet.Clean() is Done,  &  ";
  Game_obj::Clean();
}
