
#include "Parser.h"



namespace data
{
  void Throw_invalid_argument( std::string the_corrupted_input );
  void Throw_file_corrupted( std::string _str = "" );
  bool Is_template( std::string& _function );
  void Comment( std::ifstream& _file, std::string& _comment );
  std::string Check_for_comments( std::ifstream& _file, std::string& _str );
  std::string Next_line_from_file( std::ifstream& _file );
}//data



namespace data
{
  void 
  Parser::Set_this( State* _state )
  {
    m_this_state = _state;
  }

  void 
  Parser::Set_this( State* _state, 
		    Base_SDL_game_obj* _object )
  {
    m_this_state = _state;
    m_this_object = _object;
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
    m_value_from_file = false;

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
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Done'. Expected: 'Return' and a value to be returned! " );
	    else
	      return;
	  }
	else if( function == "Return" )
	  {
	    if( m_value_from_file )
	      return;
	    else
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Return'. Expected: 'Done' and no return value! " );
	  }
	else
	  data::Throw_invalid_argument( function );
      }//while

    if( m_value_from_file )
      throw std::logic_error( "(xx) Parsing ERROR! Expected: 'Return' and a value to be returned! " );
    else
      throw std::logic_error( "(xx) Parsing ERROR! Expected: 'Done' to end the parsing! " );
  }
}//data



namespace data
{
  void
  Parser::Next_do_functions( std::ifstream& _file, 
			     std::string& _function )
  {
    if( (*_function.rbegin()) != ')' )
      throw std::logic_error( "(xx) Parsing ERROR! Expected: 'Return Value' from the function: '" + _function + "'. Missing return value! " );
    if( data::Is_template( _function ))
      this->Select_type_for_do( _file, _function );
    else
      this->List_of_do_functions( _file, _function );
  }

  template< typename T > 
  T 
  Parser::Next_get_functions( std::ifstream& _file, 
			      std::string& _function )
  {
    if( (*_function.rbegin()) == ')' )
      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Return Value' from the function: '" + _function + "'. Did not expect return value! " );
    if( data::Is_template( _function ))
      return this->Select_type_for_get< T >( _file, _function );
    else
      return this->List_of_get_functions< T >( _file, _function );
  }
}//data



namespace data
{
  void 
  Parser::Select_type_for_do( std::ifstream& _file, 
			      std::string& _function )
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
      throw std::invalid_argument( "(xx) Parsing ERROR! '" + template_type + "' is not a valid type! " );
  }



  template< typename T > 
  T 
  Parser::Select_type_for_get( std::ifstream& _file, 
			       std::string& _function )
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
      throw std::invalid_argument( "(xx) Parsing ERROR! '" + template_type + "' is not a valid type! " );

    return value;
  }
}//data



namespace data
{
  void 
  Parser::List_of_do_functions( std::ifstream& _file, 
				std::string& _function )
  {
    switch( _function[0] )
      {

      case 'l': // logic Functions:
	if( _function == "l_If(PP)" )
	  m_do_functions.l_If( _file, this );
	else if( _function == "l_If_not(PP)" )
	  m_do_functions.l_If_not( _file, this );
	else 
	  Throw_invalid_argument( _function );
	break;

      case 'c': // Container:
	if( _function == "c_Container_erase(P)" )
	  m_do_functions.c_Container_erase( _file, this );
	else 
	  Throw_invalid_argument( _function );
	break;

      case 'o': // Object:
	if( _function == "o_Make_SDL_gobj(PP)" )
	  m_do_functions.o_Make_SDL_gobj( _file, this );
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

      case 'i': // Images:
	if( _function == "i_Load_image_data(PP)" )
	  m_do_functions.i_Load_image_data( _file, this );
	else if( _function == "i_Erase_image_data(P)" )
	  m_do_functions.i_Erase_image_data( _file, this );
	else if( _function == "i_Make_frame_printer(PPRR)" )
	  m_do_functions.i_Make_frame_printer( _file, this );
	else if( _function == "i_Make_action(PPPPRRRR)" )
	  m_do_functions.i_Make_action( _file, this );
	else
	  Throw_invalid_argument( _function );
	break;

      case 's': // State:
	if( _function == "s_Make_camera(P)" )
	  m_do_functions.s_Make_camera( _file, this );
	else
	  Throw_invalid_argument( _function );
	break;

      default:
	Throw_invalid_argument( _function );
      }//switch
  }



  template< typename T > 
  void 
  Parser::List_of_template_do_functions( std::ifstream& _file, 
					 std::string& _function )
  {
    switch( _function[0] )
      {
      case 'c': // Container:
	if( _function == "c_Container_add(PT)" )
	  m_do_functions.c_Container_add< T >( _file, this );
	else if( _function == "c_Container_set(PT)" )
	  m_do_functions.c_Container_set< T >( _file, this );
	else 
	  Throw_invalid_argument( _function );
	break;

      case 'p': // Parser:
	if( _function == "p_Print(T)" )
	  m_do_functions.p_Print< T >( _file, this );
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
  Parser::List_of_get_functions( std::ifstream& _file, 
				 std::string& _function )
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

      case 'c': // Container:
	if( _function == "c_Container_has(P)R" )
	  value = m_get_functions.c_Container_has( _file, this );
	else
	  Throw_invalid_argument( _function );
	break;

      case 'o': // Object:
	if( _function == "o_This_object()R" )
	  value = m_get_functions.o_This_object( this );
	else
	  Throw_invalid_argument( _function );
	break;

      case 'i': // Images:
	if( _function == "i_Has_image_data(P)R" )
	  value = m_get_functions.i_Has_image_data( _file, this );
	else
	  Throw_invalid_argument( _function );
	break;

      case 's': // State:
	if( _function == "s_This_state()R" )
	  value = m_get_functions.s_This_state( this );
	else if( _function == "s_Has_state(P)R" )
	  value = m_get_functions.s_Has_state( _file, this );
	else
	  Throw_invalid_argument( _function );
	break;

      case 't': // Texture:
	if( _function == "t_Texture_width(P)R" )
	  value = m_get_functions.t_Texture_width( _file, this );
	else if( _function == "t_Texture_height(P)R" )
	  value = m_get_functions.t_Texture_height( _file, this );
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
  Parser::List_of_template_get_functions( std::ifstream& _file, 
					  std::string& _function )
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

      case 'c': // Container:
	if( _function == "c_Container_get(P)T" )
	  value = m_get_functions.c_Container_get< T >( _file, this );
	else if( _function == "c_Container_take(P)T" )
	  value = m_get_functions.c_Container_take< T >( _file, this );
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
