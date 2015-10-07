
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Init.h"



// Singleton Class:
class Input_handler
{
 private:
  Input_handler();
  ~Input_handler() {}

 public:
  static Input_handler* Instance()
  {
    if( sm_instance_ptr == NULL )
      sm_instance_ptr = new Input_handler();
    return sm_instance_ptr;
  }

  bool Update();
  void Clean();
  void Quit() { m_running = false; }
  bool Running() { return m_running; }
  // Keyboard:
  bool Key_down() { return key_down; }
  // Mouse:
  bool Mouse_moving() { return mouse_moving; }
  const glm::vec2& Mouse_position() { return mouse_position; }
  bool Mouse_button_down() { return mouse_button_down; }
  bool Get_mouse_button( Uint8 sdl_button_flag ) { return mouse_buttons[ sdl_button_flag ]; }
  // Joystick:
  void Initialise_joysticks();
  bool Joystick_initialised() { return m_joysticks_initialised; }
  const glm::vec4& Get_joystick_values( int id ) { return m_joystick_values_vec[ id ]; }

 private:
  // --- Variables ---
  static Input_handler* sm_instance_ptr;
  bool m_running;
  // Keyboard:
  bool key_down;
  // Mouse:
  bool mouse_moving;
  glm::vec2 mouse_position;
  bool mouse_button_down;
  bool mouse_buttons[16];
  // Joystick:
  bool m_joysticks_initialised;
  std::vector< SDL_Joystick* > m_joystick_vec;
  std::vector< glm::vec4 > m_joystick_values_vec;
  int m_joystick_Deadzone;
};

typedef Input_handler the_Input_handler;



#endif

/*
  These are the SDL mouse buttons: (SDL_MouseButtonEvent) 
  SDL_BUTTON_LEFT
  SDL_BUTTON_MIDDLE
  SDL_BUTTON_RIGHT
  SDL_BUTTON_X1
  SDL_BUTTON_X2
*/
