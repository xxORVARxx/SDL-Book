
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Init.h"



class Game_object
{
 public:
  void Draw() { std::cout << "Draw Game Object.\n"; }
  void Update() { std::cout << "Update Game Object.\n"; }
  void Clean() { std::cout << "Clean Game Object.\n"; }

 protected:
  int m_x;
  int m_y;

};



class Player : public Game_object
{
 public:
  void Draw() 
  {
    Game_object::Draw();
    std::cout << "Draw Player.\n"; 
  }
  void Update()
  {
    m_x = 10;
    m_y = 20;
    std::cout << "Update Player.  x:" << m_x << "  y:" << m_y << "\n"; 
  }
  void Clean()
  {
    Game_object::Clean();
    std::cout << "Clean Player.\n"; 
  }
};



#endif
