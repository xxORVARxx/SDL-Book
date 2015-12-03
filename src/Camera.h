
#ifndef CAMERA_H
#define CAMERA_H

#include "Init.h"



class Camera
{
 public:
  Camera();

  void Setup();

  glm::vec2 Get_position() { return glm::vec2( m_position_x, m_position_y ); }
  double Get_position_x() { return m_position_x; }
  double Get_position_y() { return m_position_y; }
  void Set_position( glm::vec2 _pos) { m_position_x = _pos.x; m_position_y = _pos.y; }
  void Set_position_x( double _x ) { m_position_x = _x; }
  void Set_position_y( double _y ) { m_position_y = _y; }
  void Add_position( glm::vec2 _pos) { m_position_x += _pos.x; m_position_y += _pos.y; }
  void Add_position_x( double _x ) { m_position_x += _x; }
  void Add_position_y( double _y ) { m_position_y += _y; }

  // --- Variables ---
 private:
  double m_position_x;
  double m_position_y;
};



#endif
