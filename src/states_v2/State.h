
#ifndef STATE_H 
#define STATE_H

#include "Init.h"

class Camera;
class Base_SDL_game_obj;
class State;
namespace gs { 
  void f_Make_camera( State* _state, std::ifstream& _file ); 
}



class State
{
public:
  State( std::string _file );
  ~State();

  // --- Functions ---
  void Create();

  void Update();
  void Render();

  void Clean();

  const std::string Get_id() const { return m_state_id; }
  void Add_object( Base_SDL_game_obj* _obj ) { m_objects_vec.push_back( _obj ); }

private:
  friend void gs::f_Make_camera( State* _state, std::ifstream& _file );

  // --- Variables ---
  const std::string m_file_name;
  std::string m_state_id;

  Camera* m_camera_ptr;
  std::vector< Base_SDL_game_obj* > m_objects_vec;
};



#endif
