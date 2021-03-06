
#ifndef SDL_GOBJ_H
#define SDL_GOBJ_H

#include "Interface_SDL_game_obj.h"

class Printer;



class SDL_gobj : public Base_SDL_game_obj
{
  friend class data::Parser;

public:
  SDL_gobj( std::string _file, State* _state );
  virtual ~SDL_gobj() {}

  // --- Functions ---
  virtual void Save() {}
  virtual void Load() {}

  virtual void Update();
  virtual void Draw( Camera* _camera_ptr );
  virtual void Clean();

  virtual const Object_type Get_type_id() const { return Object_type::SDL_GOBJ; }

protected:
  virtual void Parse_data_file( std::ifstream& _file, data::Parser* _p, bool _set_p );

  // --- Variables ---
  Uint8 m_move_up_key, m_move_down_key, m_move_right_key, m_move_left_key;

  event::Trigger m_trigger_key_left;
  event::Trigger m_trigger_key_right;

  // TEST:
  void Test_function( string_t _str );
  event::Hook_T< SDL_gobj, string_t > m_hook_test;
  event::Trigger_T< integer_t > m_trigger_test;
};



#endif
