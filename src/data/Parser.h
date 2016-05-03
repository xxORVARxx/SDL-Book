 
#ifndef PARSER_H
#define PARSER_H

#include "Init.h"
#include "xx_String_cast.h"
/*
#include "Data_container.h"

//#include "xx_String_cast.h"
#include "State.h"
#include "Texture_manager_v2.h"
#include "Game_world.h"
#include "Game.h"
#include "Camera.h"
#include "SDL_gobj.h"
*/


/*
namespace data
{
  void Throw_invalid_argument( std::string the_corrupted_input );
  void Throw_file_corrupted();
  bool Is_template( std::string& _function );
  void Comment( std::ifstream& _file, std::string& _comment );
  std::string Check_for_comments( std::ifstream& _file, std::string& _str );
}//data
*/


#include "Data_do_functions.h"
#include "Data_get_functions.h"



namespace data
{
  class Parser
  {
    friend Do_functions;
    friend Get_functions;

  public:
    Parser() : m_value_from_file(false) {}

    // --- Functions ---
    template< typename T > 
    T Parse_file( std::ifstream& _file );

    void Parse_file( std::ifstream& _file );

  private:
    void Next_do_functions( std::ifstream& _file, std::string& _function );

    template< typename T > 
    T Next_get_functions( std::ifstream& _file, std::string& _function );


    void Select_type_for_do( std::ifstream& _file, std::string& _function );

    template< typename T > 
    T Select_type_for_get( std::ifstream& _file, std::string& _function );

 
    void List_of_do_functions( std::ifstream& _file, std::string& _function );

    template< typename T > 
    void List_of_template_do_functions( std::ifstream& _file, std::string& _function );

    template< typename T > 
    T List_of_get_functions( std::ifstream& _file, std::string& _function );

    template< typename T > 
    T List_of_template_get_functions( std::ifstream& _file, std::string& _function );

    // --- Variables ---
    bool m_value_from_file;

    Do_functions m_do_functions;
    Get_functions m_get_functions;
  };
}//data



#endif
