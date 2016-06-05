
#ifndef INTERFACE_SDL_GAME_OBJ_H
#define INTERFACE_SDL_GAME_OBJ_H

#include "Init.h"
#include "Events.h"
#include "Camera.h"

namespace data { class Parser; }
class State;
class Printer;



enum class Object_type
{
  VOID = 0,
    BASE_SDL_GAME_OBJ,
    SDL_GOBJ,
    MAX
};



// Interface Class:
class Interface_SDL_game_obj
{
  friend class data::Parser;

 protected:
  virtual ~Interface_SDL_game_obj() {}

 public:
  virtual void Save() = 0;
  virtual void Load() = 0;

  virtual void Update() = 0;
  virtual void Draw( Camera* _camera_ptr ) = 0;
  virtual void Clean() = 0;

  virtual const Object_type Get_type_id() const = 0;

 protected:
  virtual void Parse_data_file( std::ifstream& _file, data::Parser* _p, bool _set_p ) = 0;
};



// Base Class:
class Base_SDL_game_obj : public Interface_SDL_game_obj
{
  friend class data::Parser;

 public:
  Base_SDL_game_obj( std::string _file, State* _state );
  virtual ~Base_SDL_game_obj() {}

  // --- Functions ---
  bool Create();
  void Clone();

  virtual void Save();
  virtual void Load();

  virtual void Update() {}
  virtual void Draw( Camera* _camera_ptr ) {}
  virtual void Clean();

  bool Find_hook( const std::string& _hook_name_id, event::i_Hook** _hook_dptr = nullptr );
  bool Find_trigger( const std::string& _trigger_name_id, event::i_Trigger** _trigger_dptr = nullptr );

  void Set_printer( Printer* _printer_ptr );
  Printer* Get_printer() const;

  virtual const Object_type Get_type_id() const { return Object_type::BASE_SDL_GAME_OBJ; }
  const std::string Get_name_id() const { return m_name_id; }

protected:
  virtual void Parse_data_file( std::ifstream& _file, data::Parser* _p, bool _set_p );

  // --- Variables ---
  const std::string m_file_name;
  std::string m_name_id;
  State* m_this_state_ptr;
  Printer* m_printer_ptr;
  std::string m_action;

  std::map< const std::string, event::i_Trigger* > m_triggers_map;
  std::map< const std::string, event::i_Hook* > m_hooks_map;
};



#endif
