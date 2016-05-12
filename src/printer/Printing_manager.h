
#ifndef PRINTING_MANAGER_H
#define PRINTING_MANAGER_H

#include "Init.h"
#include <unordered_map>

namespace data{ class Parser; }
class Printer;
class Image_data;



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
  void Parser_image_data( std::ifstream& _file, Image_data* _images_data );
  void Parser_image_frames( std::ifstream& _file, Image_data* _images_data );
  void Parser_image_sequence( std::ifstream& _file, Image_data* _images_data, std::string& _str );

  // --- Variables ---
  std::unordered_map< std::string, Image_data* > m_image_data_map;
};



#endif
