 
#ifndef DATA_CONTAINER_H
#define DATA_CONTAINER_H

#include "Init.h"
#include <unordered_map>
#include "xx_String_cast.h"



namespace data
{
  struct Type_union
  {
    int type_id = 0;
    union 
    {
      int i; //             id: 1
      long int li; //       id: 2
      unsigned u; //        id: 3
      long unsigned lu; //  id: 4
      float f; //           id: 5
      double d; //          id: 6
      long double ld; //    id: 7
      bool b; //            id: 8
      char c; //            id: 9
    } type;
    xx::String_cast s; //   id: 10
  };
}//data



namespace data
{
  class Container
  {
  public:
    // --- Functions ---

    template< typename T >
    void Add( const std::string _name, const T _value )
    {
      if( m_container_map.count( _name ) != 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When ADDING a value to the container. The name: '" + _name + "' is allready in use! " );
      data::Type_union tu;
      this->Container_add_type( tu, _value );
      m_container_map[ _name ] = tu;
    }

    template< typename T >
    void Set( const std::string _name, const T _value )
    {
      if( m_container_map.count( _name ) == 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When SETTING a value: No value with the name: '" + _name + "' is in the container! " );
      if( ! this->Container_set_type( m_container_map[ _name ], _value ))
	throw std::invalid_argument( "(xx) Parsing ERROR! When SETTING a value with the name: '" + _name + "'. Variables types do not match! " );
    }

    template< typename T >
    void Get( const std::string _name, T& _value )
    {
      if( m_container_map.count( _name ) == 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When GETTING a value: No value with the name: '" + _name + "' is in the container! " );
      if( ! this->Container_get_type( m_container_map[ _name ], _value ))
	throw std::invalid_argument( "(xx) Parsing ERROR! When GETTING a value with the name: '" + _name + "'. Variables types do not match! " );
    }

    template< typename T >
    void Take( const std::string _name, T& _value )
    {
      if( m_container_map.count( _name ) == 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When TAKING a value: No value with the name: '" + _name + "' is in the container! " );
      if( ! this->Container_get_type( m_container_map[ _name ], _value ))
	throw std::invalid_argument( "(xx) Parsing ERROR! When TAKING a value with the name: '" + _name + "'. Variables types do not match! " );
      m_container_map.erase( _name );
    }

    void Erase( const std::string _name )
    {
      if( m_container_map.erase( _name ) == 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When ERASING a value. No value with the name: '" + _name + "' is in the container! " );
    }

    bool Has( const std::string _name ) const
    {
      if( m_container_map.count( _name ) == 0 )
	return false;
      return true;
    }

  private:
    void Container_add_type( data::Type_union& tu, const int _value );
    void Container_add_type( data::Type_union& tu, const long int _value );
    void Container_add_type( data::Type_union& tu, const unsigned _value );
    void Container_add_type( data::Type_union& tu, const long unsigned _value );
    void Container_add_type( data::Type_union& tu, const float _value );
    void Container_add_type( data::Type_union& tu, const double _value );
    void Container_add_type( data::Type_union& tu, const long double _value );
    void Container_add_type( data::Type_union& tu, const bool _value );
    void Container_add_type( data::Type_union& tu, const char _value );
    void Container_add_type( data::Type_union& tu, const xx::String_cast _value );

    bool Container_set_type( data::Type_union& tu, const int _value );
    bool Container_set_type( data::Type_union& tu, const long int _value );
    bool Container_set_type( data::Type_union& tu, const unsigned _value );
    bool Container_set_type( data::Type_union& tu, const long unsigned _value );
    bool Container_set_type( data::Type_union& tu, const float _value );
    bool Container_set_type( data::Type_union& tu, const double _value );
    bool Container_set_type( data::Type_union& tu, const long double _value );
    bool Container_set_type( data::Type_union& tu, const bool _value );
    bool Container_set_type( data::Type_union& tu, const char _value );
    bool Container_set_type( data::Type_union& tu, const xx::String_cast _value );

    bool Container_get_type( const data::Type_union& tu, int& _value ) const;
    bool Container_get_type( const data::Type_union& tu, long int& _value ) const;
    bool Container_get_type( const data::Type_union& tu, unsigned& _value ) const;
    bool Container_get_type( const data::Type_union& tu, long unsigned& _value ) const;
    bool Container_get_type( const data::Type_union& tu, float& _value ) const;
    bool Container_get_type( const data::Type_union& tu, double& _value ) const;
    bool Container_get_type( const data::Type_union& tu, long double& _value ) const;
    bool Container_get_type( const data::Type_union& tu, bool& _value ) const;
    bool Container_get_type( const data::Type_union& tu, char& _value ) const;
    bool Container_get_type( const data::Type_union& tu, xx::String_cast& _value ) const;

    // --- Variables ---
    std::unordered_map< std::string, data::Type_union > m_container_map;
  } static container;
}//Data



#endif
