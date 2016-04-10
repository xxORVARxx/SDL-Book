
#ifndef INTERFACE_SDL_GAME_OBJ_H
#define INTERFACE_SDL_GAME_OBJ_H

#include "Init.h"
#include "Camera.h"



// Interface Class:
class Interface_SDL_game_obj
{
 protected:
  virtual ~Interface_SDL_game_obj() {}

 public:
  virtual void Save() = 0;
  virtual void Load() = 0;

  virtual void Update() = 0;
  virtual void Draw( Camera* _camera ) = 0;
  virtual void Clean() = 0;

  virtual const std::string Get_id() const = 0;

 protected:
  virtual void Parse_data_file( std::ifstream& _file ) = 0;
};



// Base Class:
class Base_SDL_game_obj : public Interface_SDL_game_obj
{
 public:
  Base_SDL_game_obj( std::string _file );
  virtual ~Base_SDL_game_obj() {}

  // --- Functions ---
  void Create();
  void Clone();

  virtual void Save();
  virtual void Load();

  virtual void Update() {}
  virtual void Draw( Camera* _camera ) {}
  virtual void Clean() {}

  virtual const std::string Get_id() const { return "Base_SDL_game_obj"; }

protected:
  virtual void Parse_data_file( std::ifstream& _file ) {}

  // --- Variables ---
  const std::string m_file_name;
};



#endif
