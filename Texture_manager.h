
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<string>
#include<map>



class Texture_manager
{
 public:
  bool Load( SDL_Renderer* s_renderer_ptr, std::string s_id, std::string s_file_name );

  // Draw:
  void Drow( SDL_Renderer* s_renderer_ptr, std::string s_id, int s_x, int s_y, int s_w, int s_h, 
	     SDL_RendererFlip s_flip = SDL_FLIP_NONE );

  // Draw Frame:
  void Drow_frame( SDL_Renderer* s_renderer_ptr, std::string s_id, int s_x, int s_y, int s_w, int s_h, 
		   int current_row, int current_frame, SDL_RendererFlip s_flip = SDL_FLIP_NONE );

  std::map< std::string, SDL_Texture* > m_texture_map;
};



#endif
