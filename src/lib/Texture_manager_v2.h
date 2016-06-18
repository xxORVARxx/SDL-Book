
#ifndef TEXTURE_MANAGER_V2_H
#define TEXTURE_MANAGER_V2_H

#include "Init.h"



// Singleton Class:
class the_Texture_manager_v2
{
private:
  the_Texture_manager_v2();

  the_Texture_manager_v2( const the_Texture_manager_v2& ) = delete;
  the_Texture_manager_v2& operator=( const the_Texture_manager_v2& ) = delete;

public:
  ~the_Texture_manager_v2() = default;

  static the_Texture_manager_v2& Instance()
  {
    static the_Texture_manager_v2 instance;
    return instance;
  }

  // --- --- FUNCTIONS --- ---
  /* Swap between the two texture-maps. 
   * It will change which is the current texture-maps.
   * Do this before updating what textures are being used: */
  void Swap_maps();

  /* This will TAKE a textures from the not-in-use texture-map 
   * and MOVE it into the current texture-map, 
   * If the texture isn't in the not-in-use texture-map,
   * a file is used insted, to load the texture into the current texture-map. 
   * Do this to update what textures are being used:*/
  bool Move_or_load_texture( SDL_Renderer* _renderer_ptr, 
			     const std::string& _id, 
			     const std::string& _file_name );

  /* This will load a texture from a file and into the current texture-map,
   * without checking if the texture is already loaded in the 
   * not-in-use texture-map: */
  bool Load_texture( SDL_Renderer* _renderer_ptr, 
		     const std::string& _id, 
		     const std::string& _file_name );

  /* Delete all the textures from the not-in-use texture-map,
   * leaving it empty. 
   * Do this after updating what textures are being used: */
  void Clear_map();

  /* Delete all the textures from the current texture-map,
   * leaving it empty: */
  void Clear_current_map();


  /* Use these to check if a texture with this id has already been loaded: */
  bool Has_texture( const std::string& _id );
  bool Has_texture( const std::string& _id, 
		    bool _map );

  /* Use these to get a texture from the maps: */
  bool Get_texture( const std::string& _id, 
		    SDL_Texture*& _texture );
  bool Get_texture( const std::string& _id, 
		    SDL_Texture*& _texture, 
		    bool _map );

  /* Use these to delete a texture from the maps: */
  void Erase_texture( const std::string& _id );
  void Erase_texture( const std::string& _id, 
		      bool _map );


  /* This will return what is the current texture-map.
   * Use this with the functions above. 
   * Use the: '!' to get the not-in-use texture-map: */
  bool Get_current_map();

  /* Use this to get the width and height of a texture: */
  bool Get_texture_size( const std::string& _id, 
			 SDL_Point& _size );

  /* Call this function before the application terminates: */
  void Clean();

private:
  /* These are to find texture's position in a texture-map: */
  bool Find_texture( const std::string& _id, 
		     std::map< const std::string, SDL_Texture* >::iterator& _itr );
  bool Find_texture( const std::string& _id, 
		     std::map< const std::string, SDL_Texture* >::iterator& _itr, 
		     bool _map );

  /* This loads image-file into a texture: */
  bool Image_loader( SDL_Renderer* _renderer_ptr, 
		     const std::string& _id, 
		     const std::string& _file_name );

  // --- --- VARIABLES --- ---
  /* which of the two texture-maps is currently in use: */
  bool current;
  /* Array of two maps to hold the textures: */
  std::map< const std::string, SDL_Texture* > m_texture_map_arr[2];
};



#endif
