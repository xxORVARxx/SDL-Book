
#include "Input_handler.h"



// --- Static Variables ---
Input_handler* Input_handler::sm_instance_ptr = NULL;



// --- Constructors ---
Input_handler::Input_handler()
{
  m_running = true;
  m_key_down = false;
  m_mouse_moving = false;
  m_mouse_button_down = false;
  for( Uint8 i = 0 ; i < 16 ; ++i )  m_mouse_buttons[i] = false;
  m_joystick_Deadzone = 10000;
}



// --- Functions ---
bool Input_handler::Update()
{
  m_keys_state = SDL_GetKeyboardState( NULL );
  m_mouse_moving = false;
  SDL_Event event;
  while( SDL_PollEvent( &event ))
    {
      switch( event.type ) 
	{
	  // --- QUIT ---
	case SDL_QUIT : 
	  m_running = false;
	  break;
	  // --- KEYBOARD ---
	case SDL_KEYDOWN :
	  m_key_down = true;
	  break;
	case SDL_KEYUP :
	  m_key_down = false;
	  break;
	  // --- MOUSE --- 
	case SDL_MOUSEMOTION :
	  m_mouse_moving = true;
	  m_mouse_position.x = event.motion.x;
	  m_mouse_position.y = event.motion.y;
	  break;
	case SDL_MOUSEBUTTONDOWN :
	  m_mouse_button_down = true;
	  m_mouse_buttons[ event.button.button ] = true;
	  break;
	case SDL_MOUSEBUTTONUP :
	  m_mouse_button_down = false;
	  m_mouse_buttons[ event.button.button ] = false;
	  break;
	case SDL_MOUSEWHEEL :
	  // missing
	  break;
	  // --- JOYSTICK  ---
	case SDL_JOYAXISMOTION :
	  on_Joystick_axis_move( event );
	  break;
	case SDL_JOYBUTTONDOWN :
	  on_Joystick_button_down( event );
	  break;
	case SDL_JOYBUTTONUP :
	  on_Joystick_button_up( event );
	  break;
	  // --- WINDOW ---
	case SDL_WINDOWEVENT :
	  on_Window_event( event );
	  break;
	}//switch-end
    }//while-end
}



void Input_handler::on_Joystick_axis_move( SDL_Event& event )
{
  // !!!!!!!!!!!!! NOT TESTED !!!!!!!!!!!!!!
  // This is based on the Xbox 360 Controller:
  int which_one = event.jaxis.which;
  switch( event.jaxis.axis )
    {
    case 0 :// Left-stick was moved: Left or Right.
      if( event.jaxis.value > m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].x = 1;
      else if( event.jaxis.value < -m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].x = -1;
      else
	m_joystick_values_vec[ which_one ].x = 0;
      break;
    case 1 :// Left-stick was moved: Up or Down.
      if( event.jaxis.value > m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].y = 1;
      else if( event.jaxis.value < -m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].y = -1;
      else
	m_joystick_values_vec[ which_one ].y = 0;
      break;
    case 3 :// Right-stick was moved: Left or Right.
      if( event.jaxis.value > m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].z = 1;
      else if( event.jaxis.value < -m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].z = -1;
      else
	m_joystick_values_vec[ which_one ].z = 0;
      break;
    case 4 :// Right-stick was moved: Up or Down.
      if( event.jaxis.value > m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].w = 1;
      else if( event.jaxis.value < -m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].w = -1;
      else
	m_joystick_values_vec[ which_one ].w = 0;
      break;
    }//switch-end
  std::cout << which_one 
	    << "  x:" << m_joystick_values_vec[ which_one ].x 
	    << "  y:" << m_joystick_values_vec[ which_one ].x 
	    << "  z:" << m_joystick_values_vec[ which_one ].z 
	    << "  w:" << m_joystick_values_vec[ which_one ].w << "\n";
}
void Input_handler::on_Joystick_button_down( SDL_Event& event )
{

}
void Input_handler::on_Joystick_button_up( SDL_Event& event )
{

}
void Input_handler::on_Window_event( SDL_Event& event )
{
  switch( event.window.event )
    {
    case SDL_WINDOWEVENT_SIZE_CHANGED : 
      // Width = event.window.data1;
      // Height = event.window.data2;
      break;
    case SDL_WINDOWEVENT_CLOSE :// The window-manager requests that the window be closed.
      event.type = SDL_QUIT;
      SDL_PushEvent(&event);
      break;
    }//switch-end
}



void Input_handler::Clean()
{
  if( m_joysticks_initialised )
    for( unsigned int i = 0 ; i < m_joystick_vec.size() ; ++i )
      SDL_JoystickClose( m_joystick_vec[i] );

  std::cout << "INPUT HANDLER :: Clean() is Done.\n";
}



void Input_handler::Initialise_joysticks()
{
  if( SDL_WasInit( SDL_INIT_JOYSTICK ) == 0 )
    SDL_InitSubSystem( SDL_INIT_JOYSTICK );

  if( SDL_NumJoysticks() > 0 ) {
    m_joysticks_initialised = false;
    return;
  }

  for( unsigned int i = 0 ; i < SDL_NumJoysticks() ; ++i )
    {
      SDL_Joystick* temp_joy = SDL_JoystickOpen(i);
      if( SDL_JoystickGetAttached( temp_joy ) == true ) {
	m_joystick_vec.push_back( temp_joy );
	m_joystick_values_vec.push_back( glm::vec4() );
      }
      else
	std::cout << "INPUT HANDLER :: !! Joystick Error : " << SDL_GetError() << " !!\n";  
    }
  SDL_JoystickEventState( SDL_ENABLE );
  m_joysticks_initialised = true;
  std::cout << "INPUT HANDLER :: Initialised: " << m_joystick_vec.size() << " joystick(s).\n";
}
