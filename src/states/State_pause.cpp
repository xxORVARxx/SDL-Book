
#include "State_pause.h"

#include "XML_parser_states.h"



// --- PAUSE STATE ---
// --- Static Variables: ---
const std::string State_pause::sm_state_id = "PAUSE";



// --- Functions: ---
void State_pause::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering PAUSE-state.\n";
  SDL_SetCursor ( SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_ARROW ));

  // Using the 'State-Parser' to loading the 'Textures'(with the 'Singleton-Class') and make the Game-Objects:
  State_parser pause_parser;
  pause_parser.Parse_state( "XML/State_pause.xml", sm_state_id, m_objects_vec );
  // The 'Game_objects' are deleted in: Base-state::on_Exit().
}



void State_pause::on_Display_resize() 
{
  this->on_Exit();
  this->on_Enter();
}



void State_pause::Update()
{
  // Updating the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Base_game_obj* i ){ i->Update(); } );
}



void State_pause::Render()
{
  // Rendering the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Base_game_obj* i ){ i->Draw( nullptr ); } );
}



void State_pause::on_Exit()
{
  std::cout << "STATE MACHINE :: Exiting PAUSE-state.\n";
  Base_state::on_Exit(); // Deleting Oblects.
}
