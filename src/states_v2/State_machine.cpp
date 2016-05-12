
#include "State_machine.h"



void
State_machine::To_do( SMF_parameters function )
{
  m_todo_list.push_back( function );
}

void
State_machine::Flush()
{
  for( auto itr = m_todo_list.begin() ; itr != m_todo_list.end() ; ++itr )
    {
      switch( (*itr).function )
	{
	  // Create States:
	case SMF::CREATE_AT_FRONT:
	  this->Put_at_front( this->Create_state( (*itr).filename ));
	  break;
	case SMF::CREATE_FRONT_OF:
	  this->Put_front_of( this->Create_state( (*itr).filename ), (*itr).destination_id );
	  break;
	case SMF::CREATE_BEHIND_OF:
	  this->Put_behind_of( this->Create_state( (*itr).filename ), (*itr).destination_id );
	  break;
	case SMF::CREATE_AT_BACK:
	  this->Put_at_back( this->Create_state( (*itr).filename ));
	  break;
	  // Load States:
	case SMF::LOAD_AT_FRONT:
	  this->Put_at_front( this->Load_state( (*itr).filename ));
	  break;
	case SMF::LOAD_FRONT_OF:
	  this->Put_front_of( this->Load_state( (*itr).filename ), (*itr).destination_id );
	  break;
	case SMF::LOAD_BEHIND_OF:
	  this->Put_behind_of( this->Load_state( (*itr).filename ), (*itr).destination_id );
	  break;
	case SMF::LOAD_AT_BACK:
	  this->Put_at_back( this->Load_state( (*itr).filename ));
	  break;
	  // Move States:
	case SMF::MOVE_TO_FRONT:
	  this->Move_to_front( (*itr).id );
	  break;
	case SMF::MOVE_FORWARD:
	  this->Move_forward( (*itr).id );
	  break;
	case SMF::MOVE_FRONT_OF:
	  this->Move_front_of( (*itr).id, (*itr).destination_id );
	  break;
	case SMF::MOVE_BEHIND_OF:
	  this->Move_behind_of( (*itr).id, (*itr).destination_id );
	  break;
	case SMF::MOVE_BACKWARD:
	  this->Move_backward( (*itr).id );
	  break;
	case SMF::MOVE_TO_BACK:
	  this->Move_to_back( (*itr).id );
	  break;
	  // Remove States:
	case SMF::REMOVE:
	  this->Remove( (*itr).id );
	  break;
	case SMF::REMOVE_FRONT:
	  this->Remove_front();
	  break;
	case SMF::REMOVE_BACK:
	  this->Remove_back();
	  break;
	case SMF::REMOVE_ALL:
	  this->Remove_all();
	  break;

	default:
	  throw std::invalid_argument( "(xx) State Machine ERROR! when Flush-ing. " );
	}//switch
    }//for
  m_todo_list.clear();
}



void
State_machine::Update()
{
  for( auto& state_ptr : m_state_vec )
    state_ptr->Update();
}

void
State_machine::Render()
{
  for( auto& state_ptr : m_state_vec )
    state_ptr->Render();
}

void
State_machine::Clean()
{
  for( auto& state_ptr : m_state_vec )
    {
      state_ptr->Clean();
      delete state_ptr;
    }
  m_state_vec.clear();
  std::cout << "STATE MACHINE :: Clean() is done.\n";
}



bool
State_machine::Has_state( const std::string _id, 
			  State* _state ) const
{
  for( auto& state_ptr : m_state_vec )
    if( state_ptr->Get_id() == _id )
      {
	_state = state_ptr;
	return true;
      }
  return false;
}



State* 
State_machine::Create_state( const std::string& _filename )
{
  State* state_ptr = new State( _filename );
  state_ptr->Create();
  if( this->Find( state_ptr->Get_id()) != m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! When CREATING a State. The name-id: '" + state_ptr->Get_id() + "' is allready in use! " );
  return state_ptr;
}

State* 
State_machine::Load_state( const std::string& _filename )
{
  State* state_ptr = new State( _filename );
  state_ptr->Load();
  if( this->Find( state_ptr->Get_id()) == m_state_vec.end())
    return state_ptr;
  throw std::invalid_argument( "(xx) State Machine ERROR! When LOADING a State. The name-id: '" + state_ptr->Get_id() + "' is allready in use! " );
}



void
State_machine::Put_at_front( State* _state_ptr )
{
  m_state_vec.push_back( _state_ptr );
}

void
State_machine::Put_front_of( State* _state_ptr, 
			     const std::string& _id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _id + "'! " );
  m_state_vec.insert( ++itr, _state_ptr );
}

void
State_machine::Put_behind_of( State* _state_ptr, 
			      const std::string& _id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _id + "'! " );
  m_state_vec.insert( itr, _state_ptr );
}

void
State_machine::Put_at_back( State* _state_ptr )
{
  m_state_vec.insert( m_state_vec.begin(), _state_ptr );
}



void
State_machine::Move_to_front( const std::string& _id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _id + "'! " );
  if( (itr+1) == m_state_vec.end())
    return;
  State* state_ptr = *itr;
  m_state_vec.erase( itr );
  m_state_vec.push_back( state_ptr );
}

void
State_machine::Move_forward( const std::string& _id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _id + "'! " );
  if( (itr+1) == m_state_vec.end())
    return;
  std::swap( *itr, *(itr+1) );
}

void
State_machine::Move_front_of( const std::string& _id, 
			      const std::string& _destination_id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _id + "'! " );
  auto destination_itr = this->Find( _destination_id );
  if( destination_itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _destination_id + "'! " );
  if(( itr == destination_itr )||( (itr-1) == destination_itr ))
    return;
  m_state_vec.insert( ++destination_itr, *itr );
  itr = this->Find( _id ); // Iterators not valid after insertion.
  m_state_vec.erase( itr );
}

void
State_machine::Move_behind_of( const std::string& _id, 
			       const std::string& _destination_id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _id + "'! " );
  auto destination_itr = this->Find( _destination_id );
  if( destination_itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _destination_id + "'! " );
  if(( itr == destination_itr )||( (itr+1) == destination_itr ))
    return;
  m_state_vec.insert( destination_itr, *itr );
  itr = this->Find( _id ); // Iterators not valid after insertion.
  m_state_vec.erase( itr );
}

void
State_machine::Move_backward( const std::string& _id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _id + "'! " );
  if( itr == m_state_vec.begin())
    return;
  std::swap( *itr, *(itr-1) );
}

void
State_machine::Move_to_back( const std::string& _id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! No state with the name-id: '" + _id + "'! " );
  if( itr == m_state_vec.begin())
    return;
  State* state_ptr = *itr;
  m_state_vec.erase( itr );
  m_state_vec.insert( m_state_vec.begin(), state_ptr );
}



void
State_machine::Remove( const std::string& _id )
{
  auto itr = this->Find( _id );
  if( itr == m_state_vec.end())
    throw std::invalid_argument( "(xx) State Machine ERROR! When REMOVING state. No state with the name-id: '" + _id + "'! " );
  (*itr)->Clean();
  delete *itr;
  m_state_vec.erase( itr );
}

void
State_machine::Remove_front()
{
  if( m_state_vec.empty())
    throw std::invalid_argument( "(xx) State Machine ERROR! When REMOVING. No states! " );
  m_state_vec.back()->Clean();
  delete m_state_vec.back();
  m_state_vec.pop_back();
}

void
State_machine::Remove_back()
{
  if( m_state_vec.empty())
    throw std::invalid_argument( "(xx) State Machine ERROR! When REMOVING. No states! " );
  m_state_vec.front()->Clean();
  delete m_state_vec.front();
  m_state_vec.erase( m_state_vec.begin());
}

void
State_machine::Remove_all()
{
  for( auto& state_ptr : m_state_vec )
    {
      state_ptr->Clean();
      delete state_ptr;
    }
  m_state_vec.clear();
}



std::vector< State* >::iterator
State_machine::Find( const std::string _id )
{
  for( auto itr = m_state_vec.begin() ; itr != m_state_vec.end() ; ++itr )
    if( (*itr)->Get_id() == _id )
      return itr;
  return m_state_vec.end();
}
