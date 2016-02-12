
#include "Game_obj_sheet.h"
#include "Texture_manager.h"

#include "Game.h"
#include "XML_parser_states.h"



// --- Sprite-Sheet Game Object ---
void Game_obj_sheet::Load( Game_obj_sheet_parameters& _sheet_params )
{
  m_texture_id = _sheet_params.texture_id;
  m_image_size = _sheet_params.image_size;
  m_position = _sheet_params.position;
  m_scale = _sheet_params.scale;
  m_size = _sheet_params.size;

  m_total_num_of_frames = _sheet_params.total_num_of_frames;
  m_frames_in_a_row = _sheet_params.frames_in_a_row;
  m_frame_time = _sheet_params.frame_time;
  m_frame_counter = 0;
  m_frame_time_out = 0;
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

void Game_obj_sheet::Parse( xml::parser& _p )
{
  std::cout <<"Game-Object-Sheet.  ";
  _p.next_expect( xml::parser::start_element, "game_obj_parameters", xml::content::complex );

  m_texture_id = _p.element( "texture" );
  m_image_size.x = Parse_type< float >( _p, "image_size_x" );
  m_image_size.y = Parse_type< float >( _p, "image_size_y" );
  m_position.x = Parse_type< float >( _p, "position_x" );
  m_position.y = Parse_type< float >( _p, "position_y" );
  m_scale.x = Parse_type< float >( _p, "scale_x" );
  m_scale.y = Parse_type< float >( _p, "scale_y" );
  m_size.x = Parse_type< float >( _p, "size_x" );
  m_size.y = Parse_type< float >( _p, "size_y" );

  _p.next_expect( xml::parser::end_element );//game_obj_parameters
  _p.next_expect( xml::parser::start_element, "game_obj_sheet_parameters", xml::content::complex );

  m_total_num_of_frames = Parse_type< int >( _p, "total_num_of_frames" );
  m_frames_in_a_row = Parse_type< int >( _p, "frames_in_a_row" );
  m_frame_time = Parse_type< float >( _p, "frame_time" );

  _p.next_expect( xml::parser::end_element );//game_obj_sheet_parameters

  m_frame_counter = 0;
  m_frame_time_out = 0;
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
  if( (float)SDL_GetTicks() > m_frame_time_out )
    {
      m_frame_counter++;
      m_frame_time_out = SDL_GetTicks() + m_frame_time;
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
  std::cout << "Game_obj_sheet.Clean() is Done  &  ";
  Game_obj::Clean();
}
