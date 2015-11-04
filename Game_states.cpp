
#include "Game_states.h"
#include "Texture_manager.h"
#include "Input_handler.h"
#include "Game.h"




// --- MENU STATE ---
// --- Static Variables: ---
const std::string Menu_state::sm_menu_id = "MENU";

// --- Static Functions: ---
void Menu_state::smf_Menu_to_play()
{
  the_Game::Instance().Get_state_machine()->Change_state( new Play_state );
}
void Menu_state::smf_Exit_from_menu()
{
  the_Input_handler::Instance().Quit();
}



// --- Functions: ---
void Menu_state::on_Enter()
{
  m_c = '?';
  std::cout << "STATE MACHINE :: Entering MENU-state.\n";

  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance().Load( the_Game::Instance().Get_renderer(), "PLAY_B", "assets/Play_button.png" );
  the_Texture_manager::Instance().Load( the_Game::Instance().Get_renderer(), "EXIT_B", "assets/Exit_button.png" );

  // Make Objects:
  Object_load_parameters for_button_1( "PLAY_B", glm::vec2( 100, 100 ), 255, ( 147/3 ));
  m_objects_vec.push_back( new Button( for_button_1, smf_Menu_to_play ));
  Object_load_parameters for_button_2( "EXIT_B", glm::vec2( 100, 200 ), 255, ( 147/3 ));
  m_objects_vec.push_back( new Button( for_button_2, smf_Exit_from_menu ));
  // The 'new Button()' is deleted in: Menu_state::on_Exit().
}

void Menu_state::Update()
{
  // Updating the Game Objects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i )
    m_objects_vec[i]->Update();
  /*
  std::cout <<"\t M Update:\n\t 'd'=Delete, 'c'=Change, 'm'=Push-M, 'p'=Push-P\n\t 'esc'=To Continue, 'q' to Quit.\n";
  while( m_c != 27 )
    {
      std::cin >> m_c;
      if( m_c == 'q' ) {
	std::cout <<"\t\t Quit!\n";
	smf_Exit_from_menu();
      }
      if( m_c == 'd' ) {
	std::cout <<"\t\t Delete State!\n";
	Pop();
      }
      else if( m_c == 'c' ) {
	std::cout <<"\t\t Change to P!\n";
	smf_Menu_to_play();
      }
      else if( m_c == 'm' ) {
	std::cout <<"\t\t Push M!\n";
	Push_M();
      }
      else if( m_c == 'p' ) {
	std::cout <<"\t\t Push P!\n";
	Push_P();
      }
    }
  m_c = '?';
  */
}

void Menu_state::Render()
{
  // Rendering the Game Objects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i )
    m_objects_vec[i]->Draw();
}

void Menu_state::on_Exit()
{
  std::cout << "STATE MACHINE :: Exiting MENU-state.\n";
  // Deleting Oblects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Object_default* i ){ i->Clean(); delete i; } );
  m_objects_vec.clear();
}



// --- PLAY STATE ---
// --- Static Variables: ---
const std::string Play_state::sm_menu_id = "PLAY";

// --- Static Functions: ---
void Play_state::smf_Play_to_menu()
{
  the_Game::Instance().Get_state_machine()->Change_state( new Menu_state );
}



// --- Functions: ---
void Play_state::on_Enter()
{
  m_c = '?';
  std::cout << "STATE MACHINE :: Entering PLAY-state.\n";

  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance().Load( the_Game::Instance().Get_renderer(), "B_B", "assets/Blue_button.png" );
  the_Texture_manager::Instance().Load( the_Game::Instance().Get_renderer(), "ALIEN", "assets/Alien_sprite_sheet.png" );
  the_Texture_manager::Instance().Load( the_Game::Instance().Get_renderer(), "GNU", "assets/Baby_Gnu.png" );

  // Make Objects:
  Object_load_parameters for_button_1( "B_B", glm::vec2( 5, 5 ), 56, ( 147/3 ));
  m_objects_vec.push_back( new Button( for_button_1, smf_Play_to_menu ));
  Object_load_parameters for_player( "ALIEN", glm::vec2( 100, 100 ), ( 2096/8 ), ( 786/3 ));
  m_objects_vec.push_back( new Player( for_player ));
  Object_load_parameters for_enemy( "GNU", glm::vec2( 400, 150 ), 614, 555 );
  m_objects_vec.push_back( new Enemy( for_enemy ));
  // The 'new Button()' is deleted in: Menu_state::on_Exit().
}

void Play_state::Update()
{
  // Updating the Game Objects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i )
    m_objects_vec[i]->Update();
  /*
  std::cout <<"\t P Update:\n\t 'd'=Delete, 'c'=Change, 'm'=Push-M, 'p'=Push-P\n\t 'esc'=To Continue.\n";
  while( m_c != 27 )
    {
      std::cin >> m_c;
      if( m_c == 'd' ) {
	std::cout <<"\t\t Delete State!\n";
	Pop();
      }
      else if( m_c == 'c' ) {
	std::cout <<"\t\t Change to M!\n";
	Change_P_to_M();
      }
      else if( m_c == 'm' ) {
	std::cout <<"\t\t Push M!\n";
	Push_M();
      }
      else if( m_c == 'p' ) {
	std::cout <<"\t\t Push P!\n";
	Push_P();
      }
    }
  m_c = '?';
  */
}

void Play_state::Render()
{
  // Rendering the Game Objects:
  for ( int i = 0 ; i < m_objects_vec.size() ; ++i )
    m_objects_vec[i]->Draw();
}

void Play_state::on_Exit()
{
  std::cout << "STATE MACHINE :: Exiting PLAY-state.\n";
  // Deleting Oblects:
  std::for_each( m_objects_vec.begin(), m_objects_vec.end(), []( Object_default* i ){ i->Clean(); delete i; } );
  m_objects_vec.clear();
}


