
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Init.h"



// Singleton Class:
class Texture_manager
{
 private:
  Texture_manager() {}
  ~Texture_manager() {}

 public:
  static Texture_manager* Instance()
  {
    if( sm_instance_ptr == NULL )
      sm_instance_ptr = new Texture_manager();
    return sm_instance_ptr;
  }

  void Test() { std::cout <<"Test\n"; }

  // Load Texture:
  bool Load( SDL_Renderer* s_renderer_ptr, std::string s_id, std::string s_file_name );

  // Draw:
  void Drow( SDL_Renderer* s_renderer_ptr, std::string s_id, int s_x, int s_y, int s_w, int s_h, 
	     SDL_RendererFlip s_flip = SDL_FLIP_NONE );

  // Draw Frame:
  void Drow_frame( SDL_Renderer* s_renderer_ptr, std::string s_id, int s_x, int s_y, int s_w, int s_h, 
		   int current_row, int current_frame, SDL_RendererFlip s_flip = SDL_FLIP_NONE );

  // --- Variables ---
  static Texture_manager* sm_instance_ptr;
  std::map< std::string, SDL_Texture* > m_texture_map;
};



// Global Variable:
typedef Texture_manager the_Texture_manager;



#endif
