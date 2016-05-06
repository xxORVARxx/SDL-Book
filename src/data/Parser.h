 
#ifndef PARSER_H
#define PARSER_H

#include "Init.h"
#include "xx_String_cast.h"

#include "Data_do_functions.h"
#include "Data_get_functions.h"

class State;
class Base_SDL_game_obj;



namespace data
{
  class Parser
  {
    friend Do_functions;
    friend Get_functions;

  public:
    Parser() : 
      m_value_from_file(false), m_is_this_object(false), m_this_state(nullptr), m_this_object(nullptr) {}

    // --- Functions ---
    void Set_this( State* _state );
    void Set_this( State* _state, Base_SDL_game_obj* _object );

    template< typename T > 
    T Parse_file( std::ifstream& _file );

    void Parse_file( std::ifstream& _file );

  private:
    void Next_do_functions( bool _disabled, std::ifstream& _file, std::string& _function );

    template< typename T > 
    T Next_get_functions( bool _disabled, std::ifstream& _file, std::string& _function );


    void Select_type_for_do( bool _disabled, std::ifstream& _file, std::string& _function );

    template< typename T > 
    T Select_type_for_get( bool _disabled, std::ifstream& _file, std::string& _function );

 
    void List_of_do_functions( bool _disabled, std::ifstream& _file, std::string& _function );

    template< typename T > 
    void List_of_template_do_functions( bool _disabled, std::ifstream& _file, std::string& _function );

    template< typename T > 
    T List_of_get_functions( bool _disabled, std::ifstream& _file, std::string& _function );

    template< typename T > 
    T List_of_template_get_functions( bool _disabled, std::ifstream& _file, std::string& _function );

    // --- Variables ---
    bool m_value_from_file;
    bool m_is_this_object;

    State* m_this_state;
    Base_SDL_game_obj* m_this_object;

    Do_functions m_do_functions;
    Get_functions m_get_functions;
  };
}//data



#endif
