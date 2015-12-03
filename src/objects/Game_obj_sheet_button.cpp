
#include "Game_obj_sheet_button.h"
#include "Input_handler.h"
#include "Texture_manager.h"

#include "Game.h"



// --- BUTTON ---
Game_obj_sheet_button::Game_obj_sheet_button( Game_obj_parameters& _obj_params, Game_obj_sheet_parameters& _sheet_params, 
					      void (*f_Callback)()) : 
  Game_obj_sheet(_obj_params, _sheet_params), mf_Callback(f_Callback)
{
  m_clicked = false;
}



void Game_obj_sheet_button::Update()
{
  // Get Mouse Position/Coordinates:
  const glm::vec2 mouse_pos = the_Input_handler::Instance().Get_mouse_position();
  // Check whether the Mouse is over the Button or not:
  if( xx::Point_in_rect( mouse_pos, glm::vec4( m_position.x, m_position.y, m_size.x, m_size.y )))
    {
      if( m_clicked &&( ! the_Input_handler::Instance().Get_mouse_button( SDL_BUTTON_LEFT )))
	{
	  mf_Callback(); // Calling the function pointer.
	  m_clicked = false;
	}
      else if( the_Input_handler::Instance().Get_mouse_button( SDL_BUTTON_LEFT ))
	{
	  m_frame_counter = MOUSE_CLICKED;
	  m_clicked = true;
	}
      else
	{
	  m_frame_counter = MOUSE_OVER;
	  m_clicked = false;
	}
    }
  else
    {
      m_frame_counter = MOUSE_OUT;
      m_clicked = false;
    }
}



void Game_obj_sheet_button::Draw()
{
  // Finding the frame: (the first frame/row is number '1' not '0')
  int row_number;
  if( m_frame_counter % m_frames_in_a_row )
    row_number = (( m_frame_counter / m_frames_in_a_row ) + 1 );
  else
    row_number = ( m_frame_counter / m_frames_in_a_row );
  int frame_number = (( m_frame_counter - (( row_number - 1 ) * m_frames_in_a_row )));

  the_Texture_manager::Instance().Draw_frame( the_Game::Instance().Get_renderer(), m_texture_id, m_position, m_size,
					      m_frame_width, m_frame_height, frame_number, row_number );
}
