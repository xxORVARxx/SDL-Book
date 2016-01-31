
#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include "Init.h"
#include "A_Game_obj_interface.h"



struct Game_obj_parameters : public Base_game_obj_parameters
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



class Game_obj : public Base_game_obj
{
 public:
  Game_obj() {}
  virtual ~Game_obj() {}

  // --- Functions ---
  void Load( Game_obj_parameters& _obj_params );
  virtual void Parse( xml::parser& _p );

  virtual void Update() {}
  virtual void Draw( Camera* _camera );
  virtual void Clean();

  // --- Variables ---
 protected:
  std::string m_texture_id;
  glm::vec2 m_image_size;// The size of the image itself, should not be changed.
  glm::vec2 m_position;
  glm::vec2 m_scale;
  glm::vec2 m_size;// The size to be rendered on the screen.
};



class Creator_game_obj : public Base_creator_game_obj
{
  virtual Base_game_obj* Create_game_object() const
  {
    return new Game_obj;
  }
};



#endif
