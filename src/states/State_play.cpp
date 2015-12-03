
#include "State_play.h"
#include "Input_handler.h"
#include "Texture_manager.h"

#include "Game_world.h"
#include "Game.h"
#include "State_main_menu.h"
#include "State_pause.h"
#include "Game_obj_sheet_button.h"
#include "Game_obj_sheet_player.h"
#include "Game_obj_grid.h"



// --- PLAY STATE ---
// --- Static Variables: ---
const std::string State_play::sm_menu_id = "PLAY";

// --- Static Functions: ---
void State_play::smf_Play_to_pause()
{
  the_Game::Instance().Get_state_machine()->Push_state( new State_pause );
}



// --- Functions: ---
void State_play::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering PLAY-state.\n";
  SDL_SetCursor ( SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_CROSSHAIR ));

  m_camera.Setup();

  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), "HELI", "assets/Helicopter.png" );
  the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), "ROUND_B", "assets/Round_button.png" );
  // Make Objects:
  {
    m_objects_vec.push_back( new Game_obj_grid );
  }{
    Game_obj_parameters obj_params( "HELI", the_Texture_manager::Instance().Get_image_size( "HELI" ), 
				    ( the_World::Instance().Get_display_size() / 2.0f ));
    m_objects_vec.push_back( new Game_obj( obj_params ));
  }{// The Player:
    Game_obj_parameters obj_params( "HELI", the_Texture_manager::Instance().Get_image_size( "HELI" ), 
				    glm::vec2( 10, ( the_World::Instance().Get_display_height() / 3 )));
    Game_obj_sheet_parameters sheet_params( 4, 4 );
    m_objects_vec.push_back( new Game_obj_sheet_player( obj_params, sheet_params, &m_camera ));
  }{// The Pause Button:
    Game_obj_parameters obj_params( "ROUND_B", the_Texture_manager::Instance().Get_image_size( "ROUND_B" ), 
				    glm::vec2( 5, 5 ), glm::vec2( 0.15, 0.15 ));
    Game_obj_sheet_parameters sheet_params( 3, 1 );
    m_objects_vec.push_back( new Game_obj_sheet_button( obj_params, sheet_params, smf_Play_to_pause ));
  }// The 'new Game_objects' are deleted in: Play-state::on_Exit().
}



void State_play::Update()
{
  const Uint8* keys_state = the_Input_handler::Instance().Get_keys_state();

  if( keys_state[ SDL_SCANCODE_ESCAPE ] )
    the_Game::Instance().Get_state_machine()->Push_state( new State_pause );

  // Updating the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj_default* i ){ i->Update(); } );
}



void State_play::Render()
{
  // Rendering the Game Objects:
  for( auto i = m_objects_vec.begin() ; i != m_objects_vec.end() ; ++i )
    (*i)->Draw( &m_camera );
}



void State_play::on_Exit()
{
  std::cout << "STATE MACHINE :: Exiting PLAY-state.\n";
  // Deleting Oblects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj_default* i ){ i->Clean(); delete i; } );
  m_objects_vec.clear();
}
