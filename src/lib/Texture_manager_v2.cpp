
#include "Texture_manager_v2.h"



the_Texture_manager_v2::the_Texture_manager_v2()
{
  current = 0;
}



void 
the_Texture_manager_v2::Swap_maps()
{
  current = ! current;
}



bool 
the_Texture_manager_v2::Move_or_load_texture( SDL_Renderer* _renderer_ptr, 
					      const std::string& _id, 
					      const std::string& _file_name ) 
{
  if( this->Has_texture( _id ))
    {
      std::cout <<"TEXTURE MANAGER-V2 :: Texture is already loaded, or this ID: '"
		<< _id <<"' is being used for another Texture.\n";
      return false;
    }

  std::map< const std::string, SDL_Texture* >::iterator itr = m_texture_map_arr[!current].end();
  if( this->Find_texture( _id, itr, ! current ))
    {
      assert( itr != m_texture_map_arr[!current].end());//ASSERT.
      m_texture_map_arr[current][ _id ] = itr->second;
      m_texture_map_arr[!current].erase( itr );
      std::cout <<"TEXTURE MANAGER-V2 :: Texture Moved.\n";
      return true;
    }
  return this->Image_loader( _renderer_ptr, _id, _file_name );
}



bool 
the_Texture_manager_v2::Load_texture( SDL_Renderer* _renderer_ptr, 
				      const std::string& _id, 
				      const std::string& _file_name )
{
  if( this->Has_texture( _id ))
    {
      std::cout <<"TEXTURE MANAGER-V2 :: Texture is already loaded, or this ID: '"
		<< _id <<"' is being used for another Texture.\n";
      return false;
    }
  return this->Image_loader( _renderer_ptr, _id, _file_name );
}



void 
the_Texture_manager_v2::Clear_map()
{
  // Deleting Textures:
  std::for_each( m_texture_map_arr[!current].begin(), m_texture_map_arr[!current].end(), 
		 []( std::pair< const std::string, SDL_Texture* >& i ){ SDL_DestroyTexture( i.second ); } );
  m_texture_map_arr[!current].clear();
}

void 
the_Texture_manager_v2::Clear_current_map()
{
  // Deleting Textures:
  std::for_each( m_texture_map_arr[current].begin(), m_texture_map_arr[current].end(), 
		 []( std::pair< const std::string, SDL_Texture* >& i ){ SDL_DestroyTexture( i.second ); } );
  m_texture_map_arr[current].clear();
}



bool 
the_Texture_manager_v2::Has_texture( const std::string& _id )
{
  return this->Has_texture( _id, current );
}

bool 
the_Texture_manager_v2::Has_texture( const std::string& _id, 
				     bool _map )
{
  if( m_texture_map_arr[_map].find( _id ) == m_texture_map_arr[_map].end())
    return false; // Did not find texture.
  return true;
}



bool 
the_Texture_manager_v2::Get_texture( const std::string& _id, 
				     SDL_Texture*& _texture_ptr )
{
  return this->Get_texture( _id, _texture_ptr, current );
}

bool 
the_Texture_manager_v2::Get_texture( const std::string& _id, 
				     SDL_Texture*& _texture_ptr, 
				     bool _map )
{
  std::map< const std::string, SDL_Texture* >::iterator itr = m_texture_map_arr[_map].end();
  if( this->Find_texture( _id, itr, _map ))
    {
      assert( itr != m_texture_map_arr[_map].end());//ASSERT.
      _texture_ptr = itr->second;
      return true;
    }
  _texture_ptr = nullptr;//NULL
  return false; // Did not find texture.
}



void 
the_Texture_manager_v2::Erase_texture( const std::string& _id )
{
  this->Erase_texture( _id, current );
}

void 
the_Texture_manager_v2::Erase_texture( const std::string& _id, 
				       bool _map )
{
  std::map< const std::string, SDL_Texture* >::iterator itr = m_texture_map_arr[_map].end();
  if( this->Find_texture( _id, itr, _map ))
    {
      assert( itr != m_texture_map_arr[_map].end());//ASSERT.
      SDL_DestroyTexture( itr->second );
      m_texture_map_arr[_map].erase( itr ); 
    }
}



bool 
the_Texture_manager_v2::Get_current_map()
{
  return current;
}



bool 
the_Texture_manager_v2::Get_texture_size( const std::string& _id, 
					  SDL_Point& _size )
{
  SDL_Texture* texture_ptr = nullptr;//NULL
  if( Get_texture( _id, texture_ptr ))
    {
      assert( texture_ptr != nullptr );//ASSERT.
      SDL_QueryTexture( texture_ptr, nullptr, nullptr, &_size.x, &_size.y );
      return true;
    }
  _size.x = 0;
  _size.y = 0;
  return false;
}



void 
the_Texture_manager_v2::Clean()
{
  this->Clear_current_map();
  this->Clear_map();
  std::cout <<"TEXTURE MANAGER-V2 :: Clean() is Done.\n";
}



bool 
the_Texture_manager_v2::Find_texture( const std::string& _id, 
				      std::map< const std::string, SDL_Texture* >::iterator& _itr )
{
  return this->Find_texture( _id, _itr, current );
}

bool 
the_Texture_manager_v2::Find_texture( const std::string& _id, 
				      std::map< const std::string, SDL_Texture* >::iterator& _itr, 
				      bool _map )
{
  _itr = m_texture_map_arr[_map].find( _id );
  if( _itr == m_texture_map_arr[_map].end() )
    return false; // Did not find texture.
  return true;
}



bool 
the_Texture_manager_v2::Image_loader( SDL_Renderer* _renderer_ptr, 
				      const std::string& _id, 
				      const std::string& _file_name )
{
  SDL_Surface* temp_surface_ptr = nullptr;//NULL
  temp_surface_ptr = IMG_Load( _file_name.c_str() );
  if ( temp_surface_ptr == nullptr ) 
    {
      std::cout <<"TEXTURE MANAGER-V2 :: Failed to load image: '"<< _file_name 
		<<"'. Error : "<< SDL_GetError() <<" !!\n";  
      return false;
    }

  SDL_Texture* texture_ptr = nullptr;//NULL
  texture_ptr = SDL_CreateTextureFromSurface( _renderer_ptr, temp_surface_ptr );
  if ( texture_ptr == nullptr ) 
    {
      SDL_FreeSurface( temp_surface_ptr );
      std::cout <<"TEXTURE MANAGER-V2 :: Failed to create textur : "<< SDL_GetError() <<" !!\n";  
      return false;
    }  

  m_texture_map_arr[current][ _id ] = texture_ptr;
  std::cout <<"TEXTURE MANAGER-V2 :: Texture Loaded.\n";

  SDL_FreeSurface( temp_surface_ptr );
  temp_surface_ptr = nullptr;//NULL
  return true;
}
