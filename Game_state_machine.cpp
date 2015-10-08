 
#include "Game_state_machine.h"



// Adding one state without removing the previous state:
void Game_state_machine::Push_state( Game_states_blueprint* state_ptr )
{
  m_states_vec.push_back( state_ptr );
  m_states_vec.back()->on_Enter();
}



// Removing one state and adding another:
void Game_state_machine::Change_state( Game_states_blueprint* state_ptr )
{
  if( ! m_states_vec.empty() )
    {
      if( m_states_vec.back()->Get_state_id() == state_ptr->Get_state_id() )
	return;

      if( m_states_vec.back()->on_Exit() )
	{
	  delete m_states_vec.back();
	  m_states_vec.pop_back();
	}
    }
  m_states_vec.push_back( state_ptr );
  m_states_vec.back()->on_Enter();
}



// Removing one state without adding another:
void Game_state_machine::Pop_state()
{
  if( ! m_states_vec.empty() )
    {
      if( m_states_vec.back()->on_Exit() )
	{
	  delete m_states_vec.back();
	  m_states_vec.pop_back();
	}
    }
}



void Game_state_machine::Update()
{
  if( ! m_states_vec.empty() )
    {
      m_states_vec.back()->Update();
    }
}



void Game_state_machine::Render()
{
  if( ! m_states_vec.empty() )
    {
      m_states_vec.back()->Render();
    }
}



void Game_state_machine::Clean()
{
  // Deleting states:
  for ( int i = 0 ; i < m_states_vec.size() ; ++i ) {
    m_states_vec[i]->on_Exit();
    delete m_states_vec[i];
    m_states_vec[i] = NULL;
  }
  m_states_vec.clear();
}
