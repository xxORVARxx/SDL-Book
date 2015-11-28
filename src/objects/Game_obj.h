
#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include "Init.h"
#include "A_Game_obj_interface.h"



// This holds the 'Parameters' to pass through the 'Object' classes.
struct Game_obj_parameters
{
Game_obj_parameters( std::string _id, glm::vec2 _image_size, glm::vec2 _pos, 
		     glm::vec2 _scale = glm::vec2( 1, 1 ), glm::vec2 _size = glm::vec2( 0, 0 )) :
  texture_id(_id), image_size(_image_size), position(_pos), scale(_scale), size(_size) {}
  std::string texture_id;
  glm::vec2 image_size;
  glm::vec2 position;
  glm::vec2 scale;// <- Default = 1, 1
  glm::vec2 size;// <- Default = 0, 0
};



// This is the default 'Game-object' class which other 'Object' classes can 'inharents' from. 
class Game_obj : public Game_obj_interface
{
 public:
  Game_obj( Game_obj_parameters& _obj_params, bool is_a_sheet = false );
  virtual ~Game_obj() {}

  // --- Functions ---
  virtual void Update() {}
  virtual void Draw();
  virtual void Clean();

  // --- Variables ---
 protected:
  std::string m_texture_id;
  glm::vec2 m_image_size;// The size of the image itself, should not be changed.
  glm::vec2 m_position;
  glm::vec2 m_scale;
  glm::vec2 m_size;// The size to be rendered on the screen.
};



#endif
