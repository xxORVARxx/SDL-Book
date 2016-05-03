
#include "Parser.h"



namespace data
{
  void 
  Throw_invalid_argument( std::string the_corrupted_input )
  {
    throw std::invalid_argument( "(xx) Parsing ERROR! Nothing to do with: '" + the_corrupted_input + "', corrupted input from file!" );
  }

  void 
  Throw_file_corrupted( std::string _str = "" )
  {
    throw std::ios::failure( "(xx) Parsing ERROR! file corrupted!" + _str );
  }
}//data



namespace data
{
  bool 
  Is_template( std::string& _function )
  {
    for( auto i = _function.rbegin() ; (*i) != '(' ; ++i )
      {
	if( (*i) == 'T' )
	  return true;
      }//for
    return false;
  }

  void
  Comment( std::ifstream& _file, std::string& _comment )
  {
    bool comment_found = false;
    while( _file.good())
      {
	for( size_t i = 0 ; (( ! comment_found )&&( i < _comment.size() ))  ; ++i )
	  {
	    if( _comment[i] != '#' )
	      {
		comment_found = true;
		break;
	      }
	  }//for
	if( comment_found &&( *_comment.rbegin() == '#' ))
	  return;
	_file >> _comment;
      }//while
    data::Throw_file_corrupted( " in Comment." );
  }

  std::string 
  Check_for_comments( std::ifstream& _file, std::string& _str )
  {
    while( *_str.begin() == '#' )
      {
	data::Comment( _file, _str );
	_file >> _str;
	if( ! _file.good())
	  data::Throw_file_corrupted( " When Checking for Comments." );
      }
    return _str;
  }

  std::string
  Next_line_from_file( std::ifstream& _file )
  {
    std::string line;
    _file >> line;
    if( ! _file.good())
      data::Throw_file_corrupted();
    line = data::Check_for_comments( _file, line );
    return line;
  }
}//data



namespace data
{
  template< typename T > 
  T 
  Parser::Parse_file( std::ifstream& _file )
  {
    m_value_from_file = true;
    this->Parse_file( _file );

    std::string function = data::Next_line_from_file( _file );
    return this->Next_get_functions< T >( _file, function );
  }



  void 
  Parser::Parse_file( std::ifstream& _file )
  {
    std::string function;
    while( ! _file.eof())
      {
	_file >> function;
	if( _file.fail())
	  data::Throw_file_corrupted();

        if( (*function.rbegin()) == ')' )
	  {
	    this->Next_do_functions( _file, function );
	  }
	else if( function[0] == '#' )
	  {
	    data::Comment( _file, function );
	  }
	else if( function == "Done" )
	  {
	    if( m_value_from_file )
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Done'. Expected: 'Return' and a value to be returned!" );
	    else
	      return;
	  }
	else if( function == "Return" )
	  {
	    if( m_value_from_file )
	      return;
	    else
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Return'. Expected: 'Done' and no return value!" );
	  }
	else
	  data::Throw_invalid_argument( function );
      }//while

    if( m_value_from_file )
      throw std::logic_error( "(xx) Parsing ERROR! Expected: 'Return' and a value to be returned!" );
    else
      throw std::logic_error( "(xx) Parsing ERROR! Expected: 'Done' to end the parsing!" );
  }
}//data



namespace data
{
  void
  Parser::Next_do_functions( std::ifstream& _file, std::string& _function )
  {
    if( data::Is_template( _function ))
      this->Select_type_for_do( _file, _function );
    else
        this->List_of_do_functions( _file, _function );
  }

  template< typename T > 
  T 
  Parser::Next_get_functions( std::ifstream& _file, std::string& _function )
  {
    if( data::Is_template( _function ))
      return this->Select_type_for_get< T >( _file, _function );
    else
      return this->List_of_get_functions< T >( _file, _function );
  }
}//data



namespace data
{
  void 
  Parser::Select_type_for_do( std::ifstream& _file, std::string& _function )
  {
    std::string template_type = data::Next_line_from_file( _file );

    if( template_type == "Int" )
      this->List_of_template_do_functions< int >( _file, _function );
    else if( template_type == "Long_int" )
      this->List_of_template_do_functions< long int >( _file, _function );
    else if( template_type == "Unsigned" )
      this->List_of_template_do_functions< unsigned >( _file, _function );
    else if( template_type == "Long_unsigned" )
      this->List_of_template_do_functions< long unsigned >( _file, _function );
    else if( template_type == "Float" )
      this->List_of_template_do_functions< float >( _file, _function );
    else if( template_type == "Double" )
      this->List_of_template_do_functions< double >( _file, _function );
    else if( template_type == "Long_double" )
      this->List_of_template_do_functions< long double >( _file, _function );
    else if( template_type == "Bool" )
      this->List_of_template_do_functions< bool >( _file, _function );
    else if( template_type == "Char" )
      this->List_of_template_do_functions< char >( _file, _function );
    else if( template_type == "String" )
      this->List_of_template_do_functions< xx::String_cast >( _file, _function );
    else
      throw std::invalid_argument( "(xx) Parsing ERROR! '" + template_type + "' is not a valid type!" );
  }



  template< typename T > 
  T 
  Parser::Select_type_for_get( std::ifstream& _file, std::string& _function )
  {
    T value;
    std::string template_type = data::Next_line_from_file( _file );

    if( template_type == "Int" )
      value = this->List_of_template_get_functions< int >( _file, _function );
    else if( template_type == "Long_int" )
      value = this->List_of_template_get_functions< long int >( _file, _function );
    else if( template_type == "Unsigned" )
      value = this->List_of_template_get_functions< unsigned >( _file, _function );
    else if( template_type == "Long_unsigned" )
      value = this->List_of_template_get_functions< long unsigned >( _file, _function );
    else if( template_type == "Float" )
      value = this->List_of_template_get_functions< float >( _file, _function );
    else if( template_type == "Double" )
      value = this->List_of_template_get_functions< double >( _file, _function );
    else if( template_type == "Long_double" )
      value = this->List_of_template_get_functions< long double >( _file, _function );
    else if( template_type == "Bool" )
      value = this->List_of_template_get_functions< bool >( _file, _function );
    else if( template_type == "Char" )
      value = this->List_of_template_get_functions< char >( _file, _function );
    else if( template_type == "String" )
      value = this->List_of_template_get_functions< xx::String_cast >( _file, _function );
    else
      throw std::invalid_argument( "(xx) Parsing ERROR! '" + template_type + "' is not a valid type!" );

    return value;
  }
}//data



namespace data
{
  void 
  Parser::List_of_do_functions( std::ifstream& _file, std::string& _function )
  {
    switch( _function[0] )
      {
      case 'c': // Container:
	if( _function == "c_Container_erase(P)" )
	  m_do_functions.c_Container_erase( _file, this );
	else 
	  Throw_invalid_argument( _function );
	break;

      case 'o': // Object:
	if( _function == "o_Make_SDL_gobj()" )
	  m_do_functions.o_Make_SDL_gobj( _file );
	else 
	  Throw_invalid_argument( _function );
	break;

      case 't': // Texture:
	if( _function == "t_Swap_texture_maps()" )
	  m_do_functions.t_Swap_texture_maps();
	else if( _function == "t_Move_or_load_texture(PP)" )
	  m_do_functions.t_Move_or_load_texture( _file, this );
	else if( _function == "t_Clear_texture_map()" )
	  m_do_functions.t_Clear_texture_map();
	else if( _function == "t_Clear_current_texture_map()" )
	  m_do_functions.t_Clear_current_texture_map();
	else
	  Throw_invalid_argument( _function );
	break;

      case 's': // World:
	if( _function == "s_Make_camera()" )
	  m_do_functions.s_Make_camera();
	else
	  Throw_invalid_argument( _function );
	break;

      default:
	Throw_invalid_argument( _function );
      }//switch
  }



  template< typename T > 
  void 
  Parser::List_of_template_do_functions( std::ifstream& _file, std::string& _function )
  {
    switch( _function[0] )
      {
      case 'c': // Container:
	if( _function == "c_Container_add(PT)" )
	  m_do_functions.c_Container_add< T >( _file, this );
	else 
	  Throw_invalid_argument( _function );
	break;

      default:
	Throw_invalid_argument( _function );
      }//switch
  }
}//data



namespace data
{
  template< typename T > 
  T 
  Parser::List_of_get_functions( std::ifstream& _file, std::string& _function )
  {
    T value;
    switch( _function[0] )
      {
      case 'b': // Built In Types:
	if( _function == "b_Int()R" )
	  value = m_get_functions.b_Int( _file );
	else if( _function == "b_Long_int()R" )
	  value = m_get_functions.b_Long_int( _file );
	else if( _function == "b_Unsigned()R" )
	  value = m_get_functions.b_Unsigned( _file );
	else if( _function == "b_Long_unsigned()R" )
	  value = m_get_functions.b_Long_unsigned( _file );
	else if( _function == "b_Float()R" )
	  value = m_get_functions.b_Float( _file );
	else if( _function == "b_Double()R" )
	  value = m_get_functions.b_Double( _file );
	else if( _function == "b_Long_double()R" )
	  value = m_get_functions.b_Long_double( _file );
	else if( _function == "b_Bool()R" )
	  value = m_get_functions.b_Bool( _file );
	else if( _function == "b_Char()R" )
	  value = m_get_functions.b_Char( _file );
	else if( _function == "b_String()R" )
	  value = m_get_functions.b_String( _file );
	else
	  Throw_invalid_argument( _function );
	break;

      case 't': // Texture:
	if( _function == "t_Texture_width()R" )
	  value = m_get_functions.t_Texture_width( _file );
	else if( _function == "t_Texture_height()R" )
	  value = m_get_functions.t_Texture_height( _file );
	else
	  Throw_invalid_argument( _function );
	break;

      case 'w': // World:
        if( _function == "w_Display_width()R" )
	  value = m_get_functions.w_Display_width();
	else if( _function == "w_Display_height()R" )
	  value = m_get_functions.w_Display_height();
	else
	  Throw_invalid_argument( _function );
	break;

      default:
	Throw_invalid_argument( _function );
      }//switch
    return value;
  }



  template< typename T > 
  T 
  Parser::List_of_template_get_functions( std::ifstream& _file, std::string& _function )
  {
    T value;
    switch( _function[0] )
      {
      case 'm': // Mathematical Operations:
	if( _function == "m_Add(TT)T" )
	  value = m_get_functions.m_Add< T >( _file, this );
	else if( _function == "m_Subtract(TT)T" )
	  value = m_get_functions.m_Subtract< T >( _file, this );
	else if( _function == "m_Multiply(TT)T" )
	  value = m_get_functions.m_Multiply< T >( _file, this );
	else if( _function == "m_Divide(TT)T" )
	  value = m_get_functions.m_Divide< T >( _file, this );
	else
	  Throw_invalid_argument( _function );
	break;

	/*
      case 'r': // Random:
	if( _function == "r_Random_discrete_num(PP)T" )
	  value = data::r_Random_discrete_num< T >( _file );
	else if( _function == "r_Random_real_num(PP)T" )
	  value = data::r_Random_real_num< T >( _file );
	else
	  Throw_invalid_argument( _function );
	break;
	*/

      default:
	Throw_invalid_argument( _function );
      }//switch
    return value;
  }
}//data



namespace data
{
  template int             Parser::Parse_file< int >            ( std::ifstream& _file );
  template long int        Parser::Parse_file< long int >       ( std::ifstream& _file );
  template unsigned        Parser::Parse_file< unsigned >       ( std::ifstream& _file );
  template long unsigned   Parser::Parse_file< long unsigned >  ( std::ifstream& _file );
  template float           Parser::Parse_file< float >          ( std::ifstream& _file );
  template double          Parser::Parse_file< double >         ( std::ifstream& _file );
  template long double     Parser::Parse_file< long double >    ( std::ifstream& _file );
  template char            Parser::Parse_file< char >           ( std::ifstream& _file );
  template bool            Parser::Parse_file< bool >           ( std::ifstream& _file );
  template xx::String_cast Parser::Parse_file< xx::String_cast >( std::ifstream& _file );
}//data



#include "Data_do_functions.tpp"
#include "Data_get_functions.tpp"
