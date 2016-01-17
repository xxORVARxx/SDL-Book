
#include "State_pause.h"
#include "Input_handler.h"
#include "Texture_manager.h"

#include "Game_world.h"
#include "Game.h"
#include "State_main_menu.h"
#include "Game_obj_sheet_button.h"



// --- PAUSE STATE ---
// --- Static Variables: ---
const std::string State_pause::sm_pause_id = "PAUSE";

// --- Static Functions: ---
void State_pause::smf_Pause_to_main()
{
  the_Game::Instance().Get_state_machine()->Change_state( new State_main_menu );
}
void State_pause::smf_Pause_to_play()
{
  the_Game::Instance().Get_state_machine()->Pop_state();
}



// --- Functions: ---
void State_pause::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering PAUSE-state.\n";
  SDL_SetCursor ( SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_ARROW ));
  /*
  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), "RESUME_B", "assets/Resume_button.png" );
  the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), "MM_B", "assets/MM_button.png" );
  {// Make Objects:
    glm::vec2 button_position = ( the_World::Instance().Get_display_size() / 2.0f );
    button_position.y -= ( button_position.y / 3.0f ); 
    glm::vec2 image_size = the_Texture_manager::Instance().Get_image_size( "RESUME_B" );
    Game_obj_parameters obj_params( "RESUME_B", image_size, ( button_position - ( image_size / 2.0f )));
    Game_obj_sheet_parameters sheet_params( 3, 1 );
    m_objects_vec.push_back( new Game_obj_sheet_button( obj_params, sheet_params, smf_Pause_to_play ));
  }{
    glm::vec2 button_position = ( the_World::Instance().Get_display_size() / 2.0f );
    button_position.y += ( button_position.y / 3.0f ); 
    glm::vec2 image_size = the_Texture_manager::Instance().Get_image_size( "MM_B" );
    Game_obj_parameters obj_params( "MM_B", image_size, ( button_position - ( image_size / 2.0f )));
    Game_obj_sheet_parameters sheet_params( 3, 1 );
    m_objects_vec.push_back( new Game_obj_sheet_button( obj_params, sheet_params, smf_Pause_to_main ));
  }// The 'new Game_objects' are deleted in: Pause-state::on_Exit().
  */
}



void State_pause::on_Display_resize() 
{
  this->on_Exit();
  this->on_Enter();
}



void State_pause::Update()
{
  // Updating the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj_default* i ){ i->Update(); } );
}



void State_pause::Render()
{
  // Rendering the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj_default* i ){ i->Draw( nullptr ); } );
}



void State_pause::on_Exit()
{
  std::cout << "STATE MACHINE :: Exiting PAUSE-state.\n";
  // Deleting Oblects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj_default* i ){ i->Clean(); delete i; } );
  m_objects_vec.clear();
}
