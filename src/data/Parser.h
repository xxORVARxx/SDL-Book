 
#ifndef PARSER_H
#define PARSER_H

#include "Init.h"
#include "xx_String_cast.h"

#include "Data_do_functions.h"
#include "Data_get_functions.h"

class State;
class Base_SDL_game_obj;
namespace event { class Events_manager; }



namespace data
{
  class Parser
  {
    friend Do_functions;
    friend Get_functions;
    friend event::Events_manager;

  public:
    Parser() : 
      m_value_from_file(false), m_disabled(false), m_this_state(nullptr), m_this_object(nullptr), m_do_functions(&m_disabled), m_get_functions(&m_disabled) {}

    // --- Functions ---
    void Set_this( State* _state );
    void Set_this( State* _state, Base_SDL_game_obj* _object );
    bool Disabled() { return m_disabled; }

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
    bool m_disabled;

    State* m_this_state;
    Base_SDL_game_obj* m_this_object;

    Do_functions m_do_functions;
    Get_functions m_get_functions;
  };
}//data



#endif
