
#include "Game_states.h"
#include "Texture_manager.h"
#include "Input_handler.h"
#include "Game.h"




// --- MENU STATE ---
// --- Static Variables: ---
const std::string Menu_state::sm_menu_id = "MENU";
// --- Static Functions: ---
void Menu_state::sm_Menu_to_play()
{
  the_Game::Instance()->Get_state_machine()->Change_state( new Play_state() );
}
void Menu_state::sm_Exit_from_menu()
{
  the_Input_handler::Instance()->Quit();
}



// --- Functions: ---
bool Menu_state::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering MENU-state.\n";

  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance()->Load( the_Game::Instance()->Get_renderer(), "PLAY_B", "assets/Play_button.png" );
  the_Texture_manager::Instance()->Load( the_Game::Instance()->Get_renderer(), "EXIT_B", "assets/Exit_button.png" );

  // Make Objects:
  Object_load_parameters for_button_1( "PLAY_B", glm::vec2( 100, 100 ), 255, ( 147/3 ));
  m_objects_vec.push_back( new Button( for_button_1, sm_Menu_to_play ));
  Object_load_parameters for_button_2( "EXIT_B", glm::vec2( 100, 200 ), 255, ( 147/3 ));
  m_objects_vec.push_back( new Button( for_button_2, sm_Exit_from_menu ));
  // The 'new Button()' is deleted in: Menu_state::on_Exit(). 

  return true;
}

void Menu_state::Update()
{
  // Updating the Game Objects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i )
    m_objects_vec[i]->Update();
}

void Menu_state::Render()
{
  // Rendering the Game Objects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i )
    m_objects_vec[i]->Draw();
}

bool Menu_state::on_Exit()
{
  // Deleting Oblects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i ) {
    m_objects_vec[i]->Clean();
    delete m_objects_vec[i];
    m_objects_vec[i] = NULL;
  }
  m_objects_vec.clear();

  std::cout << "STATE MACHINE :: Exiting MENU-state.\n";
  return true;
}



// --- PLAY STATE ---
// --- Static Variables: ---
const std::string Play_state::sm_menu_id = "PLAY";



// --- Functions: ---
bool Play_state::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering PLAY-state.\n";

  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance()->Load( the_Game::Instance()->Get_renderer(), "ALIEN", "assets/Alien_sprite_sheet.png" );
  the_Texture_manager::Instance()->Load( the_Game::Instance()->Get_renderer(), "GNU", "assets/Baby_Gnu.png" );

  // Make Objects:
  Object_load_parameters for_player( "ALIEN", glm::vec2( 100, 100 ), ( 2096/8 ), ( 786/3 ) );
  m_objects_vec.push_back( new Player( for_player ));
  Object_load_parameters for_enemy( "GNU", glm::vec2( 400, 150 ), 614, 555 );
  m_objects_vec.push_back( new Enemy( for_enemy ));
  // The 'new Button()' is deleted in: Menu_state::on_Exit().

  return true;
}

void Play_state::Update()
{
  // Updating the Game Objects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i )
    m_objects_vec[i]->Update();
}

void Play_state::Render()
{
  // Rendering the Game Objects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i )
    m_objects_vec[i]->Draw();
}

bool Play_state::on_Exit()
{
  // Deleting Oblects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i ) {
    m_objects_vec[i]->Clean();
    delete m_objects_vec[i];
    m_objects_vec[i] = NULL;
  }
  m_objects_vec.clear();

  std::cout << "STATE MACHINE :: Exiting PLAY-state.\n";
  return true;
}


