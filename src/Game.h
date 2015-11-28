
#ifndef GAME_H
#define GAME_H

#include "Init.h"
#include "Game_state_machine.h"



// Singleton Class:
class the_Game
{
 private:
  the_Game();
  the_Game( const the_Game& ) = delete;
  the_Game& operator=( const the_Game& ) = delete;

 public:
  ~the_Game() = default;

  static the_Game& Instance()
  {
    static the_Game instance;
    return instance;
  }

  bool Init( std::string _title, int _w, int _h );
  void Handle_events();
  void Update();
  void Render();
  void Clean();

  glm::vec2 Get_display_size() { return glm::vec2( m_width, m_height ); }
  int Get_width() { return m_width; }
  int Get_height() { return m_height; }
  SDL_Renderer* Get_renderer() const { return m_renderer_ptr; }
  Game_state_machine* Get_state_machine() { return &m_state_machine; }

  // --- Variables ---
 private:
  int m_width, m_height;
  SDL_Window* m_display_ptr;
  SDL_Renderer* m_renderer_ptr;
  Game_state_machine m_state_machine;
};



#endif
