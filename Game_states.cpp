
#include "Game_states.h"


// --- MENU STATE ---
// --- Static Variables ---
const std::string Menu_state::sm_menu_id = "MENU";



// --- Functions ---
bool Menu_state::on_Enter()
{
  std::cout << "Entering MENU-state\n";
  return true;
}

void Menu_state::Update()
{

}

void Menu_state::Render()
{

}

bool Menu_state::on_Exit()
{
  std::cout << "Exiting MENU-state\n";
  return true;
}



// --- PLAY STATE ---
// --- Static Variables ---
const std::string Play_state::sm_menu_id = "PLAY";



// --- Functions ---
bool Play_state::on_Enter()
{
  std::cout << "Entering PLAY-state\n";
  return true;
}

void Play_state::Update()
{

}

void Play_state::Render()
{

}

bool Play_state::on_Exit()
{
  std::cout << "Exiting PLAY-state\n";
  return true;
}


