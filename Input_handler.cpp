
#include "Input_handler.h"



// --- Static Variables ---
Input_handler* Input_handler::sm_instance_ptr = NULL;



// --- Constructors ---
Input_handler::Input_handler()
{
  m_running = true;
  key_down = false;
  mouse_moving = false;
  mouse_button_down = false;
  for( Uint8 i = 0 ; i < 16 ; ++i )  mouse_buttons[i] = false;
  m_joystick_Deadzone = 10000;
}



// --- Functions ---
bool Input_handler::Update()
{
  mouse_moving = false;
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
	  key_down = true;
	  break;
	case SDL_KEYUP :
	  key_down = false;
	  break;
	  // --- MOUSE --- 
	case SDL_MOUSEMOTION :
	  mouse_moving = true;
	  mouse_position.x = event.motion.x;
	  mouse_position.y = event.motion.y;
	  break;
	case SDL_MOUSEBUTTONDOWN :
	  mouse_button_down = true;
	  mouse_buttons[ event.button.button ] = true;
	  break;
	case SDL_MOUSEBUTTONUP :
	  mouse_button_down = false;
	  mouse_buttons[ event.button.button ] = false;
	  break;
	case SDL_MOUSEWHEEL :

	  break;
	  // --- JOYSTICK  ---mm!!!!!!!!!!!!! NOT TESTED !!!!!!!!!!!!!!
	case SDL_JOYAXISMOTION :
	  {
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
	    break;
	  }
	  // --- WINDOW ---
	case SDL_WINDOWEVENT :
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
	  break;
	}//switch-end
    }//while-end
}



void Input_handler::Clean()
{
  if( m_joysticks_initialised )
    for( unsigned int i = 0 ; i < m_joystick_vec.size() ; ++i )
      SDL_JoystickClose( m_joystick_vec[i] );

  std::cout << "Input_handler.Clean() Done\n";
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
	std::cout << "!! Joystick Error : " << SDL_GetError() << " !!\n";  
    }
  SDL_JoystickEventState( SDL_ENABLE );
  m_joysticks_initialised = true;
  std::cout << "Initialised: " << m_joystick_vec.size() << " joystick(s)\n";
}
