 
#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "Init.h"
#include "A_Game_obj_interface.h"



class State_parser
{
 public:
  bool Parse_state( const std::string _state_file, std::string _state_id, std::vector< Base_game_obj* >& _objects_vec );

 private:
  bool Parse_textures( xml::parser& _p, std::vector< Base_game_obj* >& _objects_vec );
  bool Parse_objects( xml::parser& _p, std::vector< Base_game_obj* >& _objects_vec );
};



#endif
