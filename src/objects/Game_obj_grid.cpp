 
#include "Game_obj_grid.h"

#include "Game_world.h"
#include "Game.h"
#include "XML_parser_states.h"



// --- GRID ---
void Game_obj_grid::Load( Game_obj_grid_parameters& _grid_params )
{
   m_color = _grid_params.color;
   m_grid_size = _grid_params.grid_size;
}

void Game_obj_grid::Parse( xml::parser& _p )
{
  std::cout <<"Game-Object-Grid.  ";
  _p.next_expect( xml::parser::start_element, "game_obj_grid_parameters", xml::content::complex );

  m_color.r = (Uint8)Parse_type< unsigned int >( _p, "color_r" );
  m_color.g = (Uint8)Parse_type< unsigned int >( _p, "color_g" );
  m_color.b = (Uint8)Parse_type< unsigned int >( _p, "color_b" );
  m_color.a = (Uint8)Parse_type< unsigned int >( _p, "color_a" );
  m_grid_size = Parse_type< unsigned int >( _p, "grid_size" );

  _p.next_expect( xml::parser::end_element );//game_obj_grid_parameters
}



void Game_obj_grid::Draw( Camera* _camera )
{
  int position_x = 0;
  int position_y = 0;
  int display_size_w = the_World::Instance().Get_display_width();
  int display_size_h = the_World::Instance().Get_display_height();
  if( _camera != nullptr )
    {
      position_x = _camera->Get_position_x();
      position_y = _camera->Get_position_y();
    }

  SDL_SetRenderDrawColor( the_Game::Instance().Get_renderer(), m_color.r, m_color.g, m_color.b, m_color.a );

  for( int i = -( position_x % m_grid_size ); i <= display_size_w ; i += m_grid_size )
    SDL_RenderDrawLine( the_Game::Instance().Get_renderer(), i, 0, i, display_size_h );
  for( int i = -( position_y % m_grid_size ) ; i < display_size_h ; i += m_grid_size )
    SDL_RenderDrawLine( the_Game::Instance().Get_renderer(), 0, i, display_size_w, i );

  SDL_SetRenderDrawColor( the_Game::Instance().Get_renderer(), 0, 0, 0, 255 );
}



void Game_obj_grid::Clean()
{
  std::cout << "Game_obj_grid.Clean() is Done.\n";
}
