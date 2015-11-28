
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Init.h"



struct Texture_data
{
  Texture_data();
  ~Texture_data() {}
  Texture_data( int _w, int _h, SDL_Texture* _t );
  Texture_data( const Texture_data& _data );
  Texture_data& operator= ( const Texture_data& _data );

  int Get_width();
  int Get_height();
  SDL_Texture* Get_texture();

private:
  int texture_width;
  int texture_height;
  SDL_Texture* texture;
};



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

  glm::vec2 Get_image_size( std::string _id );
  bool Load_image( SDL_Renderer* _renderer_ptr, std::string _id, std::string _file_name );

  void Draw( SDL_Renderer* _renderer_ptr, std::string _id, glm::vec2 _position, glm::vec2 _size, 
	     SDL_RendererFlip _flip = SDL_FLIP_NONE );

  void Draw_frame( SDL_Renderer* _renderer_ptr, std::string _id, glm::vec2 _position, glm::vec2 _size,
		   int _frame_width, int _frame_height, int _frame_number, int _row_number, 
		   SDL_RendererFlip _flip = SDL_FLIP_NONE );
  /*
  // Draw Frame:
  void Draw_frame( SDL_Renderer* _renderer_ptr, std::string _id, int _x, int _y, int _w, int _h, 
		   int _current_row, int _current_frame, SDL_RendererFlip _flip = SDL_FLIP_NONE );
  */
  void Clean();

 private:
  // --- Variables ---
  std::map< const std::string, Texture_data > m_texture_map;
};



#endif
