
#include "Init.h"



template< typename T >
Type_e What_type()
{
  return Type_e::VOID;
}

template<>
Type_e What_type< byte_t >()
{
  return Type_e::BYTE;
}

template<>
Type_e What_type< integer_t >()
{
  return Type_e::INTEGER;
}

template<>
Type_e What_type< real_t >()
{
  return Type_e::REAL;
}

template<>
Type_e What_type< string_t >()
{
  return Type_e::STRING;
}



template Type_e What_type< byte_t >();
template Type_e What_type< integer_t >();
template Type_e What_type< real_t >();
template Type_e What_type< string_t >();
