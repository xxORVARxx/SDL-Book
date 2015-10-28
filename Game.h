
#ifndef GAME_H
#define GAME_H

#include "Init.h"
#include "Game_state_machine.h"



// Singleton Class:
class Game
{
 private:
  Game();
  ~Game() {}

 public:
  static Game* Instance()
  {
    if( sm_instance_ptr == NULL )
      sm_instance_ptr = new Game();
    return sm_instance_ptr;
  }

  bool Init( std::string title, int w, int h );
  void Handle_events();
  void Update();
  void Render();
  void Clean();
  SDL_Renderer* Get_renderer() const { return m_renderer_ptr; }
  Game_state_machine* Get_state_machine() { return &m_state_machine; }

  // --- Variables ---
 private:
  static Game* sm_instance_ptr;

  SDL_Window* m_display_ptr;
  SDL_Renderer* m_renderer_ptr;
  Game_state_machine m_state_machine;
};



// Global Variable:
typedef Game the_Game;



#endif
