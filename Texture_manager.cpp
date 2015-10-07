
#include "Texture_manager.h"



// --- Static Variables ---
Texture_manager* Texture_manager::sm_instance_ptr = NULL;



// --- Functions ---
bool Texture_manager::Load( SDL_Renderer* s_renderer_ptr, std::string s_id, std::string s_file_name ) 
{
  SDL_Surface* temp_surface_ptr = NULL;
  temp_surface_ptr = IMG_Load( s_file_name.c_str() );
  if ( temp_surface_ptr == NULL ) {
    std::cout << "!! Failed to load image: '" << s_file_name <<  "'. Error : " << SDL_GetError() << " !!\n";  
    return false;
  }

  SDL_Texture* texture_ptr;
  texture_ptr = SDL_CreateTextureFromSurface( s_renderer_ptr, temp_surface_ptr );
  if ( texture_ptr == NULL ) {
    SDL_FreeSurface( temp_surface_ptr );
    std::cout << "!! Failed to load textur : " << SDL_GetError() << " !!\n";  
    return false;
  }
  SDL_FreeSurface( temp_surface_ptr );

  m_texture_map[ s_id ] = texture_ptr;

  //SDL_QueryTexture( m_texture_ptr, NULL, NULL, &m_sor_rec.w, &m_sor_rec.h );
}



void Texture_manager::Drow( SDL_Renderer* s_renderer_ptr, std::string s_id, int s_x, int s_y, int s_w, int s_h, 
			    SDL_RendererFlip s_flip ) 
{
  SDL_Rect src_rec; // Source Rectangle.
  SDL_Rect dest_rec; // Destination Rectangle.

  src_rec.x = 0;
  src_rec.y = 0;
  src_rec.w = dest_rec.w = s_w;
  src_rec.h = dest_rec.h = s_h;
  dest_rec.x = s_x;
  dest_rec.y = s_y;

  SDL_RenderCopyEx( s_renderer_ptr, m_texture_map[s_id], &src_rec, &dest_rec, 0, 0, s_flip );
}



// For "Sprite Sheet":
void Texture_manager::Drow_frame( SDL_Renderer* s_renderer_ptr, std::string s_id, int s_x, int s_y, int s_w, int s_h, 
				  int current_row, int current_frame, SDL_RendererFlip s_flip ) 
{
  SDL_Rect src_rec; // Source Rectangle.
  SDL_Rect dest_rec; // Destination Rectangle.

  src_rec.x = s_w * current_frame;
  src_rec.y = s_h * current_row;
  src_rec.w = dest_rec.w = s_w;
  src_rec.h = dest_rec.h = s_h;
  dest_rec.x = s_x;
  dest_rec.y = s_y;

  SDL_RenderCopyEx( s_renderer_ptr, m_texture_map[s_id], &src_rec, &dest_rec, 0, 0, s_flip );
}
