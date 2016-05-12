
#ifndef SDL_GOBJ_H
#define SDL_GOBJ_H

#include "Interface_SDL_game_obj.h"



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
  virtual void Draw( Camera* _camera );
  virtual void Clean();

  virtual const Object_type Get_type_id() const { return Object_type::SDL_GOBJ; }

protected:
  virtual void Parse_data_file( std::ifstream& _file, data::Parser* _p, bool _set_p );

  // --- Variables ---
  glm::dvec2 m_position;
  glm::vec2 m_size;// The size to be rendered on the screen.
  glm::vec2 m_scale;

  struct Print_data
  {
    std::string m_texture_id;
    glm::vec2 m_image_size;// The size of the image itself, should not be changed.
    glm::vec2 m_print_offset;
  } m_print;
};



#endif
