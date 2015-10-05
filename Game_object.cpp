
#include "Game_object.h"


// --- Game Object ---
void Game_object::Load( std::string s_id, int s_x, int s_y, int s_w, int s_h, SDL_RendererFlip s_flip )
{
  m_texture_id = s_id;
  m_x = s_x;
  m_y = s_y;
  m_w = s_w;
  m_h = s_h;
  m_flip = s_flip;

  m_current_frame = 0;
  m_last_frame = 0;
  m_current_row = 0;
}



void Game_object::Draw( SDL_Renderer* s_renderer_ptr )
{
  Texture_manager::Instance()->Drow_frame( s_renderer_ptr, m_texture_id, m_x, m_y, m_w, m_h, 
					   m_current_row, m_current_frame, m_flip );
}



void Game_object::Update()
{
  m_current_frame = (( SDL_GetTicks() / 50 ) % 8 );

  if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
    m_current_row = (( m_current_row + 1 ) % 3 );

  m_last_frame = m_current_frame;
}



void Game_object::Clean()
{

}






// --- Player ---
void Player::Load( std::string s_id, int s_x, int s_y, int s_w, int s_h, SDL_RendererFlip s_flip )
{
  Game_object::Load( s_id, s_x, s_y, s_w, s_h, s_flip );
}

void Player::Draw( SDL_Renderer* s_renderer_ptr )
{
  Game_object::Draw( s_renderer_ptr );
}

void Player::Update()
{
  m_current_frame = (( SDL_GetTicks() / 15 ) % 8 );

  if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
    m_current_row = (( m_current_row + 1 ) % 3 );

  m_last_frame = m_current_frame;
}

void Player::Clean()
{

}



// --- Enemy ---
void Enemy::Load( std::string s_id, int s_x, int s_y, int s_w, int s_h, SDL_RendererFlip s_flip )
{
  Game_object::Load( s_id, s_x, s_y, s_w, s_h, s_flip );
}

void Enemy::Draw( SDL_Renderer* s_renderer_ptr )
{
  Game_object::Draw( s_renderer_ptr );
}

void Enemy::Update()
{
  m_current_frame = (( SDL_GetTicks() / 150 ) % 8 );

  if (( m_current_frame == 0 )&&( m_current_frame != m_last_frame ))
    m_current_row = (( m_current_row + 1 ) % 3 );

  m_last_frame = m_current_frame;
}

void Enemy::Clean()
{

}
