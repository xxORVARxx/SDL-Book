 
#ifndef FUNCTIONS_STATE_H
#define FUNCTIONS_STATE_H

#include "State.h"
#include "Texture_manager_v2.h"

#include "Game.h"
#include "Camera.h"
#include "SDL_gobj.h"

/*
namespace gs { 
  void Get_value( State* _state, std::ifstream& _file ); 
}



namespace gs {
  void f_Make_SDL_gobj( State* _state, std::ifstream& _file ) {
    std::string filename;
    _file >> filename;
    SDL_gobj* object_ptr = new SDL_gobj( filename );
    object_ptr->Create();
    _state->Add_object( object_ptr );
  }

  void f_Swap_texture_maps() {
    the_Texture_manager_v2::Instance().Swap_maps();
  }

  void f_Move_or_load_texture( std::ifstream& _file ) {
    std::string id, filename;
    _file >> id;
    _file >> filename;
    the_Texture_manager_v2::Instance().Move_or_load_texture( the_Game::Instance().Get_renderer(), 
							     id, 
							     filename );
  }

  void f_Clear_texture_map() {
    the_Texture_manager_v2::Instance().Clear_map();
  }
  void f_Clear_current_texture_map() {
    the_Texture_manager_v2::Instance().Clear_current_map();
  }

  void f_Make_camera( State* _state, std::ifstream& _file ) {
    //_state->m_camera_ptr = new Camera;
  }
}//gs



namespace gs {
  void Get_value( State* _state, std::ifstream& _file )
  {
    std::string function;
    while( _file.good())
      {
	_file >> function;

	if( function == "f_Make_SDL_gobj" )
	  f_Make_SDL_gobj( _state, _file );

	else if( function == "f_Swap_texture_maps" )
	  f_Swap_texture_maps();
	else if( function == "f_Move_or_load_texture" )
	  f_Move_or_load_texture( _file );
	else if( function == "f_Clear_texture_map" )
	  f_Clear_texture_map();
	else if( function == "f_Clear_current_texture_map" )
	  f_Clear_current_texture_map();

	else if( function == "f_Make_camera" )
	  f_Make_camera( _state, _file );

	else if( function == "f_Done" )
	  break;

	else
	  throw std::ios::failure( "Error state's data file corrupted!" );
      }
  }
}//gs
*/



#endif
