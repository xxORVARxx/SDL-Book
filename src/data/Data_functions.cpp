
#include "Data_functions.h"
#include "Texture_manager_v2.h"

#include "Game.h"
#include "Game_world.h"
#include "Camera.h"
#include "State.h"

#include "SDL_gobj.h"



namespace data
{

  void
  o_Make_SDL_gobj( State* _state, 
		   std::ifstream& _file ) 
  {
    std::string filename;
    _file >> filename;
    SDL_gobj* object_ptr = new SDL_gobj( filename );
    object_ptr->Create();
    _state->Add_object( object_ptr );
  }



  void
  t_Swap_texture_maps() 
  {
    the_Texture_manager_v2::Instance().Swap_maps();
  }

  void
  t_Move_or_load_texture( std::ifstream& _file ) 
  {
    std::string id, filename;
    _file >> id;
    _file >> filename;
    the_Texture_manager_v2::Instance().Move_or_load_texture( the_Game::Instance().Get_renderer(), 
							     id, 
							     filename );
  }

  void
  t_Clear_texture_map() 
  {
    the_Texture_manager_v2::Instance().Clear_map();
  }

  void
  t_Clear_current_texture_map() 
  {
    the_Texture_manager_v2::Instance().Clear_current_map();
  }



  void
  f_Make_camera( Camera*& _camera_ptr ) 
  {
    _camera_ptr = new Camera;
  }

}//data
