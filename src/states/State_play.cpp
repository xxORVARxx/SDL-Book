
#include "State_play.h"
#include "Input_handler.h"

#include "XML_parser_states.h"



// --- PLAY STATE ---
// --- Static Variables: ---
const std::string State_play::sm_state_id = "PLAY";



// --- Functions: ---
void State_play::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering PLAY-state.\n";
  SDL_SetCursor ( SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_CROSSHAIR ));

  // Using the 'State-Parser' to loading the 'Textures'(with the 'Singleton-Class') and make the Game-Objects:
  State_parser play_parser;
  play_parser.Parse_state( "XML/State_play.xml", sm_state_id, m_objects_vec );
  // The 'Game_objects' are deleted in: Base-state::on_Exit().
}



void State_play::Update()
{
  const Uint8* keys_state = the_Input_handler::Instance().Get_keys_state();

  if( keys_state[ SDL_SCANCODE_ESCAPE ] )
    f_Play_to_pause();

  // Updating the Game Objects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Base_game_obj* i ){ i->Update(); } );
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
  Base_state::on_Exit(); // Deleting Oblects.
}
