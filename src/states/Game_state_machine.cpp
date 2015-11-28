 
#include "Game_state_machine.h"



// --- Functions: ---
// Adding one state without removing the previous state:
void Game_state_machine::Push_state( State_interface* _state_ptr )
{
  if( _state_ptr == nullptr ) {
    std::cout << "STATE MACHINE :: ERROR: Can't Push 'NULL' as a State!\n";
    return;
  }
  m_refresh = true;
  m_state_change_vec.push_back( _state_ptr );// Add.
}

// Removing one state and adding another:
void Game_state_machine::Change_state( State_interface* _state_ptr )
{
  if( _state_ptr == nullptr ) {
    std::cout << "STATE MACHINE :: ERROR: Can't Change a State with 'NULL'!\n";
    return;
  }
  m_refresh = true;
  if( _state_ptr->Get_state_id() != m_states_vec.back()->Get_state_id() ) {
    m_state_change_vec.push_back( nullptr );// Remove.
    m_state_change_vec.push_back( _state_ptr );// Add.
  }
}

// Removing one state without adding another:
void Game_state_machine::Pop_state()
{
  m_refresh = true;
  m_state_change_vec.push_back( nullptr );// Remove.
}



void Game_state_machine::Update()
{
  if( ! m_states_vec.empty() )
    m_states_vec.back()->Update();

  if( m_refresh )
    this->Refresh();
}

void Game_state_machine::Render()
{
  if( ! m_states_vec.empty() )
    m_states_vec.back()->Render();
}

void Game_state_machine::Clean()
{
  std::for_each( m_states_vec.begin(), m_states_vec.end(), []( State_interface* i ){ i->on_Exit(); delete i; } );
  m_states_vec.clear();
  std::for_each( m_state_change_vec.begin(), m_state_change_vec.end(), []( State_interface* i ){ i->on_Exit(); delete i; } );
  m_state_change_vec.clear();
  std::cout << "STATE MACHINE :: Clean() is done.\n";
}



void Game_state_machine::Delete_and_remove_state()
{
  if( ! m_states_vec.empty() ) 
    {
      m_states_vec.back()->on_Exit();
      delete m_states_vec.back();
      m_states_vec.pop_back();
    }
}

void Game_state_machine::Add_and_begin_state( State_interface* _state_ptr ) 
{
  m_states_vec.push_back( _state_ptr );
  m_states_vec.back()->on_Enter();
}

void Game_state_machine::Refresh()
{
  for( auto i = m_state_change_vec.begin() ; i != m_state_change_vec.end() ; ++i ) 
    {
      if( *i == nullptr )
	this->Delete_and_remove_state();
      else 
        this->Add_and_begin_state( *i );
    }
  m_state_change_vec.clear();
  m_refresh = false;
}
