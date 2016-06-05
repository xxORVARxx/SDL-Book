
#include "Event_functions.h"



namespace event 
{
  template< typename T >
  event::Type Get_type()
  {
    return event::Type::VOID;
  }

  template<>
  event::Type Get_type< byte_t >()
  {
    return event::Type::BYTE;
  }

  template<>
  event::Type Get_type< integer_t >()
  {
    return event::Type::INTEGER;
  }

  template<>
  event::Type Get_type< real_t >()
  {
    return event::Type::REAL;
  }

  template<>
  event::Type Get_type< string_t >()
  {
    return event::Type::STRING;
  }
}//event



namespace event 
{
  template< typename T > 
  event::Parameter_base< T >* Make_parameter( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p )
  {
    std::string parameter_type = std::string( _p->Parse_file< xx::String_cast >( _file ));

    if( parameter_type == "Constant_value" )
      {
        event::Parameter_variable< T >* variable_ptr = new event::Parameter_variable< T >();
	T value = _p->Parse_file< T >( _file );
	variable_ptr->Set( value );
	std::cout <<"-----------------"<< (int)variable_ptr->Get() <<"\n";
	return variable_ptr;
      }
    else if( parameter_type == "Trigger_variable_1" )
      {
	assert( event::Get_type< T >() == _trigger_ptr->Get_variable_1()->Type() );//ASSERT.
	return dynamic_cast< event::Parameter_variable< T >* >( _trigger_ptr->Get_variable_1() );
      }
    else if( parameter_type == "Trigger_Variable_2" )
      {
	assert( event::Get_type< T >() == _trigger_ptr->Get_variable_2()->Type() );//ASSERT.
	return dynamic_cast< event::Parameter_variable< T >* >( _trigger_ptr->Get_variable_2() );
      }
    else if( parameter_type == "Add" )
      {
	return new Parameter_add< T >( _trigger_ptr, _file, _p );
      }
    else
      throw std::invalid_argument( "(xx) Parsing ERROR! When making event's parameter: '" + parameter_type + "', corrupted input from file! " );
  }
}//event



namespace event 
{
  template event::Type Get_type< byte_t >();
  template event::Type Get_type< integer_t >();
  template event::Type Get_type< real_t >();
  template event::Type Get_type< string_t >();

  template event::Parameter_base< byte_t >* Make_parameter( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );
  template event::Parameter_base< integer_t >* Make_parameter( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );
  template event::Parameter_base< real_t >* Make_parameter( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );
  template event::Parameter_base< string_t >* Make_parameter( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );
}//event 
