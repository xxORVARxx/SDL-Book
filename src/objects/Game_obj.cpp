
#include "Game_obj.h"
#include "Texture_manager.h"

#include "Game.h"



// --- Game object ---
Game_obj::Game_obj( Game_obj_parameters& _obj_params, bool is_a_sheet )
{
  m_texture_id = _obj_params.texture_id;
  m_image_size = _obj_params.image_size;
  m_position = _obj_params.position;
  m_scale = _obj_params.scale;
  m_size = _obj_params.size;

  // If this is a 'Game_obj_sheet', then this is done in the Game_obj_sheet's constructor instead.
  if ( ! is_a_sheet )
    {
      // If there is no 'size' requested ('size' is 0), then the 'image_size' is used:
      if( m_size.x == 0 )  m_size.x = m_image_size.x;
      if( m_size.y == 0 )  m_size.y = m_image_size.y;
      m_size *= m_scale;
    }
}



void Game_obj::Draw()
{
  the_Texture_manager::Instance().Draw( the_Game::Instance().Get_renderer(), m_texture_id, m_position, m_size );
}

void Game_obj::Clean()
{
  std::cout << "Game_obj.Clean() is Done.\n";
}
