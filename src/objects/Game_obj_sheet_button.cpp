
#include "Game_obj_sheet_button.h"
#include "Input_handler.h"
#include "Texture_manager.h"

#include "Game.h"



// --- BUTTON ---
void Game_obj_sheet_button::Load( Game_obj_button_parameters& _button_params )
{
  mf_Callback = _button_params.mf_Callback;
  m_clicked = false;
}

void Game_obj_sheet_button::Parse( xml::parser& _p )
{
  std::cout <<"Game-Object-Sheet-Button.  ";
  Game_obj_sheet::Parse( _p );
  _p.next_expect( xml::parser::start_element, "game_obj_button_parameters", xml::content::complex );

  std::string call_back = _p.attribute( "mf_Callback" );

  _p.next_expect( xml::parser::end_element );//game_obj_button_parameters

  m_clicked = false;
}



void Game_obj_sheet_button::Update()
{
  /*
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
  */
}



void Game_obj_sheet_button::Draw( Camera* _camera )
{
  /*
  // Finding the frame: (the first frame/row is number '1' not '0')
  int row_number;
  if( m_frame_counter % m_frames_in_a_row )
    row_number = (( m_frame_counter / m_frames_in_a_row ) + 1 );
  else
    row_number = ( m_frame_counter / m_frames_in_a_row );
  int frame_number = (( m_frame_counter - (( row_number - 1 ) * m_frames_in_a_row )));

  the_Texture_manager::Instance().Draw_frame( the_Game::Instance().Get_renderer(), m_texture_id, m_position, m_size,
					      m_frame_width, m_frame_height, frame_number, row_number );
  */
}
