
#include "Texture_manager.h"



// --- Functions ---
bool the_Texture_manager::Load( SDL_Renderer* _renderer_ptr, std::string _id, std::string _file_name ) 
{
  if( m_texture_map.find( _id ) != m_texture_map.end()) {
    std::cout << "TEXTURE MANAGER :: Texture is already loaded, or this: '"<< _id <<"' id is being used for another Texture.\n";
    return true;
  }

  SDL_Surface* temp_surface_ptr = nullptr;//NULL
  temp_surface_ptr = IMG_Load( _file_name.c_str() );
  if ( temp_surface_ptr == nullptr ) {
    std::cout << "TEXTURE MANAGER :: Failed to load image: '" << _file_name <<  "'. Error : " << SDL_GetError() << " !!\n";  
    return false;
  }

  SDL_Texture* texture_ptr = nullptr;//NULL
  texture_ptr = SDL_CreateTextureFromSurface( _renderer_ptr, temp_surface_ptr );
  if ( texture_ptr == nullptr ) {
    SDL_FreeSurface( temp_surface_ptr );
    std::cout << "TEXTURE MANAGER :: Failed to create textur : " << SDL_GetError() << " !!\n";  
    return false;
  }
  SDL_FreeSurface( temp_surface_ptr );
  temp_surface_ptr = nullptr;//NULL

  m_texture_map[ _id ] = texture_ptr;

  //SDL_QueryTexture( m_texture_ptr, NULL, NULL, &m_sor_rec.w, &m_sor_rec.h );
}



void the_Texture_manager::Drow( SDL_Renderer* _renderer_ptr, std::string _id, int _x, int _y, int _w, int _h, 
				SDL_RendererFlip _flip ) 
{
  SDL_Rect src_rec; // Source Rectangle.
  SDL_Rect dest_rec; // Destination Rectangle.

  src_rec.x = 0;
  src_rec.y = 0;
  src_rec.w = dest_rec.w = _w;
  src_rec.h = dest_rec.h = _h;
  dest_rec.x = _x;
  dest_rec.y = _y;

  std::map< const std::string, SDL_Texture* >::iterator it = m_texture_map.find( _id );
  if( it != m_texture_map.end() )
    SDL_RenderCopyEx( _renderer_ptr, it->second, &src_rec, &dest_rec, 0, 0, _flip );
}



// For "Sprite Sheet":
void the_Texture_manager::Drow_frame( SDL_Renderer* _renderer_ptr, std::string _id, int _x, int _y, int _w, int _h, 
				      int _current_row, int _current_frame, SDL_RendererFlip _flip ) 
{
  SDL_Rect src_rec; // Source Rectangle.
  SDL_Rect dest_rec; // Destination Rectangle.

  src_rec.x = _w * _current_frame;
  src_rec.y = _h * _current_row;
  src_rec.w = dest_rec.w = _w;
  src_rec.h = dest_rec.h = _h;
  dest_rec.x = _x;
  dest_rec.y = _y;

  std::map< const std::string, SDL_Texture* >::iterator it = m_texture_map.find( _id );
  if( it != m_texture_map.end() )
    SDL_RenderCopyEx( _renderer_ptr, it->second, &src_rec, &dest_rec, 0, 0, _flip );
}



void the_Texture_manager::Clean()
{
  // Deleting Textures:
  std::for_each( m_texture_map.begin(), m_texture_map.end(), 
		 []( std::pair< const std::string, SDL_Texture* >& i ){ SDL_DestroyTexture( i.second ); } );
  m_texture_map.clear();
}
