
#ifndef SDL_GOBJ_H
#define SDL_GOBJ_H

#include "Init.h"
#include "Interface_SDL_game_obj.h"



class SDL_gobj : public Base_SDL_game_obj
{
public:
  SDL_gobj( std::string _file );
  virtual ~SDL_gobj() {}

  // --- Functions ---


  virtual void Save() {}
  virtual void Load() {}

  virtual void Update() {}
  virtual void Draw( Camera* _camera ) {}
  virtual void Clean();

  virtual std::string Get_id() { return "SDL_gobj"; }

protected:
  virtual void Parse_data_file( std::ifstream& _file );

  // --- Variables ---
  std::string m_texture_id;
  glm::vec2 m_image_size;// The size of the image itself, should not be changed.
  glm::dvec2 m_position;
  glm::vec2 m_scale;
  glm::vec2 m_size;// The size to be rendered on the screen.
};



#endif
