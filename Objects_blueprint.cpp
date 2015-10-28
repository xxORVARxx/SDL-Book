
#include "Objects_blueprint.h"
#include "Texture_manager.h"
#include "Game.h"



// --- Object_load_parameters ---


// --- Object_blueprint ---


// --- Object_default ---
Object_default::Object_default( Object_load_parameters& params ) : Object_blueprint( params )
{
  m_texture_id = params.Get_id();
  m_texture_flip = params.Get_flip();

  m_position = params.Get_position();
  m_w = params.Get_w();
  m_h = params.Get_h();

  m_current_frame = 0;
  m_last_frame = 0;
  m_current_row = 0;
}



void Object_default::Update()
{
  m_velocity += m_acceleration;
  m_position += m_velocity;
}

void Object_default::Draw()
{
  the_Texture_manager::Instance()->Drow_frame( the_Game::Instance()->Get_renderer(), m_texture_id, 
					       (int)m_position.x, (int)m_position.y, m_w, m_h, 
					       m_current_row, m_current_frame, m_texture_flip );
}

void Object_default::Clean()
{
  std::cout << "Object_default.Clean() is Done.\n";
}


