
#include "Parser.h"
#include "xx_String_cast.h"

#include "State.h"

#include "Data_values.h"
#include "Data_functions.h"



namespace data
{

  // --- --- PARSE VALUE --- ---
  template< typename T > 
  T 
  Parser::Parse_value( std::ifstream& _file )
  {
    T value;
    std::string function;
    _file >> function;
    if( _file.good())
      {
	switch( function[0] )
	  {
	  case 'b': // Built In Types:

	    if( function == "b_Int" )
	      value = data::b_Int( _file );
	    else if( function == "b_Long_int" )
	      value = data::b_Long_int( _file );
	    else if( function == "b_Unsigned" )
	      value = data::b_Unsigned( _file );
	    else if( function == "b_Long_unsigned" )
	      value = data::b_Long_unsigned( _file );
	    else if( function == "b_Float" )
	      value = data::b_Float( _file );
	    else if( function == "b_Double" )
	      value = data::b_Double( _file );
	    else if( function == "b_Long_double" )
	      value = data::b_Long_double( _file );
	    else if( function == "b_Bool" )
	      value = data::b_Bool( _file );
	    else if( function == "b_Char" )
	      value = data::b_Char( _file );
	    else if( function == "b_String" )
	      value = data::b_String( _file );

	    else
	      throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + function + "' !" );
	    break;
	  case 'm': // Mathematical Operations:

	    if( function == "m_Add" )
	      value = m_Add< T >( _file );
	    else if( function == "m_Subtract" )
	      value = m_Subtract< T >( _file );
	    else if( function == "m_Multiply" )
	      value = m_Multiply< T >( _file );
	    else if( function == "m_Divide" )
	      value = m_Divide< T >( _file );

	    else
	      throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + function + "' !" );
	    break;
	  case 'f': // Functions:

	    if( function == "f_Texture_width" )
	      value = data::f_Texture_width( _file );
	    else if( function == "f_Texture_height" )
	      value = data::f_Texture_height( _file );
	    else if( function == "f_Display_width" )
	      value = data::f_Display_width();
	    else if( function == "f_Display_height" )
	      value = data::f_Display_height();
	    else if( function == "f_Random_discrete_num" )
	      value = data::f_Random_discrete_num< T >( _file );
	    else if( function == "f_Random_real_num" )
	      value = data::f_Random_real_num< T >( _file );

	    else
	      throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + function + "' !" );
	    break;
	  default:
	    throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + function + "' !" );
	  }//switch
      }
    else 
      throw std::ios::failure( "Parsing ERROR! file corrupted!" );
    return value;
  }



  // --- --- PARSE FILE --- ---
  void 
  Parser::Parse_file( State* _state, 
		      std::ifstream& _file )
  {
    std::string function;
    while( ! _file.eof())
      {
	_file >> function;

	if( _file.fail())
	  throw std::ios::failure( "Parsing ERROR! file corrupted!" );

	switch( function[0] )
	  {
	  case 'v': // Value Returning:
	    this->Value( function, _state, _file );
	    break;
	  case 'o': // Objects:
	    this->Object( function, _state, _file );
	    break;
	  case 't': // Texture:
	    this->Texture( function, _state, _file );
	    break;
	  case 'f': // Functions:
	    this->Function( function, _state, _file );
	    break;
	  case 'p':
	    if( function == "p_Done" ) 
	      {
		std::cout << "All Done!\n";
		return;
	      }
	    break;
	  default:
	    throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + function + "' !" );
	  }//switch
      }//while
  }



  void 
  Parser::Value( std::string& _function, 
		 State* _state, 
		 std::ifstream& _file )
  {
    std::string template_type;
    std::string variable_name;
    _file >> template_type;
    _file >> variable_name;

    if( template_type == "vb_Int" )
      this->Value_template< int >( variable_name, _function, _state, _file );
    else if( template_type == "vb_Long_int" )
      this->Value_template< long int >( variable_name, _function, _state, _file );
    else if( template_type == "vb_unsigned" )
      this->Value_template< unsigned >( variable_name, _function, _state, _file );
    else if( template_type == "vb_Long_unsigned" )
      this->Value_template< long unsigned >( variable_name, _function, _state, _file );
    else if( template_type == "vb_Float" )
      this->Value_template< float >( variable_name, _function, _state, _file );
    else if( template_type == "vb_Double" )
      this->Value_template< double >( variable_name, _function, _state, _file );
    else if( template_type == "vb_Long_double" )
      this->Value_template< long double >( variable_name, _function, _state, _file );
    else if( template_type == "vb_Bool" )
      this->Value_template< bool >( variable_name, _function, _state, _file );
    else if( template_type == "vb_Char" )
      this->Value_template< char >( variable_name, _function, _state, _file );
    else if( template_type == "vb_String" )
      this->Value_template< xx::String_cast >( variable_name, _function, _state, _file );
    else
      throw std::invalid_argument( "Parsing ERROR! '" + template_type + "' is not a valid type!" );
  }



  template< typename T > 
  T
  Parser::Value_template( std::string& _variable_name, 
			  std::string& _function, 
			  State* _state, 
			  std::ifstream& _file )
  {
    T value;
    if( _function == "v_Get_value" )
      {
	value = this->Parse_value< T >( _file );
      }
    else if( _function == "v_Save_value" )
      {
	value = this->Parse_value< T >( _file );
	// PUTT IN MAP HERE, OR SOMTHING LIKE THIS:
	// my_map< T >[ _variable_name ] = value;
      }
    else if( _function == "v_Load_value" )
      {
	// SEARCH MAP HERE FOR SOME VALUE, OR SOMTHING LIKE THIS:
	// value = my_map< T >.find( _variable_name );
      }
    else
      throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + _function + "' !" );
    return value;
  }



  void 
  Parser::Object( std::string& _function, 
		  State* _state, 
		  std::ifstream& _file )
  {
    if( _function == "o_Make_SDL_gobj" )
      data::o_Make_SDL_gobj( _state, _file );
    else
      throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + _function + "' !" );
  }



  void 
  Parser::Texture( std::string& _function, 
		   State* _state, 
		   std::ifstream& _file )
  {
    if( _function == "t_Swap_texture_maps" )
      data::t_Swap_texture_maps();
    else if( _function == "t_Move_or_load_texture" )
      data::t_Move_or_load_texture( _file );
    else if( _function == "t_Clear_texture_map" )
      data::t_Clear_texture_map();
    else if( _function == "t_Clear_current_texture_map" )
      data::t_Clear_current_texture_map();
    else
      throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + _function + "' !" );
  }



  void 
  Parser::Function( std::string& _function, 
		    State* _state, 
		    std::ifstream& _file )
  {
    if( _function == "f_Make_camera" )
      data::f_Make_camera( _state->m_camera_ptr );
    else
      throw std::invalid_argument( "Parsing ERROR! Nothing to do with: '" + _function + "' !" );
  }

}//data
