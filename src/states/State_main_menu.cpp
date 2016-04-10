
#include "State_main_menu.h"

#include "XML_parser_states.h"
#include "SDL_gobj.h"
#include "xx_String_cast.h"

// --- MAIN MENU STATE ---
// --- Static Variables: ---
const std::string State_main_menu::sm_state_id = "MAIN_MENU";



// --- Functions: ---
void State_main_menu::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering MAIN-MENU-state.\n";
  SDL_SetCursor ( SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_ARROW ));
  
  // Using the 'State-Parser' to loading the 'Textures'(with the 'Singleton-Class') and make the Game-Objects:
  State_parser main_menu_parser;
  main_menu_parser.Parse_state( "XML/State_main_menu.xml", sm_state_id, m_objects_vec );
  // The 'Game_objects' are deleted in: Base-state::on_Exit().
}



void State_main_menu::on_Display_resize() 
{
  this->on_Exit();
  this->on_Enter();
}



void State_main_menu::Update()
{
  // Updating the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Base_game_obj* i ){ i->Update(); } );
}



void State_main_menu::Render()
{
  // Rendering the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Base_game_obj* i ){ i->Draw( nullptr ); } );
}



void State_main_menu::on_Exit()
{
  std::cout << "STATE MACHINE :: Exiting MAIN-MENU-state.\n";
  Base_state::on_Exit(); // Deleting Oblects.
}
