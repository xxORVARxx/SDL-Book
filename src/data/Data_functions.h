
#ifndef DATA_FUNCTIONS_H
#define DATA_FUNCTIONS_H

#include "Parser.h"

class State;
class Camera;



namespace data
{
  void o_Make_SDL_gobj( State* _state, 
			std::ifstream& _file );

  void t_Swap_texture_maps();
  void t_Move_or_load_texture( std::ifstream& _file );
  void t_Clear_texture_map();
  void t_Clear_current_texture_map();

  void f_Make_camera( Camera*& _camera_ptr );
}//data



#endif
