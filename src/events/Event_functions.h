
#ifndef EVENT_FUNCTIONS_H
#define EVENT_FUNCTIONS_H

#include "Init.h"
#include "Parser.h"
#include "xx_String_cast.h"

using byte_t = char;
using integer_t = long int;
using real_t = double;
using string_t = xx::String_cast;



namespace event 
{ 
  enum class Type
  {
      VOID,
      BYTE,
      INTEGER,
      REAL,
      STRING
  };
}//event



namespace event{ template< typename T > struct Parameter_base; }
namespace event{ class i_Trigger; }



namespace event 
{
  template< typename T > 
  event::Type Get_type();



  template< typename T > 
  event::Parameter_base< T >* Make_parameter( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p );
}//event



namespace event 
{
  // Event-Parameter Interface:
  struct i_Parameter
  {
    i_Parameter( const event::Type _type ) 
      : m_type(_type) {}
    virtual ~i_Parameter() {}
    virtual event::Type Type() { return m_type; }
  protected:
    const event::Type m_type;
  };



  template< typename T >
  struct Parameter_base : public i_Parameter
  {
    Parameter_base() 
      : i_Parameter(event::Get_type<T>()) {}
    virtual ~Parameter_base() {}
    virtual event::Type Type() { return i_Parameter::m_type; }
    virtual T Get() = 0;
  };



  template< typename T >
  struct Parameter_variable : public Parameter_base< T >
  {
    virtual ~Parameter_variable() {}
    virtual event::Type Type() { return i_Parameter::m_type; }
    virtual T Get() { return m_value; }
    void Set( T _value ) { m_value = _value; }
  protected:
    T m_value;
  };



  template< typename T >
  struct Parameter_add : public Parameter_base< T >
  {
    Parameter_add( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p )
    {
      p1 = event::Make_parameter< T >( _trigger_ptr, _file, _p );
      p2 = event::Make_parameter< T >( _trigger_ptr, _file, _p );
    }
    virtual ~Parameter_add()
    {
      delete p1;
      delete p2;
    }
    virtual event::Type Type() { return i_Parameter::m_type; }
    virtual T Get() { return ( p1->Get() + p2->Get()); }
  protected:
    event::Parameter_base< T >* p1;
    event::Parameter_base< T >* p2;
  };
}//event



#include "Event_link.h"
#include "Event_hook.h"
#include "Event_trigger.h"



#endif
