
#ifndef GAME_H
#define GAME_H

#include "Init.h"
#include "Objects_blueprint.h"



// Singleton Class:
class Game
{
 private:
  Game();

 public:
  ~Game();

  static Game* Instance()
  {
    if( sm_instance_ptr == NULL )
      {
	sm_instance_ptr = new Game();
	return sm_instance_ptr;
      }
    return sm_instance_ptr;
  }

  bool Init( std::string title, int w, int h );
  void Handle_events();
  void Update();
  void Render();
  void Clean();
  SDL_Renderer* Get_renderer() const { return m_renderer_ptr; }

  // --- Variables ---
  bool m_running;

  private:
  static Game* sm_instance_ptr;
  SDL_Window* m_display_ptr;
  SDL_Renderer* m_renderer_ptr;

  int m_color;
  int m_color_add;

  // Game Objects:
  std::vector< Object_default* > m_obj_vec;
};



#endif
