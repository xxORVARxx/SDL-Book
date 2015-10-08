
#ifndef GAME_H
#define GAME_H

#include "Init.h"
#include "Game_state_machine.h"
#include "Objects_blueprint.h"



// Singleton Class:
class Game
{
 private:
  Game();
  ~Game();

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

  // --- Variables ---
 private:
  static Game* sm_instance_ptr;
  int m_color;
  int m_color_add;

  SDL_Window* m_display_ptr;
  SDL_Renderer* m_renderer_ptr;
  Game_state_machine m_state_machine;

  // Game Objects:
  std::vector< Object_default* > m_obj_vec;
};

typedef Game the_Game;



#endif
