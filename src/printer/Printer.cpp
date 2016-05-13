 
#include "Printer.h"
#include "Texture_manager_v2.h"
#include "Game.h"
#include "Game_world.h"
#include "Camera.h"



Printer::Action::Action( std::string _texture_id, 
			 const glm::vec2* _size,
			 glm::vec2 _scale,
		         const std::vector< Image_data::Frame >* _frames,
			 const std::vector< unsigned short >* _sequence,
			 unsigned short _itr ) :
  m_end(false), m_texture_id(_texture_id), m_texture_size_ptr(_size), m_scale(_scale), m_frames_vec_ptr(_frames), m_sequence_vec_ptr(_sequence), m_sequence_iterator(_itr)
{
}



void 
Printer::Action::Start( unsigned short _itr )
{
  m_sequence_iterator = _itr;
  m_end = false;
}



void 
Printer::Action::Continue()
{
  if( m_end )
    m_end = false;
  if( ++m_sequence_iterator == m_sequence_vec_ptr->size())
    {
      m_sequence_iterator = 0;
      m_end = true;
    }
}



Printer::Printer() : 
  m_timer(0.0f), m_flip(SDL_FLIP_NONE) 
{
}



void 
Printer::Print( std::string& _action, glm::vec2 _position )
{
  auto action_itr = m_actions_map.find( _action );
  if( action_itr == m_actions_map.end())
    {
      std::cerr <<"(xx) Printer ERROR! When printing an Action with ID: '"<< _action <<"'. Sequence not found!\n";
      return;
    }

  if( m_timer < 0.0f )
    {
      action_itr->second.Continue();
      m_timer = action_itr->second.m_frames_vec_ptr->at( action_itr->second.m_sequence_vec_ptr->at( action_itr->second.m_sequence_iterator )).m_ms;
    }
  else
    m_timer -= the_World::Instance().Get_delta_time() * 1000.0f;


  m_src_rec = action_itr->second.m_frames_vec_ptr->at( action_itr->second.m_sequence_vec_ptr->at( action_itr->second.m_sequence_iterator )).m_src_rec;
  m_dest_rec.x = m_position.x;
  m_dest_rec.y = m_position.y;
  m_dest_rec.w = m_src_rec.w * m_scale.x;
  m_dest_rec.h = m_src_rec.h * m_scale.y;


  SDL_Texture* texture_ptr = nullptr;
  the_Texture_manager_v2::Instance().Get_texture( action_itr->second.m_texture_id, texture_ptr );
  SDL_Point rotate_center = { 0, 0 }; // Point to Rotate Around.
  double rotation = 0.0d;
  SDL_RenderCopyEx( the_Game::Instance().Get_renderer(), texture_ptr, &m_src_rec, &m_dest_rec, rotation, &rotate_center, m_flip );


  /*
  std::cout << _action <<":     ";
  for( int i = 0 ; i <  action_itr->second.m_sequence_vec_ptr->size() ; ++i )
    std::cout << action_itr->second.m_sequence_vec_ptr->at( i ) <<"\t";
  std::cout <<"\n";
*/
}



void 
Printer::Flip_horizontally()
{
  int flip = m_flip;
  if(( flip == 0 )||( flip == 2 ))  
    ++flip;
  else if(( flip == 1 )||( flip == 3 ))
    --flip;
  m_flip = static_cast<SDL_RendererFlip>( flip );
}

void 
Printer::Flip_horizontally( bool _set_flip )
{
  int flip = m_flip;
  if( _set_flip )
    {
      if(( flip == 0 )||( flip == 2 ))
	++flip;
    }
  else
    {
      if(( flip == 1 )||( flip == 3 ))
	--flip;
    }
  m_flip = static_cast<SDL_RendererFlip>( flip );
}

void 
Printer::Flip_vertically()
{
  int flip = m_flip;
  if(( flip == 0 )||( flip == 1 ))  
    flip += 2;
  else if(( flip == 2 )||( flip == 3 ))  
    flip -= 2;
  m_flip = static_cast<SDL_RendererFlip>( flip );
}

void 
Printer::Flip_vertically( bool _set_flip )
{
  int flip = m_flip;
  if( _set_flip )
    {
      if(( flip == 0 )||( flip == 1 ))  
	flip += 2;
    }
  else
    {
      if(( flip == 2 )||( flip == 3 ))  
	flip -= 2;
    }
  m_flip = static_cast<SDL_RendererFlip>( flip );
}

