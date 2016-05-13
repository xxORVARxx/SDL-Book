
#ifndef CAMERA_H
#define CAMERA_H

#include "Init.h"



class Camera
{
 public:
  Camera();

  // --- Functions ---
  void Setup();

  glm::vec2 Get_position() { return m_position; }
  float Get_position_x() { return m_position.x; }
  float Get_position_y() { return m_position.y; }
  void Set_position( glm::vec2 _pos) { m_position = _pos; }
  void Set_position_x( float _x ) { m_position.x = _x; }
  void Set_position_y( float _y ) { m_position.y = _y; }
  void Add_position( glm::vec2 _pos) { m_position += _pos; }
  void Add_position_x( float _x ) { m_position.x += _x; }
  void Add_position_y( float _y ) { m_position.y += _y; }

  // --- Variables ---
 private:
  glm::vec2 m_position;
};



#endif
