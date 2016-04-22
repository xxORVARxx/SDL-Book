
#include "Data_container.h"



namespace data
{
  void 
  Container::Container_add_type( const int _value, 
				 data::Type_union& tu )
  {
    tu.type.i = _value;
    tu.type_id = 1;
  }

  void 
  Container::Container_add_type( const long int _value, 
				 data::Type_union& tu )
  {
    tu.type.li = _value;
    tu.type_id = 2;
  }

  void 
  Container::Container_add_type( const unsigned _value, 
				 data::Type_union& tu )
  {
    tu.type.u = _value;
    tu.type_id = 3;
  }

  void 
  Container::Container_add_type( const long unsigned _value, 
				 data::Type_union& tu )
  {
    tu.type.lu = _value;
    tu.type_id = 4;
  }

  void 
  Container::Container_add_type( const float _value, 
				 data::Type_union& tu )
  {
    tu.type.f = _value;
    tu.type_id = 5;
  }

  void 
  Container::Container_add_type( const double _value, 
				 data::Type_union& tu )
  {
    tu.type.d = _value;
    tu.type_id = 6;
  }

  void 
  Container::Container_add_type( const long double _value, 
				 data::Type_union& tu )
  {
    tu.type.ld = _value;
    tu.type_id = 7;
  }

  void 
  Container::Container_add_type( const bool _value, 
				 data::Type_union& tu )
  {
    tu.type.b = _value;
    tu.type_id = 8;
  }

  void 
  Container::Container_add_type( const char _value, 
				 data::Type_union& tu )
  {
    tu.type.c = _value;
    tu.type_id = 9;
  }

  void 
  Container::Container_add_type( const xx::String_cast _value, 
				 data::Type_union& tu )
  {
    tu.s = _value;
    tu.type.i = 0;
    tu.type_id = 10;
  }
}//data



namespace data
{
  bool 
  Container::Container_set_type( const int _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 1 )
      return false;
    tu.type.i = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const long int _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 2 )
      return false;
    tu.type.li = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const unsigned _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 3 )
      return false;
    tu.type.u = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const long unsigned _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 4 )
      return false;
    tu.type.lu = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const float _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 5 )
      return false;
    tu.type.f = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const double _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 6 )
      return false;
    tu.type.d = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const long double _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 7 )
      return false;
    tu.type.ld = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const bool _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 8 )
      return false;
    tu.type.b = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const char _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 9 )
      return false;
    tu.type.c = _value;
    return true;
  }

  bool 
  Container::Container_set_type( const xx::String_cast _value, 
				 data::Type_union& tu )
  {
    if( tu.type_id != 10 )
      return false;
    tu.s = _value;
    return true;
  }
}//data



namespace data
{
  bool 
  Container::Container_get_type( int& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 1 )
      return false;
    _value = tu.type.i;
    return true;
  }

  bool 
  Container::Container_get_type( long int& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 2 )
      return false;
    _value = tu.type.li;
    return true;
  }

  bool 
  Container::Container_get_type( unsigned& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 3 )
      return false;
    _value = tu.type.u;
    return true;
  }

  bool 
  Container::Container_get_type( long unsigned& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 4 )
      return false;
    _value = tu.type.lu;
    return true;
  }

  bool 
  Container::Container_get_type( float& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 5 )
      return false;
    _value = tu.type.f;
    return true;
  }

  bool 
  Container::Container_get_type( double& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 6 )
      return false;
    _value = tu.type.d;
    return true;
  }

  bool 
  Container::Container_get_type( long double& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 7 )
      return false;
    _value = tu.type.ld;
    return true;
  }

  bool 
  Container::Container_get_type( bool& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 8 )
      return false;
    _value = tu.type.b;
    return true;
  }

  bool 
  Container::Container_get_type( char& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 9 )
      return false;
    _value = tu.type.c;
    return true;
  }

  bool 
  Container::Container_get_type( xx::String_cast& _value, 
				 const data::Type_union& tu ) const
  {
    if( tu.type_id != 10 )
      return false;
    _value = tu.s;
    return true;
  }
}//data
