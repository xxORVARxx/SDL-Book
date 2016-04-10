
#ifndef XX_STRING_CAST_H
#define XX_STRING_CAST_H

#include <string>



namespace xx
{
  /* This is a 'wrapper'-class for std::string, to cheat type-safety. 
   * It IS a string that can be 'implicitly'-converted to most built-in-types
   * and, constructed from most built-in-types. Most 'operators' have been 
   * overloaded to work with most built-in-types, making this class work 
   * well in/with templates that do(or can/could do) mathematical operations.
   */

  struct String_cast
  {
    // Convert Types to String:
    String_cast() {}
    String_cast( const int _i ) { str = std::to_string( _i ); }
    String_cast( const long int _li ) { str = std::to_string( _li ); }
    String_cast( const unsigned _u ) { str = std::to_string( _u ); }
    String_cast( const long unsigned _lu ) { str = std::to_string( _lu ); }
    String_cast( const float _f ) { str = std::to_string( _f ); Remove_zeros( str ); }
    String_cast( const double _d ) { str = std::to_string( _d ); Remove_zeros( str ); }
    String_cast( const long double _ld ) { str = std::to_string( _ld ); Remove_zeros( str ); }
    String_cast( const bool _b ) { if( _b ) str = "True"; else str = "Fasle"; }
    String_cast( const char _c ) { str = _c; }
    String_cast( char const* _cs ) { str = _cs; }
    String_cast( std::string _s ) { str = _s; }
    String_cast( const xx::String_cast& _s ) { str = _s.str; }


    // Convert String to Types:
    operator int() const { 
      try { return std::stoi( str ); }
      catch( const std::exception& e ) { return 0; }
    }
    operator long int() const { 
      try { return std::stol( str ); }
      catch( const std::exception& e ) { return 0; }
    }
    operator unsigned() const {
      try { return std::stoul( str ); }
      catch( const std::exception& e ) { return 0; }
    }
    operator long unsigned() const {
      try { return std::stoul( str ); }
      catch( const std::exception& e ) { return 0; }
    }
    operator float() const { 
      try { return std::stof( str ); }
      catch( const std::exception& e ) { return 0; }
    }
    operator double() const {
      try { return std::stod( str ); }
      catch( const std::exception& e ) { return 0; }
    }
    operator long double() const { 
      try { return std::stold( str ); }
      catch( const std::exception& e ) { return 0; }
    }
    operator bool() const {
      try { return str.empty(); }
      catch( const std::exception& e ) { return 0; }
    }
    operator char() const { 
      try { return str[0]; }
      catch( const std::exception& e ) { return 0; }
    }
    operator std::string() const {
      try { return str; }
      catch( const std::exception& e ) { return 0; }
    }


    // Overload + Operator:
    template< typename T >
    xx::String_cast operator+( const T& _t ) const {
      try {
	std::string temp = std::to_string( _t );
	Remove_zeros( temp );
	return xx::String_cast( str + temp );
      }
      catch( const std::exception& e ) { 
	return xx::String_cast( str ); 
      }
    }
    xx::String_cast operator+( const bool _b ) const {
      return xx::String_cast( str );
    }
    xx::String_cast operator+( const char _c ) const {
      return xx::String_cast( str + _c );
    }
    xx::String_cast operator+( char const* _cs ) const {
      return xx::String_cast( str + _cs );
    }
    xx::String_cast operator+( const std::string& _s ) const {
      return xx::String_cast( str + _s );
    }
    xx::String_cast operator+( const xx::String_cast& _s ) const {
      return xx::String_cast( str + _s.str );
    }

    // Overload - Operator:
    template< typename T >
    xx::String_cast operator-( const T& _t ) const {
      try {
	std::string temp = std::to_string( _t );
	Remove_zeros( temp );
	return( xx::String_cast( str ) - temp );
      }
      catch( const std::exception& e ) { 
	return xx::String_cast( str ); 
      }
    }
    xx::String_cast operator-( const bool _b ) const {
      return xx::String_cast( str );
    }
    xx::String_cast operator-( const char _c ) const {
      if( str.empty())  return xx::String_cast( str );
      std::string temp( str );
      while( true ) {
	std::size_t found = temp.find( _c );
	if( found == std::string::npos )  break;
	else  temp.erase( found, 1 );
      }
      return xx::String_cast( temp );
    }
    xx::String_cast operator-( char const* _cs ) const {
      std::string s( _cs );
      if( str.empty() || s.empty())  return xx::String_cast( str );
      std::string temp( str );
      while( true ) {
	std::size_t found = temp.find( s );
	if( found == std::string::npos )  break;
	else  temp.erase( found, s.size());
      }
      return xx::String_cast( temp );
    }
    xx::String_cast operator-( const std::string& _s ) const {
      if( str.empty() || _s.empty())  return xx::String_cast( str );
      std::string temp( str );
      while( true ) {
	std::size_t found = temp.find( _s );
	if( found == std::string::npos )  break;
	else  temp.erase( found, _s.size());
      }
      return xx::String_cast( temp );
    }
    xx::String_cast operator-( const xx::String_cast& _s ) const {
      if( str.empty() || _s.str.empty())  return xx::String_cast( str );
      std::string temp( str );
      while( true ) {
	std::size_t found = temp.find( _s.str );
	if( found == std::string::npos )  break;
	else  temp.erase( found, _s.str.size());
      }
      return xx::String_cast( temp );
    }

    // Overload * Operator:
    template< typename T >
    xx::String_cast operator*( const T& _t ) const {
      try {
	std::string temp = std::to_string( _t );
	Remove_zeros( temp );
	return xx::String_cast( temp + str );
      }
      catch( const std::exception& e ) { 
	return xx::String_cast( str ); 
      }
    }
    xx::String_cast operator*( const bool _b ) const {
      return xx::String_cast( str );
    }
    xx::String_cast operator*( const char _c ) const {
      return xx::String_cast( _c + str );
    }
    xx::String_cast operator*( char const* _cs ) const {
      return xx::String_cast( _cs + str );
    }
    xx::String_cast operator*( const std::string& _s ) const {
      return xx::String_cast( _s + str );
    }
    xx::String_cast operator*( const xx::String_cast& _s ) const {
      return xx::String_cast( _s.str + str );
    }

    // Overload / Operator:
    template< typename T >
    xx::String_cast operator/( const T& _t ) const {
      try {
	std::string temp = std::to_string( _t );
	Remove_zeros( temp );
	return( xx::String_cast( str ) / temp );
      }
      catch( const std::exception& e ) { 
	return xx::String_cast( str ); 
      }
    }
    xx::String_cast operator/( const bool _b ) const {
      return xx::String_cast( str );
    }
    xx::String_cast operator/( const char _c ) const {
      if( str.empty())  return xx::String_cast( str );
      std::string temp( str );
      while( true ) {
	std::size_t found = temp.find_first_of( _c );
	if( found == std::string::npos )  break;
	else  temp.erase( found, 1 );
      }
      return xx::String_cast( temp );
    }
    xx::String_cast operator/( char const* _cs ) const {
      std::string s( _cs );
      if( str.empty() || s.empty())  return xx::String_cast( str );
      std::string temp( str );
      while( true ) {
	std::size_t found = temp.find_first_of( s );
	if( found == std::string::npos )  break;
	else  temp.erase( found, 1 );
      }
      return xx::String_cast( temp );
    }
    xx::String_cast operator/( const std::string& _s ) const {
      if( str.empty() || _s.empty())  return xx::String_cast( str );
      std::string temp( str );
      while( true ) {
	std::size_t found = temp.find_first_of( _s );
	if( found == std::string::npos )  break;
	else  temp.erase( found, 1 );
      }
      return xx::String_cast( temp ); 
    }
    xx::String_cast operator/( const xx::String_cast& _s ) const {
      if( str.empty() || _s.str.empty())  return xx::String_cast( str );
      std::string temp( str );
      while( true ) {
	std::size_t found = temp.find_first_of( _s.str );
	if( found == std::string::npos )  break;
	else  temp.erase( found, 1 );
      }
      return xx::String_cast( temp );
    }


    // Overload += Operator:
    template< typename T >
    xx::String_cast& operator+=( const T& _t ) {
      *this = *this + _t;
      return *this;
    }
    xx::String_cast& operator+=( const bool _b ) {
      return *this;
    }
    xx::String_cast& operator+=( const char _c ) {
      *this = *this + _c;
      return *this;
    }
    xx::String_cast& operator+=( char const* _cs ) {
      *this = *this + _cs;
      return *this;
    }
    xx::String_cast& operator+=( const std::string& _s ) {
      *this = *this + _s;
      return *this;
    }
    xx::String_cast& operator+=( const xx::String_cast& _s ) {
      *this = *this + _s;
      return *this;
    }

    // Overload -= Operator:
    template< typename T >
    xx::String_cast& operator-=( const T& _t ) {
      *this = *this - _t;
      return *this;
    }
    xx::String_cast& operator-=( const bool _b ) {
      return *this;
    }
    xx::String_cast& operator-=( const char _c ) {
      *this = *this - _c;
      return *this;
    }
    xx::String_cast& operator-=( char const* _cs ) {
      *this = *this - _cs;
      return *this;
    }
    xx::String_cast& operator-=( const std::string& _s ) {
      *this = *this - _s;
      return *this;
    }
    xx::String_cast& operator-=( const xx::String_cast& _s ) {
      *this = *this - _s;
      return *this;
    }

    // Overload *= Operator:
    template< typename T >
    xx::String_cast& operator*=( const T& _t ) {
      *this = *this * _t;
      return *this;
    }
    xx::String_cast& operator*=( const bool _b ) {
      return *this;
    }
    xx::String_cast& operator*=( const char _c ) {
      *this = *this * _c;
      return *this;
    }
    xx::String_cast& operator*=( char const* _cs ) {
      *this = *this * _cs;
      return *this;
    }
    xx::String_cast& operator*=( const std::string& _s ) {
      *this = *this * _s;
      return *this;
    }
    xx::String_cast& operator*=( const xx::String_cast& _s ) {
      *this = *this * _s;
      return *this;
    }

    // Overload /= Operator:
    template< typename T >
    xx::String_cast& operator/=( const T& _t ) {
      *this = *this / _t;
      return *this;
    }
    xx::String_cast& operator/=( const bool _b ) {
      return *this;
    }
    xx::String_cast& operator/=( const char _c ) {
      *this = *this / _c;
      return *this;
    }
    xx::String_cast& operator/=( char const* _cs ) {
      *this = *this / _cs;
      return *this;
    }
    xx::String_cast& operator/=( const std::string& _s ) {
      *this = *this / _s;
      return *this;
    }
    xx::String_cast& operator/=( const xx::String_cast& _s ) {
      *this = *this / _s;
      return *this;
    }


    // Overload Equality Operator:
    bool operator==( const int _i ) const {
      try { return( _i == std::stoi( str )); }
      catch( const std::exception& e ) { return false; }
    }
    bool operator==( const long int _li ) const {
      try { return( _li == std::stol( str )); }
      catch( const std::exception& e ) { return false; }
    }
    bool operator==( const unsigned _u ) const {
      try { return( _u == std::stoul( str )); }
      catch( const std::exception& e ) { return false; }
    }
    bool operator==( const long unsigned _lu ) const {
      try { return( _lu == std::stoul( str )); }
      catch( const std::exception& e ) { return false; }
    }
    bool operator==( const float _f ) const {
      try { return( _f == std::stof( str )); }
      catch( const std::exception& e ) { return false; }
    }
    bool operator==( const double _d ) const {
      try { return( _d == std::stod( str )); }
      catch( const std::exception& e ) { return false; }
    }
    bool operator==( const long double _ld ) const {
      try { return( _ld == std::stold( str )); }
      catch( const std::exception& e ) { return false; }
    }
    bool operator==( const bool _b ) const {
      if( str.empty())  return false;
      else  return true;
    }
    bool operator==( const char _c ) const {
      if( str.size() == 1 )  return( str[0] == _c );
      else  return false;
    }
    bool operator==( const char* _cs ) const {
      return( str == std::string( _cs ));
    }
    bool operator==( const std::string& _s ) const {
      return( str == _s );
    }
    bool operator==( const xx::String_cast& _s ) const {
      return( str == _s.str );
    }

    // Overload Inequality Operator:
    bool operator!=( const int _i ) const {
      try { return( _i != std::stoi( str )); }
      catch( const std::exception& e ) { return true; }
    }
    bool operator!=( const long int _li ) const {
      try { return( _li != std::stol( str )); }
      catch( const std::exception& e ) { return true; }
    }
    bool operator!=( const unsigned _u ) const {
      try { return( _u != std::stoul( str )); }
      catch( const std::exception& e ) { return true; }
    }
    bool operator!=( const long unsigned _lu ) const {
      try { return( _lu != std::stoul( str )); }
      catch( const std::exception& e ) { return true; }
    }
    bool operator!=( const float _f ) const {
      try { return( _f != std::stof( str )); }
      catch( const std::exception& e ) { return true; }
    }
    bool operator!=( const double _d ) const {
      try { return( _d != std::stod( str )); }
      catch( const std::exception& e ) { return true; }
    }
    bool operator!=( const long double _ld ) const {
      try { return( _ld != std::stold( str )); }
      catch( const std::exception& e ) { return true; }
    }
    bool operator!=( const bool _b ) const {
      if( str.empty())  return true;
      else  return false;
    }
    bool operator!=( const char _c ) const {
      if( str.size() == 1 )  return( str[0] != _c );
      else  return true;
    }
    bool operator!=( const char* _cs ) const {
      return( str != std::string( _cs ));
    }
    bool operator!=( const std::string& _s ) const {
      return( str != _s );
    }
    bool operator!=( const xx::String_cast& _s ) const {
      return( str != _s.str );
    }


    // Overload Less Operator:
    //   NOTE: Comperations is done in Alphabetical-order.
    template< typename T >
    bool operator<( const T& _t ) const {
      try {
	std::string temp = std::to_string( _t );
	Remove_zeros( temp );
	return( str < temp );
      }
      catch( const std::exception& e ) { return false; }
    }
    bool operator<( const bool _b ) const {
      return _b;
    }
    bool operator<( const char _c ) const {
      return( str < std::string( &_c ));
    }
    bool operator<( const char* _cs ) const {
      return( str < std::string( _cs ));
    }
    bool operator<( const std::string& _s ) const {
      return( str < _s );
    }
    bool operator<( const xx::String_cast& _s ) const {
      return( str < _s.str );
    }

    // Overload Less/Equal Operator:
    //   NOTE: Comperations is done in Alphabetical-order.
    template< typename T >
    bool operator<=( const T& _t ) const {
      try {
	std::string temp = std::to_string( _t );
	Remove_zeros( temp );
	return( str <= temp );
      }
      catch( const std::exception& e ) { return false; }
    }
    bool operator<=( const bool _b ) const {
      return _b;
    }
    bool operator<=( const char _c ) const {
      return( str <= std::string( &_c ));
    }
    bool operator<=( const char* _cs ) const {
      return( str <= std::string( _cs ));
    }
    bool operator<=( const std::string& _s ) const {
      return( str <= _s );
    }
    bool operator<=( const xx::String_cast& _s ) const {
      return( str <= _s.str );
    }

    // Overload Greater Operator:
    //   NOTE: Comperations is done in Alphabetical-order.
    template< typename T >
    bool operator>( const T& _t ) const {
      try {
	std::string temp = std::to_string( _t );
	Remove_zeros( temp );
	return( str > temp );
      }
      catch( const std::exception& e ) { return false; }
    }
    bool operator>( const bool _b ) const {
      return _b;
    }
    bool operator>( const char _c ) const {
      return( str > std::string( &_c ));
    }
    bool operator>( const char* _cs ) const {
      return( str > std::string( _cs ));
    }
    bool operator>( const std::string& _s ) const {
      return( str > _s );
    }
    bool operator>( const xx::String_cast& _s ) const {
      return( str > _s.str );
    }

    // Overload Greater/Equal Operator:
    //   NOTE: Comperations is done in Alphabetical-order.
    template< typename T >
    bool operator>=( const T& _t ) const {
      try {
	std::string temp = std::to_string( _t );
	Remove_zeros( temp );
	return( str >= temp );
      }
      catch( const std::exception& e ) { return false; }
    }
    bool operator>=( const bool _b ) const {
      return _b;
    }
    bool operator>=( const char _c ) const {
      return( str >= std::string( &_c ));
    }
    bool operator>=( const char* _cs ) const {
      return( str >= std::string( _cs ));
    }
    bool operator>=( const std::string& _s ) const {
      return( str >= _s );
    }
    bool operator>=( const xx::String_cast& _s ) const {
      return( str >= _s.str );
    }


    // Overload Random-Access Operator:
    char& operator[]( const int i ) {
      if( str.empty())
	throw std::length_error( "(xx) Indexing an empty string." );
      if(( i >= str.size() )&&( i < -str.size() ))
	throw std::length_error( "(xx) Index Out of Bounds." );
      if( i >= 0 )  return str[ i ];
      else  return str[ str.size() + i ];
    }
    const char& operator[]( const int i ) const {
      if( str.empty())
	throw std::length_error( "(xx) Indexing an empty string." );
      if(( i >= str.size() )&&( i < -str.size() ))
	throw std::length_error( "(xx) Index Out of Bounds." );
      if( i >= 0 )  return str[ i ];
      else  return str[ str.size() + i ];
    }


    // Overload the stream insertion and extraction operators:
    friend std::ostream& operator<<( std::ostream& _stream, const xx::String_cast& _s ) {
      _stream << _s.str;
      return _stream;
    }
    friend std::istream& operator>>( std::istream& _stream, xx::String_cast& _s ) {
      _stream >> _s.str;
      return _stream;
    }


    // --- Functions ---
    size_t Size() {
      return str.size();
    }

  private:
    void Remove_zeros( std::string& _s ) const {
      if( _s.find('.') != std::string::npos )
        for( std::string::reverse_iterator ri = _s.rbegin(); ri != _s.rend(); ++ri ) {
	  if(( *ri == '0' )||( *ri == '.' ))  _s.pop_back();
	  else  break;
	}
    }

    // --- Variables ---
    std::string str;
  };
}//xx



#endif
