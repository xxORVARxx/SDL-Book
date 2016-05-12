
#ifndef PRINTER_H
#define PRINTER_H

#include "Init.h"
#include "Printing_manager.h"
#include <unordered_map>
#include <chrono>

namespace data{ class Parser; }
class Printer;



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
  // --- Variables ---
  glm::vec2 m_image_size;
  std::vector< Image_data::Frame > m_frames_vec;
  std::unordered_map< std::string, std::vector< unsigned short > > m_sequence_map;
};



// Each 'Object' own a 'Printer'.
class Printer
{
  friend the_Printing_manager;
  struct Action
  {
    Action( unsigned short _itr = 0 );
    void Start( unsigned short _itr = 0 );
    void Continue();
    // --- Variables ---
    bool m_end;
    std::string m_texture_id;
    glm::vec2 m_scale;
    unsigned short m_sequence_iterator;
    std::vector< Image_data::Frame >* m_frames_vec_ptr;
    std::vector< unsigned short >* m_sequence_vec_ptr;
  };
public:
  Printer();
  // --- Functions ---
  void Print( std::string _action );

  void Flip_vertically();
  void Flip_vertically( bool _set_flip );
  void Flip_horizontally();
  void Flip_horizontally( bool _set_flip );

private:
  // --- Variables ---
  glm::vec2 m_scale;
  SDL_RendererFlip m_flip;
  SDL_Rect m_src_rec; // Source Rectangle.
  SDL_Rect m_dest_rec; // Destination Rectangle.
  std::unordered_map< std::string, Printer::Action > m_actions_map;
};



#endif
