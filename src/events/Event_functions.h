
#ifndef EVENT_FUNCTIONS_H
#define EVENT_FUNCTIONS_H

#include "Parser.h"

namespace event{ class i_Trigger; }
namespace event{ template< typename T > class Parameter_base; }



namespace event
{
  template< typename T1 > 
  struct Parameater
  {
    Parameater()
      : m_owner(true), m_deleted(std::make_shared<bool>(false)), m_parameter_ptr(nullptr) {}

    Parameater( bool _owner, event::Parameter_base< T1 >* _parameter_ptr ) 
      : m_owner(_owner), m_deleted(std::make_shared<bool>(false)), m_parameter_ptr(_parameter_ptr) {}

    Parameater( Parameater&& _p )
      : m_owner(true), m_deleted(nullptr), m_parameter_ptr(nullptr)
    { 
      m_owner = _p.m_owner;  
      m_deleted = _p.m_deleted;  
      m_parameter_ptr = _p.m_parameter_ptr;
      _p.m_owner = false;
      _p.m_deleted = nullptr;
      _p.m_parameter_ptr = nullptr;
    }

    ~Parameater()
    {
      if( m_owner )
	{
	  delete m_parameter_ptr;
	  *m_deleted = true;
	}
    }

    Parameater& operator=( Parameater&& _p )
    {
      if( this != &_p )
	{
	  if( m_owner )
	    delete m_parameter_ptr;
	  m_owner = _p.m_owner;  
	  m_deleted = _p.m_deleted;  
	  m_parameter_ptr = _p.m_parameter_ptr;
	  _p.m_owner = false;
	  _p.m_deleted = nullptr;
	  _p.m_parameter_ptr = nullptr;
	}
      return *this;
    }

    T1 operator()()
    {
      return m_parameter_ptr->Get();
    }

    // --- Functions ---
    bool Good()
    {
      return(( ! *m_deleted )&&( m_parameter_ptr ));
    }

    // --- Variables ---
    bool m_owner;
    std::shared_ptr< bool > m_deleted;
    event::Parameter_base< T1 >* m_parameter_ptr;
  };
}//event



namespace event
{
  template< typename T1 > 
  using Return_function_t = event::Parameater< T1 >(& /*Func_ref*/)( event::i_Trigger*, std::ifstream&, data::Parser* );

  template< typename T1 > 
  event::Return_function_t< T1 > Get_function( std::string& _function );
}//event



namespace event
{
  template< typename T1 > 
  event::Parameater< T1 > Constant_value( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 > 
  event::Parameater< T1 > Trigger_variable_1( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 > 
  event::Parameater< T1 > Trigger_variable_2( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 > 
  event::Parameater< T1 > Add( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 > 
  event::Parameater< T1 > Subtract( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 > 
  event::Parameater< T1 > Is_equal( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 > 
  event::Parameater< T1 > Convert_to_byte( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 >
  event::Parameater< T1 > Convert_to_integer( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 >
  event::Parameater< T1 > Convert_to_real( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );

  template< typename T1 >
  event::Parameater< T1 > Convert_to_string( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );
}//event



namespace event 
{
  // Event-Parameter Interface:
  struct i_Parameter
  {
    i_Parameter( const Type_e _type ) 
      : m_type(_type) {}
    virtual ~i_Parameter() {}
    virtual bool Owner() = 0;
    virtual Type_e Type() { return m_type; }
  protected:
    const Type_e m_type;
  };



  template< typename T >
  struct Parameter_base : public i_Parameter
  {
    Parameter_base() 
      : i_Parameter(What_type<T>()) {}
    virtual ~Parameter_base() {}
    virtual bool Owner() { return true; }
    virtual Type_e Type() { return i_Parameter::m_type; }
    virtual T Get() = 0;
  };



  template< typename T >
  struct Parameter_variable : public Parameter_base< T >
  {
    Parameter_variable( bool _owner ) : m_owner(_owner) {}
    virtual ~Parameter_variable() {}
    virtual bool Owner() { return m_owner; }
    virtual Type_e Type() { return i_Parameter::m_type; }
    virtual T Get() { return m_value; }
    void Set( T _value ) { m_value = _value; }
  protected:
    bool m_owner;
    T m_value;
  };



  template< typename T1, typename T2 >
  struct Parameter_operator : public Parameter_base< T1 >
  {
    Parameter_operator( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p, std::function< T1(T2,T2) > _Operation )
      : m_Operation(_Operation)
    {
      auto local_function = _p->Parse_file< event::Return_function_t< T2 > >( _file, event::Get_function );
      m_parameter_1 = local_function( _trigger_ptr, _file, _p );

      local_function = _p->Parse_file< event::Return_function_t< T2 > >( _file, event::Get_function );
      m_parameter_2 = local_function( _trigger_ptr, _file, _p );
    }
    virtual ~Parameter_operator() {}
    virtual bool Owner() { return true; }
    virtual Type_e Type() { return i_Parameter::m_type; }
    virtual T1 Get() 
    { 
      assert( m_parameter_1.Good());//ASSERT.
      assert( m_parameter_2.Good());//ASSERT.
      return m_Operation( m_parameter_1(), m_parameter_2()); 
    }
  protected:
    std::function< T1(T2,T2) > m_Operation;
    event::Parameater< T2 > m_parameter_1;
    event::Parameater< T2 > m_parameter_2;
  };



  template< typename T1, typename T2 >
  struct Parameter_convert : public Parameter_base< T1 >
  {
    Parameter_convert( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p )
    {
      auto local_function = _p->Parse_file< event::Return_function_t< T2 > >( _file, event::Get_function );
      m_parameter = local_function( _trigger_ptr, _file, _p );
    }
    virtual ~Parameter_convert() {}
    virtual bool Owner() { return true; }
    virtual Type_e Type() { return i_Parameter::m_type; }
    virtual T1 Get()
    {
      assert( m_parameter.Good());//ASSERT.
      return (T1)(m_parameter());
    }
  protected:
    event::Parameater< T2 > m_parameter;
  };
}//event



#include "Event_link.h"
#include "Event_hook.h"
#include "Event_trigger.h"



#endif
