
#include "Objects_blueprint.h"
#include "Texture_manager.h"
#include "Game.h"



// --- Object_load_parameters ---


// --- Object_blueprint ---


// --- Object_default ---
Object_default::Object_default( Object_load_parameters* params_ptr ) : Object_blueprint( params_ptr )
{
  m_texture_id = params_ptr->Get_id();
  m_texture_flip = params_ptr->Get_flip();

  m_x = params_ptr->Get_x();
  m_y = params_ptr->Get_y();
  m_w = params_ptr->Get_w();
  m_h = params_ptr->Get_h();

  m_current_frame = 0;
  m_last_frame = 0;
  m_current_row = 0;
}



void Object_default::Update()
{
  m_current_frame = (( SDL_GetTicks() / 50 ) % 8 );
  if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
    m_current_row = (( m_current_row + 1 ) % 3 );
  m_last_frame = m_current_frame;
}



void Object_default::Draw()
{
  Texture_manager::Instance()->Drow_frame( Game::Instance()->Get_renderer(), m_texture_id, m_x, m_y, m_w, m_h, 
					   m_current_row, m_current_frame, m_texture_flip );
}



void Object_default::Clean()
{
  std::cout << "Object_default.Clean() Done\n";
}


