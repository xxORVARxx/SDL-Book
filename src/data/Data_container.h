 
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

    template< typename T >
    void Add( const T _value, const std::string _name )
    {
      if( m_container_map.count( _name ) != 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When ADDING a value to the container. The name: '" + _name + "' is allready in use!" );
      data::Type_union tu;
      this->Container_add_type( _value, tu );
      m_container_map[ _name ] = tu;
    }

    template< typename T >
    void Set( const T _value, const std::string _name )
    {
      if( m_container_map.count( _name ) == 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When SETTING a value: No value with the name: '" + _name + "' is in the container!" );
      if( ! this->Container_set_type( _value, m_container_map[ _name ] ))
	throw std::invalid_argument( "(xx) Parsing ERROR! When SETTING a value with the name: '" + _name + "'. Variables types do not match!" );
    }

    template< typename T >
    void Get( T& _value, const std::string _name )
    {
      if( m_container_map.count( _name ) == 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When GETTING a value: No value with the name: '" + _name + "' is in the container!" );
      if( ! this->Container_get_type( _value, m_container_map[ _name ] ))
	throw std::invalid_argument( "(xx) Parsing ERROR! When GETTING a value with the name: '" + _name + "'. Variables types do not match!" );
    }

    template< typename T >
    void Take( T& _value, const std::string _name )
    {
      if( m_container_map.count( _name ) == 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When TAKING a value: No value with the name: '" + _name + "' is in the container!" );
      if( ! this->Container_get_type( _value, m_container_map[ _name ] ))
	throw std::invalid_argument( "(xx) Parsing ERROR! When TAKING a value with the name: '" + _name + "'. Variables types do not match!" );
      m_container_map.erase( _name );
    }

    void Erase( const std::string _name )
    {
      if( m_container_map.erase( _name ) == 0 )
	throw std::invalid_argument( "(xx) Parsing ERROR! When ERASING a value. No value with the name: '" + _name + "' is in the container!" );
    }

  private:
    void Container_add_type( const int _value, data::Type_union& tu );
    void Container_add_type( const long int _value, data::Type_union& tu );
    void Container_add_type( const unsigned _value, data::Type_union& tu );
    void Container_add_type( const long unsigned _value, data::Type_union& tu );
    void Container_add_type( const float _value, data::Type_union& tu );
    void Container_add_type( const double _value, data::Type_union& tu );
    void Container_add_type( const long double _value, data::Type_union& tu );
    void Container_add_type( const bool _value, data::Type_union& tu );
    void Container_add_type( const char _value, data::Type_union& tu );
    void Container_add_type( const xx::String_cast _value, data::Type_union& tu );

    bool Container_set_type( const int _value, data::Type_union& tu );
    bool Container_set_type( const long int _value, data::Type_union& tu );
    bool Container_set_type( const unsigned _value, data::Type_union& tu );
    bool Container_set_type( const long unsigned _value, data::Type_union& tu );
    bool Container_set_type( const float _value, data::Type_union& tu );
    bool Container_set_type( const double _value, data::Type_union& tu );
    bool Container_set_type( const long double _value, data::Type_union& tu );
    bool Container_set_type( const bool _value, data::Type_union& tu );
    bool Container_set_type( const char _value, data::Type_union& tu );
    bool Container_set_type( const xx::String_cast _value, data::Type_union& tu );

    bool Container_get_type( int& _value, const data::Type_union& tu ) const;
    bool Container_get_type( long int& _value, const data::Type_union& tu ) const;
    bool Container_get_type( unsigned& _value, const data::Type_union& tu ) const;
    bool Container_get_type( long unsigned& _value, const data::Type_union& tu ) const;
    bool Container_get_type( float& _value, const data::Type_union& tu ) const;
    bool Container_get_type( double& _value, const data::Type_union& tu ) const;
    bool Container_get_type( long double& _value, const data::Type_union& tu ) const;
    bool Container_get_type( bool& _value, const data::Type_union& tu ) const;
    bool Container_get_type( char& _value, const data::Type_union& tu ) const;
    bool Container_get_type( xx::String_cast& _value, const data::Type_union& tu ) const;

    // --- Variables ---
    std::unordered_map< std::string, data::Type_union > m_container_map;
  } static container;
}//Data



#endif
