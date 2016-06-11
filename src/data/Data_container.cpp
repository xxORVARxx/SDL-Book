
#include "Data_container.h"



namespace data
{
  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const int _value )
  {
    tu.type.i = _value;
    tu.type_id = 1;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const long int _value )
  {
    tu.type.li = _value;
    tu.type_id = 2;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const unsigned _value )
  {
    tu.type.u = _value;
    tu.type_id = 3;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const long unsigned _value )
  {
    tu.type.lu = _value;
    tu.type_id = 4;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const float _value )
  {
    tu.type.f = _value;
    tu.type_id = 5;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const double _value )
  {
    tu.type.d = _value;
    tu.type_id = 6;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const long double _value )
  {
    tu.type.ld = _value;
    tu.type_id = 7;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const bool _value )
  {
    tu.type.b = _value;
    tu.type_id = 8;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const char _value )
  {
    tu.type.c = _value;
    tu.type_id = 9;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const signed char _value )
  {
    tu.type.c = _value;
    tu.type_id = 10;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const unsigned char _value )
  {
    tu.type.c = _value;
    tu.type_id = 11;
  }

  void 
  Container::Container_add_type( data::Type_union& tu, 
				 const xx::String_cast _value )
  {
    tu.s = _value;
    tu.type.i = 0;
    tu.type_id = 12;
  }
}//data



namespace data
{
  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const int _value )
  {
    if( tu.type_id != 1 )
      return false;
    tu.type.i = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const long int _value )
  {
    if( tu.type_id != 2 )
      return false;
    tu.type.li = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const unsigned _value )
  {
    if( tu.type_id != 3 )
      return false;
    tu.type.u = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const long unsigned _value )
  {
    if( tu.type_id != 4 )
      return false;
    tu.type.lu = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const float _value )
  {
    if( tu.type_id != 5 )
      return false;
    tu.type.f = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const double _value )
  {
    if( tu.type_id != 6 )
      return false;
    tu.type.d = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const long double _value )
  {
    if( tu.type_id != 7 )
      return false;
    tu.type.ld = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const bool _value )
  {
    if( tu.type_id != 8 )
      return false;
    tu.type.b = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const char _value )
  {
    if( tu.type_id != 9 )
      return false;
    tu.type.c = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const signed char _value )
  {
    if( tu.type_id != 10 )
      return false;
    tu.type.c = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const unsigned char _value )
  {
    if( tu.type_id != 11 )
      return false;
    tu.type.c = _value;
    return true;
  }

  bool 
  Container::Container_set_type( data::Type_union& tu, 
				 const xx::String_cast _value )
  {
    if( tu.type_id != 12 )
      return false;
    tu.s = _value;
    return true;
  }
}//data



namespace data
{
  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 int& _value ) const
  {
    if( tu.type_id != 1 )
      return false;
    _value = tu.type.i;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 long int& _value ) const
  {
    if( tu.type_id != 2 )
      return false;
    _value = tu.type.li;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 unsigned& _value ) const
  {
    if( tu.type_id != 3 )
      return false;
    _value = tu.type.u;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 long unsigned& _value ) const
  {
    if( tu.type_id != 4 )
      return false;
    _value = tu.type.lu;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 float& _value ) const
  {
    if( tu.type_id != 5 )
      return false;
    _value = tu.type.f;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 double& _value ) const
  {
    if( tu.type_id != 6 )
      return false;
    _value = tu.type.d;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 long double& _value ) const
  {
    if( tu.type_id != 7 )
      return false;
    _value = tu.type.ld;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 bool& _value ) const
  {
    if( tu.type_id != 8 )
      return false;
    _value = tu.type.b;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 char& _value ) const
  {
    if( tu.type_id != 9 )
      return false;
    _value = tu.type.c;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 signed char& _value ) const
  {
    if( tu.type_id != 10 )
      return false;
    _value = tu.type.c;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 unsigned char& _value ) const
  {
    if( tu.type_id != 11 )
      return false;
    _value = tu.type.c;
    return true;
  }

  bool 
  Container::Container_get_type( const data::Type_union& tu, 
				 xx::String_cast& _value ) const
  {
    if( tu.type_id != 12 )
      return false;
    _value = tu.s;
    return true;
  }
}//data
