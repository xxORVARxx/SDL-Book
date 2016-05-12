
#include "Printing_manager.h"
#include "Printer.h"
#include "Parser.h"

void Check_for_line_comments( std::ifstream& _file );
void Parse_xywh( std::ifstream& _file, SDL_Rect& _xywh, std::string& _order );
void Parse_milliseconds( std::ifstream& _file, float& _ms );
void Parse_offset( std::ifstream& _file, SDL_Point& _oxy, std::string& _order );



bool 
the_Printing_manager::Load_image_data( std::string& _file_name, 
				       std::string& _image_data_id )
{
  std::string prefix = "Data/images/";
  std::string suffix = ".data";

  if( this->Has_image_data( _image_data_id ))
    throw std::invalid_argument( "(xx) Printer ERROR! When LOADING 'Image-Data'. The ID: '"+ _image_data_id +"' is allready in use! " );
  Image_data* image_data_ptr = new Image_data;
  try
    {
      std::ifstream data_file( prefix + _file_name + suffix );
      if( data_file.is_open() && data_file.good())
	{
	  this->Parser_image_data( data_file, image_data_ptr );

	  m_image_data_map[ _image_data_id ] = image_data_ptr;

	  data_file.close();
	}
      else 
	throw std::ios::failure( "(xx) Printer ERROR! When opening 'Image-Data' file: '"+ prefix + _file_name + suffix +"'! " );
    }
  catch( const std::exception& e )
    {
      delete image_data_ptr;
      std::cerr <<"PRINTER ERROR :: When parsing the 'Image-Data' file: '"<< prefix << _file_name << suffix <<"'!\n";
      std::cerr <<"\t"<< e.what() <<'\n';
      return false;
    }
  return true;
}



bool 
the_Printing_manager::Has_image_data( std::string& _image_data_id )
{
  auto itr = m_image_data_map.find( _image_data_id );
  if( itr == m_image_data_map.end())
    return false;
  return true;
}



void 
the_Printing_manager::Erase_image_data( std::string& _image_data_id )
{
  auto itr = m_image_data_map.find( _image_data_id );
  if( itr == m_image_data_map.end())
    throw xx::Image_data_not_found( "(xx) Printer ERROR! When ERASING 'Image-Data'. No image-data with the ID: '"+ _image_data_id +"'! " );
  delete (*itr).second;
  m_image_data_map.erase( itr );
}



void 
the_Printing_manager::Clean()
{
  for( auto& map_pair : m_image_data_map )
    delete map_pair.second;
  m_image_data_map.clear();
  std::cout <<"PRINTING MANAGER :: Clean() is Done.\n";
}



void 
the_Printing_manager::Parser_image_data( std::ifstream& _file, 
					 Image_data* _images_data )
{
  bool w_ok = false;
  bool h_ok = false;
  int size = 0;
  char c = '?';
  for( int i = 0 ; i < 2 ; ++i )
    {
      Check_for_line_comments( _file );
      _file >> c;
      switch( c )
	{
	case 'w':
	case 'W':
	  Check_for_line_comments( _file );
	  _file >> size;
	  _images_data->m_image_size.x = size;
	  w_ok = true;
	  break;
	case 'h':
	case 'H':
	  Check_for_line_comments( _file );
	  _file >> size;
	  _images_data->m_image_size.y = size;
	  h_ok = true;
	  break;
	default:
	  throw xx::Missing_argument( "(xx) Printer ERROR! Expected the 'Image-Data' file to begin with:  w  or  h ! " );
	}//switch
      if( ! _file.good())
	throw std::ios::failure( "(xx) Printer ERROR! file corrupted. When reading WIDTH and HEIGHT! " );
    }//for
  if(( ! w_ok )||( _images_data->m_image_size.x <= 0 ))
    throw xx::Missing_argument( "(xx) Printer ERROR! Expected:  w  and then the image's WIDTH in pixels. The width cannot zero! " );
  if(( ! h_ok )||( _images_data->m_image_size.y <= 0 ))
    throw xx::Missing_argument( "(xx) Printer ERROR! Expected:  h  and then the image's HEIGHT in pixels. The height cannot zero! " );

  this->Parser_image_frames( _file, _images_data );
}



void 
the_Printing_manager::Parser_image_frames( std::ifstream& _file, 
					   Image_data* _images_data )
{
  std::string function;
  Check_for_line_comments( _file );
  _file >> function;
  if( function.size() != 4 )
    throw std::invalid_argument( "(xx) Printer ERROR! Expected: Only the characters:  xywh  (but in any order). And not this: '"+ function +"'! " );

  while( _file.good())
    {
      SDL_Rect xywh;  xx::Zero_out_SDL_Rect( xywh );
      float ms = 0.0f;
      SDL_Point oxy;  xx::Zero_out_SDL_Point( oxy );

      // Getting the Source Rectangle:
      Parse_xywh( _file, xywh, function );
      if(( xywh.x + xywh.w ) > _images_data->m_image_size.x )
	throw xx::Image_size_mismatch( "(xx) Printer ERROR! frame outside the image. (frame x + frame w > image w)! " );
      if(( xywh.y + xywh.h ) > _images_data->m_image_size.y )
	throw xx::Image_size_mismatch( "(xx) Printer ERROR! frame outside the image. (frame y + frame h > image h)! " );

      // Getting the Milliseconds:
      Parse_milliseconds( _file, ms );

      Check_for_line_comments( _file );
      _file >> function;
      if(( function.size() == 0 )||( ! _file.good()))
	throw std::ios::failure( "(xx) Printer ERROR! file corrupted! " );

      // Getting the Offset:
      if(( function[0] == 'o' )||( function[0] == 'O' ))
	{
	  Parse_offset( _file, oxy, function );
	  Check_for_line_comments( _file );
	  _file >> function;
	}

      // Saving the Frame:
      _images_data->m_frames_vec.push_back( Image_data::Frame( xywh, ms, oxy ));

      if( function[0] == '"' )
	break;
      else if( function.size() == 4 )
	continue;
      else
	throw std::invalid_argument( "(xx) Printer ERROR! Expected: The characters:  xywh  (but in any order) or:  oxy  or:  oyx  or a String, starting with a double-quote: \" . Unexpected: '"+ function +"'! " );
    }//while

  this->Parser_image_sequence( _file, _images_data, function );
}



void
the_Printing_manager::Parser_image_sequence( std::ifstream& _file, 
					    Image_data* _images_data, 
					    std::string& _sequence_id )
{
  std::vector< unsigned short > sequence_vec;
  _sequence_id = xx::Read_string_from_file( _file, _sequence_id );
  while( _file.good())
    {
      do
	{ 
	  int index = -1;
	  Check_for_line_comments( _file );
	  _file >> index;
	  --index;

	  if( _file.fail())// not a number.
	    throw std::invalid_argument( xx::String_cast( "(xx) Printer ERROR! Expected: Indices from  1  to  " ) + 
					 _images_data->m_frames_vec.size() +" . Or a String starting with a double-quote: \" ! " );
	  if(( index < 0 )||( index >= _images_data->m_frames_vec.size()))
	    throw std::invalid_argument( xx::String_cast( "(xx) Printer ERROR! Expected: Indices from  1  to  " ) + 
					 _images_data->m_frames_vec.size() +" . Unexpected index of: "+ (index+1) +"! " );

	  sequence_vec.push_back( index );

	  Check_for_line_comments( _file );
	  _file >> std::ws;
	}
      while(( _file.peek() != '"' )&& _file.good());

      auto pair = _images_data->m_sequence_map.insert( std::make_pair( _sequence_id, sequence_vec ));
      sequence_vec.clear();

      if( ! pair.second )
	throw std::invalid_argument( "(xx) Printer ERROR! When Creating a SEQUENCE. The sequence-name-id: '" + _sequence_id + "' is allready in use! " );
      if( _file.good())
	_sequence_id = xx::Read_string_from_file( _file );
    }//while

  /*/  PRINT FARIM DATA:
  std::cout <<"\n---------->"<< _images_data->m_image_size.x <<"\t"<< _images_data->m_image_size.y <<"\n";
  for( auto& frame : _images_data->m_frames_vec )
    {
      std::cout <<"\tx:"<< frame.m_src_rec.x <<"\ty:"<< frame.m_src_rec.y <<"\tw:"<< frame.m_src_rec.w <<"\th:"<< frame.m_src_rec.h <<"\t\tms:"<< frame.m_ms;
      if( frame.m_offset.x || frame.m_offset.y )
	std::cout <<"\t\tox:"<< frame.m_offset.x <<"\toy:"<< frame.m_offset.y;
      std::cout <<"\n";
    }
  std::cout <<"\n";
  for( auto& sequence : _images_data->m_sequence_map )
    {
      std::cout <<"\t"<< sequence.first <<"\n\t";
      for( auto& index : sequence.second )
	std::cout <<"\t"<< index;
      std::cout <<"\n";
    }
  */
}



Printer*
the_Printing_manager::Make_printer( std::ifstream& _file, 
				    data::Parser* _p )
{
  Printer* printer_ptr;
  if( ! _p->Disabled())
    printer_ptr = new Printer;
  try
    {
      if( ! _p->Disabled())
	{
	  printer_ptr->m_scale.x = _p->Parse_file< float >( _file );
	  printer_ptr->m_scale.y = _p->Parse_file< float >( _file );
	}
      else
	{
	  _p->Parse_file< float >( _file );
	  _p->Parse_file< float >( _file );
	  return nullptr;
	}
    }
  catch( const std::exception& e )
    {
      delete printer_ptr;
      throw xx::Printer_error( std::string( "(xx) Printer ERROR! When creating Printer!\n\t" ) + e.what());
    }
  return printer_ptr;
}



void 
the_Printing_manager::Make_action( std::ifstream& _file,
				   data::Parser* _p,
				   Printer* _printer_ptr, 
				   std::string& _image_data_id, 
				   std::string& _sequence_id )
{
  try
    {
      if( ! _p->Disabled())
	{
	  std::string actions_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
	  std::string texture_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
	  glm::vec2 scale( _p->Parse_file< float >( _file ),
			   _p->Parse_file< float >( _file ));

	  // Find the 'Image-Data':
	  auto image_data_itr = m_image_data_map.find( _image_data_id );
	  if( image_data_itr == m_image_data_map.end())
	    throw std::invalid_argument("(xx) Printer ERROR! When make an Action. No Image-Data with the ID: '"+ _image_data_id +"'! ");

	  // Find the 'Sequence' in the Image-Data:
	  auto sequence_itr = image_data_itr->second->m_sequence_map.find( _sequence_id );
	  if( sequence_itr == image_data_itr->second->m_sequence_map.end())
	    throw std::invalid_argument("(xx) Printer ERROR! When make an Action. The Image-Data with the ID: '"+ _image_data_id +
					"', does not contain any Sequence with the ID: '"+ _sequence_id +"'! ");

	  // Create the 'Action' and add it to the Printer:
	  auto action_itr = _printer_ptr->m_actions_map.insert( std::make_pair( actions_id, Printer::Action()));
	  if( ! action_itr.second )
	    throw std::invalid_argument("(xx) Printer ERROR! When make an Action. The actions ID: '" + actions_id + "' is allready in use! ");

	  // Set the Action's 'Values':
	  Printer::Action* action_ptr = &(*action_itr.first).second;
	  action_ptr->m_texture_id = texture_id;
	  action_ptr->m_scale = scale;
	  action_ptr->m_frames_vec_ptr = &image_data_itr->second->m_frames_vec;
	  action_ptr->m_sequence_vec_ptr = &sequence_itr->second;
	}
      else
	{
	  _p->Parse_file< xx::String_cast >( _file );
	  _p->Parse_file< float >( _file );
	  _p->Parse_file< float >( _file );
	  return;
	}
    }
  catch( const std::exception& e )
    {
      throw xx::Printer_error( std::string( "(xx) Printer ERROR! When make an Action!\n\t" ) + e.what());
    }
}
