
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Init.h"



// Singleton Class:
class the_Texture_manager
{
 private:
  the_Texture_manager() = default;
  the_Texture_manager( const the_Texture_manager& ) = delete;
  the_Texture_manager& operator=( const the_Texture_manager& ) = delete;

 public:
  ~the_Texture_manager() = default;

  static the_Texture_manager& Instance()
  {
    static the_Texture_manager instance;
    return instance;
  }

  // Load Texture:
  bool Load( SDL_Renderer* _renderer_ptr, std::string _id, std::string _file_name );
  // Draw:
  void Drow( SDL_Renderer* _renderer_ptr, std::string _id, int _x, int _y, int _w, int _h, 
	     SDL_RendererFlip _flip = SDL_FLIP_NONE );
  // Draw Frame:
  void Drow_frame( SDL_Renderer* _renderer_ptr, std::string _id, int _x, int _y, int _w, int _h, 
		   int _current_row, int _current_frame, SDL_RendererFlip _flip = SDL_FLIP_NONE );
  void Clean();

 private:
  // --- Variables ---
  std::map< const std::string, SDL_Texture* > m_texture_map;
};



#endif
