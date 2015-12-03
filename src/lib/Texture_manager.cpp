
#include "Texture_manager.h"



// --- Texture Data ---
Texture_data::Texture_data() : 
  texture_width(0), texture_height(0), texture(nullptr) {}

Texture_data::Texture_data( int _w, int _h, SDL_Texture* _t ) : 
  texture_width(_w), texture_height(_h), texture(_t) {}

Texture_data::Texture_data( const Texture_data& _data ) : 
  texture_width(_data.texture_width), texture_height(_data.texture_height), texture(_data.texture) {}

Texture_data& Texture_data::operator= ( const Texture_data& _data )
{ 
  if( this == &_data )
    return *this; 
  texture_width = _data.texture_width;
  texture_height = _data.texture_height;
  texture = _data.texture;
  return *this; 
}

int Texture_data::Get_width()
{
  return texture_width;
}

int Texture_data::Get_height()
{
  return texture_height;
}

SDL_Texture* Texture_data::Get_texture()
{
  return texture;
}



// --- Texture Manager ---
 glm::vec2 the_Texture_manager::Get_image_size( std::string _id )
 {
   std::map< const std::string, Texture_data >::iterator it = m_texture_map.find( _id );
   if( it == m_texture_map.end() )
     {
       std::cout << "TEXTURE MANAGER :: Texture not found! No Texture with this ID: '"<< _id <<"'.\n";
       return glm::vec2( 0, 0 );
     }
   return glm::vec2( it->second.Get_width(), it->second.Get_height());
 }



bool the_Texture_manager::Load_image( SDL_Renderer* _renderer_ptr, std::string _id, std::string _file_name ) 
{
  if( m_texture_map.find( _id ) != m_texture_map.end()) {
    std::cout << "TEXTURE MANAGER :: Texture is already loaded, or this: '"<< _id <<"' id is being used for another Texture.\n";
    return false;
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

  m_texture_map[ _id ] = Texture_data( temp_surface_ptr->w, temp_surface_ptr->h, texture_ptr );

  SDL_FreeSurface( temp_surface_ptr );
  temp_surface_ptr = nullptr;//NULL
  return true;
}



void the_Texture_manager::Draw( SDL_Renderer* _renderer_ptr, std::string _id, glm::vec2 _position, glm::vec2 _size, 
				SDL_RendererFlip _flip )
{
  std::map< const std::string, Texture_data >::iterator it = m_texture_map.find( _id );
  if( it == m_texture_map.end() )
    {
      std::cout << "TEXTURE MANAGER :: Texture not found! No Texture with this ID: '"<< _id <<"'.\n";
      return;
    }
  SDL_Rect src_rec; // Source Rectangle.
  SDL_Rect dest_rec; // Destination Rectangle.
  src_rec.x = 0;
  src_rec.y = 0;
  src_rec.w = it->second.Get_width();
  src_rec.h = it->second.Get_height();
  dest_rec.x = _position.x;
  dest_rec.y = _position.y;
  dest_rec.w = _size.x;
  dest_rec.h = _size.y;

  if( _flip == SDL_FLIP_NONE )
    SDL_RenderCopy( _renderer_ptr, it->second.Get_texture(), &src_rec, &dest_rec );
  else
    SDL_RenderCopyEx( _renderer_ptr, it->second.Get_texture(), &src_rec, &dest_rec, 0, nullptr, _flip );
}



// For Sprite Sheets:
void the_Texture_manager::Draw_frame( SDL_Renderer* _renderer_ptr, std::string _id, glm::vec2 _position, glm::vec2 _size,
				      int _frame_width, int _frame_height, int _frame_number, int _row_number, 
				      SDL_RendererFlip _flip )
{
  std::map< const std::string, Texture_data >::iterator it = m_texture_map.find( _id );
  if( it == m_texture_map.end() )
    {
      std::cout << "TEXTURE MANAGER :: Texture not found! No Texture with this ID: '"<< _id <<"'.\n";
      return;
    }
  SDL_Rect src_rec; // Source Rectangle.
  SDL_Rect dest_rec; // Destination Rectangle.
  src_rec.x = ( _frame_width * ( _frame_number - 1 ));
  src_rec.y = ( _frame_height * ( _row_number - 1 ));
  src_rec.w = _frame_width;
  src_rec.h = _frame_height;
  dest_rec.x = _position.x;
  dest_rec.y = _position.y;
  dest_rec.w = _size.x;
  dest_rec.h = _size.y;

  if( _flip == SDL_FLIP_NONE )
    SDL_RenderCopy( _renderer_ptr, it->second.Get_texture(), &src_rec, &dest_rec );
  else
    SDL_RenderCopyEx( _renderer_ptr, it->second.Get_texture(), &src_rec, &dest_rec, 0, nullptr, _flip );
}



void the_Texture_manager::Draw_frame_rot( SDL_Renderer* _renderer_ptr, std::string _id, glm::vec2 _position, glm::vec2 _size,
					  int _frame_width, int _frame_height, int _frame_number, int _row_number, 
					  double _angle, double _divide_width, double _divide_height, 
					  SDL_RendererFlip _flip )
{
  std::map< const std::string, Texture_data >::iterator it = m_texture_map.find( _id );
  if( it == m_texture_map.end() )
    {
      std::cout << "TEXTURE MANAGER :: Texture not found! No Texture with this ID: '"<< _id <<"'.\n";
      return;
    }
  SDL_Rect src_rec; // Source Rectangle.
  SDL_Rect dest_rec; // Destination Rectangle.
  src_rec.x = ( _frame_width * ( _frame_number - 1 ));
  src_rec.y = ( _frame_height * ( _row_number - 1 ));
  src_rec.w = _frame_width;
  src_rec.h = _frame_height;
  dest_rec.x = _position.x;
  dest_rec.y = _position.y;
  dest_rec.w = _size.x;
  dest_rec.h = _size.y;

  if( _divide_width == 0 )  
    _divide_width = _size.x;
  if( _divide_height == 0 )  
    _divide_height = _size.y;
  SDL_Point center_rec; // Point to Rotate Around.
  center_rec.x = _size.x / _divide_width;
  center_rec.y = _size.y / _divide_height;

  SDL_RenderCopyEx( _renderer_ptr, it->second.Get_texture(), &src_rec, &dest_rec, _angle, &center_rec, _flip );
}



void the_Texture_manager::Clean()
{
  // Deleting Textures:
  std::for_each( m_texture_map.begin(), m_texture_map.end(), 
		 []( std::pair< const std::string, Texture_data >& i ){ SDL_DestroyTexture( i.second.Get_texture() ); } );
  m_texture_map.clear();
}

