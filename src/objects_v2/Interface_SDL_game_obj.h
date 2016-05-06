
#ifndef INTERFACE_SDL_GAME_OBJ_H
#define INTERFACE_SDL_GAME_OBJ_H

#include "Init.h"
#include "Camera.h"

namespace data { class Parser; }
class State;



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
  virtual void Draw( Camera* _camera ) = 0;
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
  void Create();
  void Clone();

  virtual void Save();
  virtual void Load();

  virtual void Update() {}
  virtual void Draw( Camera* _camera ) {}
  virtual void Clean() {}

  virtual const Object_type Get_type_id() const { return Object_type::BASE_SDL_GAME_OBJ; }
  const std::string Get_name_id() const { return m_name_id; }

protected:
  virtual void Parse_data_file( std::ifstream& _file, data::Parser* _p, bool _set_p );

  // --- Variables ---
  const std::string m_file_name;
  std::string m_name_id;
  State* m_this_state;
};



#endif
