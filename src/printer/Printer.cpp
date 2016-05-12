 
#include "Printer.h"
#include "Texture_manager_v2.h"
#include "Game.h"



Image_data::Frame::Frame( SDL_Rect& _xywh, 
			  float& _m, 
			  SDL_Point& _oxy ) : 
  m_src_rec(_xywh), m_ms(_m), m_offset(_oxy) 
{

}



Printer::Action::Action( unsigned short _itr ) :
  m_end(false), m_sequence_iterator(_itr)
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
  m_flip(SDL_FLIP_NONE) 
{

}



void 
Printer::Print( std::string _action )
{
  auto action_itr = m_actions_map.find( _action );
  if( action_itr == m_actions_map.end())
    {
      std::cerr <<"(xx) Printer ERROR! When printing an Action with ID: '"<< _action <<"'. Sequence not found!\n";
      return;
    }

  // FOR TESTING:
  std::cout << _action <<":     ";
  for( int i = 0 ; i <  action_itr->second.m_sequence_vec_ptr->size() ; ++i )
    std::cout << action_itr->second.m_sequence_vec_ptr->at( i ) <<"\t";
  std::cout <<"\n";
  /*
  SDL_Texture* texture_ptr = nullptr;
  the_Texture_manager_v2::Instance().Get_texture( m_texture_id, texture_ptr );
  SDL_Point rotate_center; // Point to Rotate Around.
  double rotation = 0.0d;
  SDL_RenderCopyEx( the_Game::Instance().Get_renderer(), texture_ptr, &m_src_rec, &m_dest_rec, rotation, &rotate_center, m_flip );
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

