
#ifndef STATE_H 
#define STATE_H

#include "Init.h"

namespace data { class Parser; }
class Camera;
class Base_SDL_game_obj;



class State
{
  friend class data::Parser;

public:
  State( std::string _file );
  ~State();

  // --- Functions ---
  void Create();
  void Load() {}
  void Save() {}

  Base_SDL_game_obj* Find_object( std::string& object_name_id );

  void Update() const;
  void Render() const;

  void Clean();

  const std::string Get_id() const { return m_name_id; }
  void Add_object( Base_SDL_game_obj* _obj ) { m_objects_vec.push_back( _obj ); }
  void Make_camera();
private:
  // --- Variables ---
  bool disable_logic;
  bool disable_render;

  const std::string m_file_name;
  std::string m_name_id;

  Camera* m_camera_ptr;
  std::vector< Base_SDL_game_obj* > m_objects_vec;
};



#endif
