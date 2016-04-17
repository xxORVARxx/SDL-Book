 
#ifndef SCRIPT_H
#define SCRIPT_H

#include "Init.h"

class State;



namespace data
{
  class Parser
  {
  public:
    // --- Functions ---

    template< typename T > 
    T Parse_value( std::ifstream& _file );

    void Parse_file( State* _state, std::ifstream& _file );

  private:
    void Value( std::string& _function, State* _state, std::ifstream& _file );
    template< typename T > 
    T Value_template( std::string& _variable_name, std::string& _function, State* _state, std::ifstream& _file );
    void Object( std::string& _function, State* _state, std::ifstream& _file );
    void Texture( std::string& _function, State* _state, std::ifstream& _file );
    void Function( std::string& _function, State* _state, std::ifstream& _file );
    // --- Variables ---

  };
}//data



#endif
