
#include "Objects_blueprint.h"
#include "Texture_manager.h"
#include "Game.h"



// --- Object_load_parameters ---


// --- Object_blueprint ---


// --- Object_default ---
Object_default::Object_default( Object_load_parameters& _params ) : Object_blueprint( _params )
{
  m_texture_id = _params.Get_id();
  m_texture_flip = _params.Get_flip();

  m_position = _params.Get_position();
  m_w = _params.Get_w();
  m_h = _params.Get_h();
  m_frame = _params.Get_frame();
  m_row = _params.Get_row();
  m_frame_speed = _params.Get_frame_speed();

  m_current_frame = 0;
  m_last_frame = 0;
  m_current_row = 0;

}



void Object_default::Update()
{
  m_velocity += m_acceleration;
  m_position += m_velocity;

  m_current_frame = (( SDL_GetTicks() / m_frame_speed ) % m_frame );
  if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
    m_current_row = (( m_current_row + 1 ) % m_row );
  m_last_frame = m_current_frame;
}

void Object_default::Draw()
{
  if( m_velocity.x > 0 )  m_texture_flip = SDL_FLIP_NONE;
  if( m_velocity.x < 0 )  m_texture_flip = SDL_FLIP_HORIZONTAL;

  the_Texture_manager::Instance().Drow_frame( the_Game::Instance().Get_renderer(), m_texture_id, 
					      (int)m_position.x, (int)m_position.y, m_w, m_h, 
					      m_current_row, m_current_frame, m_texture_flip );
}

void Object_default::Clean()
{
  std::cout << "Object_default.Clean() is Done.\n";
}
