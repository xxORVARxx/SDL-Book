
#include "State_main_menu.h"
#include "Input_handler.h"
#include "Texture_manager.h"

#include "Game_world.h"
#include "Game.h"
#include "State_play.h"
#include "Game_obj_sheet_button.h"



// --- MAIN MENU STATE ---
// --- Static Variables: ---
const std::string State_main_menu::sm_menu_id = "MENU";

// --- Static Functions: ---
void State_main_menu::smf_Menu_to_play()
{
  the_Game::Instance().Get_state_machine()->Change_state( new State_play );
}
void State_main_menu::smf_Exit_from_menu()
{
  the_Input_handler::Instance().Quit();
}



// --- Functions: ---
void State_main_menu::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering MENU-state.\n";
  SDL_SetCursor ( SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_ARROW ));
  /*
  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), "PLAY_B", "assets/Play_button.png" );
  the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), "EXIT_B", "assets/Exit_button.png" );
  {// Make Objects:
    glm::vec2 button_position = ( the_World::Instance().Get_display_size() / 2.0f );
    button_position.y -= ( button_position.y / 3.0f ); 
    glm::vec2 image_size = the_Texture_manager::Instance().Get_image_size( "PLAY_B" );
    Game_obj_parameters obj_params( "PLAY_B", image_size, ( button_position - ( image_size / 2.0f )));
    Game_obj_sheet_parameters sheet_params( 3, 1 );
    m_objects_vec.push_back( new Game_obj_sheet_button( obj_params, sheet_params, smf_Menu_to_play ));
  }{
    glm::vec2 button_position = ( the_World::Instance().Get_display_size() / 2.0f );
    button_position.y += ( button_position.y / 3.0f );
    glm::vec2 image_size = the_Texture_manager::Instance().Get_image_size( "EXIT_B" );
    Game_obj_parameters obj_params( "EXIT_B", image_size, ( button_position - ( image_size / 2.0f  )));
    Game_obj_sheet_parameters sheet_params( 3, 1 );
    m_objects_vec.push_back( new Game_obj_sheet_button( obj_params, sheet_params, smf_Exit_from_menu ));
  }// The 'new Game_objects' are deleted in: Menu-state::on_Exit().
  */
}



void State_main_menu::on_Display_resize() 
{
  this->on_Exit();
  this->on_Enter();
}



void State_main_menu::Update()
{
  // Updating the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj_default* i ){ i->Update(); } );
}



void State_main_menu::Render()
{
  // Rendering the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj_default* i ){ i->Draw( nullptr ); } );
}



void State_main_menu::on_Exit()
{
  std::cout << "STATE MACHINE :: Exiting MENU-state.\n";
  // Deleting Oblects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Game_obj_default* i ){ i->Clean(); delete i; } );
  m_objects_vec.clear();
}
