
#ifndef PRINTING_MANAGER_H
#define PRINTING_MANAGER_H

#include "Init.h"

class Printer;
class the_Printing_manager;
namespace data{ class Parser; }



// The 'Image-Data' is shared between 'Objects'.
class Image_data
{
  friend the_Printing_manager;
  friend Printer;
  struct Frame
  {
    Frame( SDL_Rect& _xywh, float& _m, SDL_Point& _oxy );
    SDL_Rect m_src_rec;
    float m_ms;
    SDL_Point m_offset;
  };
  Image_data( glm::vec2& _size, std::vector< Image_data::Frame >& _frames, std::map< const std::string, std::vector< unsigned short > >& _sequences );
  const std::vector< unsigned short >* Get_sequence_vec( const std::string& _sequence_id );
  // --- Variables ---
  const glm::vec2 m_image_size;
  const std::vector< Image_data::Frame > m_frames_vec;
  const std::map< const std::string, std::vector< unsigned short > > m_sequence_map;
};



// Singleton Class:
class the_Printing_manager
{
public:
  the_Printing_manager() {}
  ~the_Printing_manager() = default;

  static the_Printing_manager& Instance()
  {
    static the_Printing_manager instance;
    return instance;
  }

private:
  the_Printing_manager( const the_Printing_manager& ) = delete;
  the_Printing_manager& operator=( const the_Printing_manager& ) = delete;

public:
  // --- Functions ---
  bool Load_image_data( std::string& _file_name, std::string& _image_data_id );
  bool Has_image_data( std::string& _image_data_id );
  void Erase_image_data( std::string& _image_data_id );

  Printer* Make_printer( std::ifstream& _file, data::Parser* _p );
  void Make_action( std::ifstream& _file, data::Parser* _p, Printer* _printer_ptr, std::string& _image_data_id, std::string& _sequence_id );

  void Clean();

private:
  Image_data* Parser_image_data( std::ifstream& _file );

  // --- Variables ---
  std::map< std::string, Image_data* > m_image_data_map;
};



#endif
