
#include "Game.h"
#include "Input_handler.h"
#include "Texture_manager.h"
#include "Objects.h"



// --- Static Variables ---
Game* Game::sm_instance_ptr = NULL;



// --- Constructors ---
Game::Game()
{
  m_display_ptr = NULL;
  m_renderer_ptr = NULL;

  m_color = 0;
  m_color_add = 2;
}
Game::~Game()
{
  Clean();
}



// --- Functions ---
bool Game::Init( std::string s_title, int s_w, int s_h )
{
  // Initializing_SDL2:
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    std::cout << "!! Failed to initialize SDL : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_display_ptr = SDL_CreateWindow( s_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				    s_w, s_h, SDL_WINDOW_RESIZABLE );
  if ( m_display_ptr == NULL ) {
    std::cout << "!! Failed to create window : " << SDL_GetError() << " !!\n";  
    return false;
  }

  m_renderer_ptr = SDL_CreateRenderer( m_display_ptr, -1, SDL_RENDERER_ACCELERATED );
  if ( m_renderer_ptr == NULL ) {
    std::cout << "!! Failed to create renderer : " << SDL_GetError() << " !!\n";  
    return false;
  }


  // Opening Inputh Handler:
  the_Input_handler::Instance()->Initialise_joysticks();


  // Loading Texture with the "Singleton Class":
  the_Texture_manager::Instance()->Load( m_renderer_ptr, "Alien", "assets/Alien_sprite_sheet.png" );


  // Make Objects:
  Object_load_parameters olp1( "Alien", glm::vec2( 0, 0 ), ( 2096/8 ), ( 786/3 ) );
  Object_load_parameters olp2( "Alien", glm::vec2( 200, 0 ), ( 2096/8 ), ( 786/3 ) );
  Object_load_parameters olp3( "Alien", glm::vec2( 400, 0 ), ( 2096/8 ), ( 786/3 ) );

  m_obj_vec.push_back( new Object_default( &olp1 ));
  m_obj_vec.push_back( new Player( &olp2 ));
  m_obj_vec.push_back( new Enemy( &olp3 ));


  return true;
}



void Game::Handle_events()
{
  // Inputh Handler:
  the_Input_handler::Instance()->Update();
}



void Game::Update()
{
  // Updating the Game Objects:
  for ( int i = 0 ; i < m_obj_vec.size() ; ++i )
    m_obj_vec[i]->Update();


  // Background:
  m_color += m_color_add;
  if (( m_color >= 150 )||( m_color <= 0  ))
    m_color_add *= -1;
}



void Game::Render()
{
  SDL_SetRenderDrawColor( m_renderer_ptr, m_color, 0, 0, 255 );
  SDL_RenderClear( m_renderer_ptr );


  // Rendering the Game Objects:
  for ( int i = 0 ; i < m_obj_vec.size() ; ++i )
    m_obj_vec[i]->Draw();


  SDL_RenderPresent( m_renderer_ptr );
}



void Game::Clean()
{
  // Deleting Oblects:
  for ( int i = 0 ; i < m_obj_vec.size() ; ++i ) {
    m_obj_vec[i]->Clean();
    delete m_obj_vec[i];
    m_obj_vec[i] = NULL;
  }
  
  // Closing Inputh Handler:
  the_Input_handler::Instance()->Clean();

  // Closing SDL:
  SDL_DestroyRenderer( m_renderer_ptr );
  SDL_DestroyWindow( m_display_ptr );
  SDL_Quit();
  std::cout << "Game.Clean() Done\n";
}
