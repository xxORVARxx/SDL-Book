
#ifndef EVENT_H
#define EVENT_H

#include "Init.h"

class Printer;



class Interface_event_hook
{
public:
  virtual ~Interface_event_hook() = 0;
  virtual void Set_parameter_1( void* _ptr ) = 0;
  virtual void Set_parameter_2( void* _ptr ) = 0;
  virtual void Callback() = 0;
};
inline Interface_event_hook::~Interface_event_hook() { }



template< class T_class, typename T_return >
class Event_hook_R : public Interface_event_hook
{
public:
  Event_hook_R( T_class* _class_ptr, T_return(Printer::*_function_ptr)() ) : 
    m_class_ptr(_class_ptr), m_callback_ptr(_function_ptr) {}
  virtual ~Event_hook_R() {}
  //void Set_object( T_class* _class_ptr ) { m_class_ptr = _class_ptr; }
  virtual void Callback()
  {
    if( m_class_ptr == nullptr )
      throw xx::Missing_argument( "(xx) Event Hook ERROR! The OBJECT which the callback function belongs to is missing! " );
    // Calling the Callback function:
    (m_class_ptr->*m_callback_ptr)();
  }
private:
  T_class* m_class_ptr;
  T_return(Printer::*m_callback_ptr)();
};



template< class T_class, typename T, typename T_return >
class Event_hook_TR : public Interface_event_hook
{
public:
  Event_hook_TR( T_class* _class_ptr, T_return(Printer::*_function_ptr)(T) ) : 
    m_class_ptr(_class_ptr), m_callback_ptr(_function_ptr), m_parameter_ptr_1(nullptr) {}
  virtual ~Event_hook_TR() {}
  //void Set_object( T_class* _class_ptr ) { m_class_ptr = _class_ptr; }
  virtual void Set_parameter_1( void* _parameter_ptr_1 ) { m_parameter_ptr_1 = _parameter_ptr_1; }
  virtual void Set_parameter_2( void* _parameter_ptr_2 ) {/* ERROR */}
  virtual void Callback()
  {
    if( m_class_ptr == nullptr )
      throw xx::Missing_argument( "(xx) Event Hook ERROR! The OBJECT which the callback function belongs to is missing! " );
    if( m_parameter_ptr_1 == nullptr )
      throw xx::Missing_argument( "(xx) Event Hook ERROR! PARAMETER number-1, for the callback function, is missing! " );
    // Calling the Callback function:
    (m_class_ptr->*m_callback_ptr)( *static_cast< T* >( m_parameter_ptr_1 ));
  }
private:
  T_class* m_class_ptr;
  void* m_parameter_ptr_1;
  T_return(Printer::*m_callback_ptr)(T);
};


/*
template< class T_class, typename T1, typename T2, typename T_return >
class Event_hook_TTR : public Interface_event_hook
{
public:
  Event_hook_TTR( T_class* _class_ptr, T_return(Printer::*_function_ptr)(T1,T2), T1* _para1, T2* _para2 );
  ~Event_hook_TTR() {}
  void Set_object( T_class* _class_ptr ) { m_class_ptr = _class_ptr; }
  virtual void operator()();
private:
  T_class* m_class_ptr;
  T1* m_para1;
  T2* m_para2;
  T_return(Printer::*m_callback_ptr)(T1,T2);
};
*/





class Interface_event_trigger
{
public:
  Interface_event_trigger() : m_hook_ptr(nullptr) {}
  virtual ~Interface_event_trigger() = 0;
  void Set_hook( Interface_event_hook* _hook_ptr ) { m_hook_ptr = _hook_ptr; }
  virtual void* Get_variable_A() = 0;
  virtual void* Get_variable_B() = 0;
  void operator()()
  {
    if( m_hook_ptr == nullptr )
      return;
    m_hook_ptr->Callback();
  }
private:
  Interface_event_hook* m_hook_ptr;
};
inline Interface_event_trigger::~Interface_event_trigger() {}



template< typename T >
class Event_trigger_T : public Interface_event_trigger
{
public:
  Event_trigger_T( T* _pointer_A ) : 
    m_pointer_A(_pointer_A) {}
  Event_trigger_T( T _constant_A ) : 
    m_constant_A(_constant_A), m_pointer_A(&m_constant_A) {}
  virtual ~Event_trigger_T() {}
  virtual void* Get_variable_A() { return m_pointer_A; }
  virtual void* Get_variable_B() { throw xx::Missing_argument( "(xx) Event Trigger ERROR! VARIABLE-B is not available for this trigger! " ); }
private:
  void* m_pointer_A;
  T m_constant_A;
};



template< typename T1, typename T2 >
class Event_trigger_TT : public Interface_event_trigger
{
public:
  Event_trigger_TT( T1* _pointer_A, T2* _pointer_B ) : 
    m_pointer_A(_pointer_A), m_pointer_B(_pointer_B) {}
  Event_trigger_TT( T1 _const_A, T2* _pointer_B ) : 
    m_constant_A(_const_A), m_pointer_A(&m_constant_A), m_pointer_B(_pointer_B) {}
  Event_trigger_TT( T1* _pointer_A, T2 _const_B ) : 
    m_pointer_A(_pointer_A), m_constant_B(_const_B), m_pointer_B(&m_constant_B) {}
  Event_trigger_TT( T1 _const_A, T2 _const_B ) : 
    m_constant_A(_const_A), m_pointer_A(&m_constant_A), m_constant_B(_const_B), m_pointer_B(&m_constant_B) {}
  virtual ~Event_trigger_TT() {}
  virtual void* Get_variable_A() { return m_pointer_A; }
  virtual void* Get_variable_B() { return m_pointer_B; }
private:
  void* m_pointer_A;
  void* m_pointer_B;
  T1 m_constant_A;
  T2 m_constant_B;
};



#endif
