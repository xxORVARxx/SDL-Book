
#include "Game_states.h"
#include "Texture_manager.h"
#include "Game.h"




// --- MENU STATE ---
// --- Static Variables ---
const std::string Menu_state::sm_menu_id = "MENU";



// --- Functions ---
bool Menu_state::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering MENU-state.\n";

  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance()->Load( the_Game::Instance()->Get_renderer(), "PLAY_B", "assets/Play_button.png" );
  the_Texture_manager::Instance()->Load( the_Game::Instance()->Get_renderer(), "EXIT_B", "assets/Exit_button.png" );
  
  // Make Objects:
  m_objects_vec.push_back( new Button( new Object_load_parameters( "PLAY_B", glm::vec2( 100, 100 ), 255, ( 147/3 ) )));
  m_objects_vec.push_back( new Button( new Object_load_parameters( "EXIT_B", glm::vec2( 100, 200 ), 255, ( 147/3 ) )));
  // The 'new Object_load_parameters()' is deleted in: Object_default::Object_default(),
  // And the 'new Button()' is deleted in: Menu_state::on_Exit(). 

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
// --- Static Variables ---
const std::string Play_state::sm_menu_id = "PLAY";



// --- Functions ---
bool Play_state::on_Enter()
{
  std::cout << "STATE MACHINE :: Entering PLAY-state.\n";

  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance()->Load( the_Game::Instance()->Get_renderer(), "ALIEN", "assets/Alien_sprite_sheet.png" );
  the_Texture_manager::Instance()->Load( the_Game::Instance()->Get_renderer(), "GNU", "assets/Baby_Gnu.png" );
  
  // Make Objects:
  m_objects_vec.push_back( new Player( new Object_load_parameters( "ALIEN", glm::vec2( 100, 100 ), ( 2096/8 ), ( 786/3 ) )));
  m_objects_vec.push_back( new Enemy( new Object_load_parameters( "GNU", glm::vec2( 400, 150 ), 614, 555 )));
  // The 'new Object_load_parameters()' is deleted in: Object_default::Object_default(),
  // And the 'new Button()' is deleted in: Menu_state::on_Exit(). 

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


