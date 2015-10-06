
#ifndef OBJECTS_BLUEPRINT_H
#define OBJECTS_BLUEPRINT_H

#include "Init.h"



// This holds the 'Parameters' to pass through the 'Blueprint' class to the 'Object' classes.
struct Object_load_parameters
{
 Object_load_parameters( std::string s_id, int s_x, int s_y, int s_w, int s_h, SDL_RendererFlip s_flip = SDL_FLIP_NONE  ) :
  m_id(s_id), m_x(s_x), m_y(s_y), m_w(s_w), m_h(s_h), m_flip(s_flip) {}

  std::string Get_id() { return m_id; }
  SDL_RendererFlip Get_flip() { return m_flip; }
  int Get_x() { return m_x; }
  int Get_y() { return m_y; }
  int Get_w() { return m_w; }
  int Get_h() { return m_h; }

 private:
  std::string m_id;
  SDL_RendererFlip m_flip;
  int m_x;
  int m_y;
  int m_w;
  int m_h;
};



// Polymorphism.  Abstract Base Class. 
// This is a 'Blueprint' class which other 'Object' classes have to be designed after.
class Object_blueprint
{
 protected:
  Object_blueprint( const Object_load_parameters* params_ptr ) {}
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
  Object_default( Object_load_parameters* params_ptr );

  virtual void Update();
  virtual void Draw();
  virtual void Clean();

 protected:
  std::string m_texture_id;
  SDL_RendererFlip m_texture_flip;
  int m_x;
  int m_y;
  int m_w;
  int m_h;
  int m_current_frame;
  int m_last_frame;
  int m_current_row;
};



#endif