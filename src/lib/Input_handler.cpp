
#include "Input_handler.h"



// --- Constructors ---
the_Input_handler::the_Input_handler() 
{
  m_running = true;
  m_mouse_moving = false;
  m_mouse_button_down = false;
  for( Uint8 i = 0 ; i < 16 ; ++i )  m_mouse_buttons[i] = false;
  m_joystick_Deadzone = 10000;
  mf_Callback_on_display_resize = nullptr;
}



// --- Functions ---
bool the_Input_handler::Update()
{
  m_keys_state = SDL_GetKeyboardState( nullptr );
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
	  break;
	case SDL_KEYUP :
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
	  this->on_Joystick_axis_move( event );
	  break;
	case SDL_JOYBUTTONDOWN :
	  this->on_Joystick_button_down( event );
	  break;
	case SDL_JOYBUTTONUP :
	  this->on_Joystick_button_up( event );
	  break;
	  // --- WINDOW ---
	case SDL_WINDOWEVENT :
	  this->on_Window_event( event );
	  break;
	}//switch-end
    }//while-end
}



void the_Input_handler::Clean()
{
  if( m_joysticks_initialised )
    for( unsigned int i = 0 ; i < m_joystick_vec.size() ; ++i )
      SDL_JoystickClose( m_joystick_vec[i] );

  std::cout << "INPUT HANDLER :: Clean() is Done.\n";
}



void the_Input_handler::on_Joystick_axis_move( SDL_Event& _event )
{
  // !!!!!!!!!!!!! NOT TESTED !!!!!!!!!!!!!!
  // This is based on the Xbox 360 Controller:
  int which_one = _event.jaxis.which;
  switch( _event.jaxis.axis )
    {
    case 0 :// Left-stick was moved: Left or Right.
      if( _event.jaxis.value > m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].x = 1;
      else if( _event.jaxis.value < -m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].x = -1;
      else
	m_joystick_values_vec[ which_one ].x = 0;
      break;
    case 1 :// Left-stick was moved: Up or Down.
      if( _event.jaxis.value > m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].y = 1;
      else if( _event.jaxis.value < -m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].y = -1;
      else
	m_joystick_values_vec[ which_one ].y = 0;
      break;
    case 3 :// Right-stick was moved: Left or Right.
      if( _event.jaxis.value > m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].z = 1;
      else if( _event.jaxis.value < -m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].z = -1;
      else
	m_joystick_values_vec[ which_one ].z = 0;
      break;
    case 4 :// Right-stick was moved: Up or Down.
      if( _event.jaxis.value > m_joystick_Deadzone )
	m_joystick_values_vec[ which_one ].w = 1;
      else if( _event.jaxis.value < -m_joystick_Deadzone )
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
void the_Input_handler::on_Joystick_button_down( SDL_Event& _event )
{

}
void the_Input_handler::on_Joystick_button_up( SDL_Event& _event )
{

}
void the_Input_handler::on_Window_event( SDL_Event& _event )
{
  switch( _event.window.event )
    {
    case SDL_WINDOWEVENT_SIZE_CHANGED :
      if( mf_Callback_on_display_resize != nullptr )
	mf_Callback_on_display_resize( _event.window.data1, _event.window.data2 );
      // Width = _event.window.data1;
      // Height = _event.window.data2;
      break;
    case SDL_WINDOWEVENT_CLOSE :// The window-manager requests that the window be closed.
      _event.type = SDL_QUIT;
      SDL_PushEvent( &_event );
      break;
    }//switch-end
}



void the_Input_handler::Initialise_joysticks()
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



void the_Input_handler::Set_callback_on_display_resize( void(* _Callback )( int _w, int _h ) )
{
  mf_Callback_on_display_resize = _Callback;
}
