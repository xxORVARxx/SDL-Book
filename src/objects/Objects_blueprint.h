
#ifndef OBJECTS_BLUEPRINT_H
#define OBJECTS_BLUEPRINT_H

#include "Init.h"



// This holds the 'Parameters' to pass through the 'Blueprint' class to the 'Object' classes.
struct Object_load_parameters
{
Object_load_parameters( std::string _id, glm::vec2 _pos, int _w, int _h, int _frame, int _row, int _speed,
			SDL_RendererFlip _flip = SDL_FLIP_NONE  ) :
  m_id(_id), m_position(_pos), m_w(_w), m_h(_h), m_frame(_frame), m_row(_row), m_frame_speed(_speed), m_flip(_flip) {}

  std::string Get_id() { return m_id; }
  SDL_RendererFlip Get_flip() { return m_flip; }
  glm::vec2 Get_position() { return m_position; }
  int Get_w() { return m_w; }
  int Get_h() { return m_h; }
  int Get_frame() { return m_frame; }
  int Get_row() { return m_row; }
  int Get_frame_speed() { return m_frame_speed; }

private:
  std::string m_id;
  SDL_RendererFlip m_flip;
  glm::vec2 m_position;
  int m_w;
  int m_h;
  int m_frame;
  int m_row;
  int m_frame_speed;
};



// Polymorphism.  Abstract Base Class. 
// This is a 'Blueprint' class which other 'Object' classes have to be designed after.
class Object_blueprint
{
 protected:
  Object_blueprint( const Object_load_parameters& _params ) {}
  virtual ~Object_blueprint() {}

 public:
  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual void Clean() = 0;
};



// This is the 'default-Object' class which other 'Object' classes can 'inharents' from. 
class Object_default : public Object_blueprint
{
 public:
  Object_default( Object_load_parameters& _params );
  virtual ~Object_default() {}

  // --- Functions ---
  virtual void Update();
  virtual void Draw();
  virtual void Clean();

  // --- Variables ---
 protected:
  std::string m_texture_id;
  SDL_RendererFlip m_texture_flip;
  glm::vec2 m_acceleration;
  glm::vec2 m_velocity;
  glm::vec2 m_position;
  int m_w;
  int m_h;
  int m_frame;
  int m_row;
  int m_frame_speed;

  int m_current_frame;
  int m_last_frame;
  int m_current_row;
};



#endif
