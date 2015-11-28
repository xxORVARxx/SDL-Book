
#include "State_play.h"
#include "State_pause.h"
#include "State_main_menu.h"
#include "Game.h"
#include "Texture_manager.h"
#include "Input_handler.h"
#include "Game_obj_sheet_button.h"
#include "Game_obj_sheet_player.h"



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

  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), "HELI", "assets/Helicopter.png" );
  the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), "ROUND_B", "assets/Round_button.png" );
  {// Make Objects:
    Game_obj_parameters obj_params( "HELI", the_Texture_manager::Instance().Get_image_size( "HELI" ), 
				    glm::vec2( 10, ( the_Game::Instance().Get_display_size().y / 3 )));
    Game_obj_sheet_parameters sheet_params( 4, 4 );
    m_objects_vec.push_back( new Game_obj_sheet_player( obj_params, sheet_params ));
  }{
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
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj* i ){ i->Update(); } );
}

void State_play::Render()
{
  // Rendering the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj* i ){ i->Draw(); } );
}

void State_play::on_Exit()
{
  std::cout << "STATE MACHINE :: Exiting PLAY-state.\n";
  // Deleting Oblects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj* i ){ i->Clean(); delete i; } );
  m_objects_vec.clear();
}
