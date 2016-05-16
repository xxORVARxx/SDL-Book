
#ifndef PRINTER_H
#define PRINTER_H

#include "Init.h"
#include "Printing_manager.h"
#include "Events.h"

class Image_data;
namespace data{ class Parser; }
class Camera;




// Each 'Object' own a 'Printer'.
class Printer
{
  friend the_Printing_manager;
  struct Action
  {
    Action( std::string _texture_id, const glm::vec2* _size, glm::vec2 _scale, const std::vector< Image_data::Frame >* _frames, 
	    const std::vector< unsigned short >* _sequence, unsigned short _itr = 0 );
    // --- Functions ---
    void Start( unsigned short _itr = 0 );
    void Continue();
    // --- Variables ---
    bool m_end;
    std::string m_texture_id;
    const glm::vec2* m_texture_size_ptr;
    glm::vec2 m_scale;
    unsigned short m_sequence_iterator;
    const std::vector< Image_data::Frame >* m_frames_vec_ptr;
    const std::vector< unsigned short >* m_sequence_vec_ptr;
  };
public:
  Printer();
  // --- Functions ---
  void Print( std::string& _action, glm::vec2 _position );

  void Flip_vertically();
  void Flip_vertically( bool _set_flip );
  void Flip_horizontally();
  void Flip_horizontally( bool _set_flip );



private:
  // --- Variables ---
  glm::vec2 m_position;
  glm::vec2 m_scale;
  float m_timer;
  SDL_RendererFlip m_flip;
  SDL_Rect m_src_rec; // Source Rectangle.
  SDL_Rect m_dest_rec; // Destination Rectangle.
  std::map< const std::string, Printer::Action > m_actions_map;

  Event_hook_TR< Printer, bool, void > flip_vertically_hook;
  Event_hook_TR< Printer, bool, void > flip_horizontally_hook;
  std::map< const std::string, Interface_event_trigger* > m_triggers_map;
  std::map< const std::string, Interface_event_hook* > m_hooks_map;
};



#endif
