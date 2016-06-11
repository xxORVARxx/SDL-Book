
#include "Events_manager.h"



namespace event
{
  template< typename T1 > 
  event::Return_function_t< T1 >
  Get_function( std::string& _function )
  {
    if( _function == "Constant_value()R" )
      return event::Constant_value< T1 >;
    else if( _function == "Trigger_variable_1()" )
      return event::Trigger_variable_1< T1 >;
    else if( _function == "Trigger_Variable_2()" )
      return event::Trigger_variable_2< T1 >;
    else if( _function == "Add(LL)" )
      return event::Add< T1 >;
    else if( _function == "Subtract(LL)" )
      return event::Subtract< T1 >;
    else if( _function == "Is_equal(LL)" )
      return event::Is_equal< T1 >;
    else if( _function == "Convert_to_byte(L)" )
      return event::Convert_to_byte< T1 >;
    else if( _function == "Convert_to_integer(L)" )
      return event::Convert_to_integer< T1 >;
    else if( _function == "Convert_to_real(L)" )
      return event::Convert_to_real< T1 >;
    else if( _function == "Convert_to_string(L)" )
      return event::Convert_to_string< T1 >;
    else
      throw std::invalid_argument( "(xx) Parsing ERROR! When making Event. Local-function not found: '" + _function + "'. Corrupted input from file! " ); ;
  }
}//event



namespace event
{
  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Constant_value( event::i_Trigger* _trigger_ptr, 
		  std::ifstream& _file,
		  data::Parser* _p )
  {
    event::Parameter_variable< T1 >* variable_ptr = new event::Parameter_variable< T1 >();
    T1 value = _p->Parse_file< T1 >( _file );
    variable_ptr->Set( value );
    return variable_ptr;
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Trigger_variable_1( event::i_Trigger* _trigger_ptr,
		      std::ifstream& _file, 
		      data::Parser* _p )
  {
    assert( What_type< T1 >() == _trigger_ptr->Get_variable_1()->Type() );//ASSERT.
    return dynamic_cast< event::Parameter_variable< T1 >* >( _trigger_ptr->Get_variable_1() );
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Trigger_variable_2( event::i_Trigger* _trigger_ptr,
		      std::ifstream& _file, data::Parser* _p )
  {
    assert( What_type< T1 >() == _trigger_ptr->Get_variable_2()->Type() );//ASSERT.
    return dynamic_cast< event::Parameter_variable< T1 >* >( _trigger_ptr->Get_variable_2() );
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Add( event::i_Trigger* _trigger_ptr,
       std::ifstream& _file,
       data::Parser* _p )
  {
    return new Parameter_operator< T1, T1 >( _trigger_ptr, _file, _p, []( T1 a, T1 b ) ->T1 { return a + b; } );
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Subtract( event::i_Trigger* _trigger_ptr,
	    std::ifstream& _file,
	    data::Parser* _p )
  {
    return new Parameter_operator< T1, T1 >( _trigger_ptr, _file, _p, []( T1 a, T1 b ) ->T1 { return a - b; } );
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Is_equal( event::i_Trigger* _trigger_ptr,
	    std::ifstream& _file,
	    data::Parser* _p )
  {
    return new Parameter_operator< T1, byte_t >( _trigger_ptr, _file, _p, []( T1 a, T1 b ) ->T1 { return ( a == b ); } );
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Convert_to_byte( event::i_Trigger* _trigger_ptr,
		   std::ifstream& _file,
		   data::Parser* _p )
  {
    return new Parameter_convert< T1, byte_t >( _trigger_ptr, _file, _p );
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Convert_to_integer( event::i_Trigger* _trigger_ptr,
		      std::ifstream& _file,
		      data::Parser* _p )
  {
    return new Parameter_convert< T1, integer_t >( _trigger_ptr, _file, _p );
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Convert_to_real( event::i_Trigger* _trigger_ptr,
		   std::ifstream& _file,
		   data::Parser* _p )
  {
    return new Parameter_convert< T1, real_t >( _trigger_ptr, _file, _p );
  }



  template< typename T1 > 
  event::Parameter_base< T1 >* 
  Convert_to_string( event::i_Trigger* _trigger_ptr,
		     std::ifstream& _file,
		     data::Parser* _p )
  {
    return new Parameter_convert< T1, string_t >( _trigger_ptr, _file, _p );
  }
}//event



template event::Return_function_t< byte_t > event::Get_function< byte_t >( std::string& );
template event::Return_function_t< integer_t > event::Get_function< integer_t >( std::string& );
template event::Return_function_t< real_t > event::Get_function< real_t >( std::string& );
template event::Return_function_t< string_t > event::Get_function< string_t >( std::string& );
