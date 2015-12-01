
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Init.h"



// Singleton Class:
class the_Input_handler
{
 private:
  the_Input_handler();
  the_Input_handler( const the_Input_handler& ) = delete;
  the_Input_handler& operator=( const the_Input_handler& ) = delete;

 public:
  ~the_Input_handler() = default;

  static the_Input_handler& Instance()
  {
    static the_Input_handler instance;
    return instance;
  }

  // --- Functions ---
  bool Update();
  void Clean();

  void Quit() { m_running = false; }
  bool is_Running() { return m_running; }

  // Keyboard:
  const Uint8* Get_keys_state() { return m_keys_state; }

  // Mouse:
  bool is_Mouse_moving() { return m_mouse_moving; }
  const glm::vec2& Get_mouse_position() { return m_mouse_position; }
  bool is_Mouse_button_down() { return m_mouse_button_down; }
  bool Get_mouse_button( Uint8 sdl_button_flag ) { return m_mouse_buttons[ sdl_button_flag ]; }
  // Joystick:
  void Initialise_joysticks();
  bool is_Joystick_initialised() { return m_joysticks_initialised; }
  const glm::vec4& Get_joystick_values( int joystick_id ) { return m_joystick_values_vec[ joystick_id ]; }

 private:
  // Handle Joystick & Window Events:
  void on_Joystick_axis_move( SDL_Event& event );
  void on_Joystick_button_down( SDL_Event& event );
  void on_Joystick_button_up( SDL_Event& event );
  void on_Window_event( SDL_Event& event );

  // --- Variables ---
  bool m_running;
  // Keyboard:
  const Uint8* m_keys_state;
  // Mouse:
  bool m_mouse_moving;
  glm::vec2 m_mouse_position;
  bool m_mouse_button_down;
  bool m_mouse_buttons[16];
  // Joystick:
  bool m_joysticks_initialised;
  std::vector< SDL_Joystick* > m_joystick_vec;
  std::vector< glm::vec4 > m_joystick_values_vec;
  int m_joystick_Deadzone;
};



#endif

/*
  These are the SDL mouse buttons: (SDL_MouseButtonEvent) 
  SDL_BUTTON_LEFT
  SDL_BUTTON_MIDDLE
  SDL_BUTTON_RIGHT
  SDL_BUTTON_X1
  SDL_BUTTON_X2
*/
