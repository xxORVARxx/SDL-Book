
#include "Parser.h"



namespace data
{
  void Throw_invalid_argument( std::string the_corrupted_input );
  void Throw_file_corrupted( std::string _str = "" );
  bool Is_template( std::string& _function );
  void Comment( std::ifstream& _file, std::string& _comment );
  std::string Check_for_comments( std::ifstream& _file, std::string& _str );
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
    this->Parse_file( _file, "Return" );
    std::string function = data::Next_line_from_file( _file );
    return this->Next_get_functions< T >( _file, function );
  }



  void 
  Parser::Parse_file( std::ifstream& _file, std::string _end )
  {
    std::string function;
    while( ! _file.eof())
      {
	_file >> function;
	if( _file.fail())
	  data::Throw_file_corrupted();

        if( (*function.rbegin()) == ')' ) // Do-Function.
	  {
	    this->Next_do_functions( _file, function );
	  }
	else if( function[0] == '#' ) // Comment.
	  {
	    data::Comment( _file, function );
	  }
	else if( function == "Done" ) // Done.
	  {
	    if( _end == "Done" )
	      return;
	    else if( _end == "Local" )
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Done'. Expected: 'Local' and a Local-function! " );
	    else
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Done'. Expected: 'Return' and a value to be returned! " );
	  }
	else if( function == "Return" ) // Return.
	  {
	    if( _end == "Return" )
	      return;
	    else if( _end == "Local" )
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Return'. Expected: 'Local' and a Local-function! " );
	    else
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Return'. Expected: 'Done' and no return value! " );
	  }
	else if( function == "Local" ) // Local-Function
	  {
	    if( _end == "Local" )
	      return;
	    else
	      throw std::logic_error( "(xx) Parsing ERROR! Unexpected: 'Local'. Not expecting Local-function! " );
	  }
	else
	  data::Throw_invalid_argument( function );
      }//while

    if( function == "Done" )
      throw std::logic_error( "(xx) Parsing ERROR! Expected: 'Done' to end the parsing! " );
    else
      throw std::logic_error( "(xx) Parsing ERROR! Expected: 'Return' and a value to be returned! " );
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

    if( template_type == "Byte" )
      this->List_of_template_do_functions< byte_t >( _file, _function );
    else if( template_type == "Integer" )
      this->List_of_template_do_functions< integer_t >( _file, _function );
    else if( template_type == "Real" )
      this->List_of_template_do_functions< real_t >( _file, _function );
    else if( template_type == "String" )
      this->List_of_template_do_functions< string_t >( _file, _function );
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

    if( template_type == "Byte" )
      value = this->List_of_template_get_functions< byte_t >( _file, _function );
    else if( template_type == "Integer" )
      value = this->List_of_template_get_functions< integer_t >( _file, _function );
    else if( template_type == "Real" )
      value = this->List_of_template_get_functions< real_t >( _file, _function );
    else if( template_type == "String" )
      value = this->List_of_template_get_functions< string_t >( _file, _function );
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

      case 's': // State:
	if( _function == "s_Make_camera(P)" )
	  m_do_functions.s_Make_camera( _file, this );
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
	else if( _function == "i_Make_frame_printer(PPRRRR)" )
	  m_do_functions.i_Make_frame_printer( _file, this );
	else if( _function == "i_Make_action(PPPPRRRR)" )
	  m_do_functions.i_Make_action( _file, this );
	else
	  Throw_invalid_argument( _function );
	break;

      case 'e': // Events:
	if( _function == "e_Make_event()" )
	  m_do_functions.e_Make_event( _file, this );
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
	if( _function == "b_Byte()R" )
	  value = m_get_functions.b_Byte( _file );
	else if( _function == "b_Integer()R" )
	  value = m_get_functions.b_Integer( _file );
	else if( _function == "b_Real()R" )
	  value = m_get_functions.b_Real( _file );
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
  template byte_t Parser::Parse_file< byte_t >( std::ifstream& _file );
  template integer_t Parser::Parse_file< integer_t >( std::ifstream& _file );
  template real_t Parser::Parse_file< real_t >( std::ifstream& _file );
  template string_t Parser::Parse_file< string_t >( std::ifstream& _file );
}//data



#include "Data_do_functions.tpp"
#include "Data_get_functions.tpp"
