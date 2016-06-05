
#include "Printing_manager.h"
#include "Printer.h"
#include "Parser.h"
#include "Events.h"

void Check_for_line_comments( std::ifstream& _file );
void Parser_image_size( std::ifstream& _file, glm::vec2& _image_size );
void Parse_xywh( std::ifstream& _file, SDL_Rect& _xywh, std::string& _order );
void Parse_milliseconds( std::ifstream& _file, float& _ms );
void Parse_offset( std::ifstream& _file, SDL_Point& _oxy, std::string& _order );
void Parse_sequences( std::ifstream& _file, std::string& _sequence_id, std::map< const std::string, std::vector< unsigned short > >& _sequence_map, unsigned int _frames_count );



Image_data::Frame::Frame( SDL_Rect& _xywh, 
			  float& _m, 
			  SDL_Point& _oxy )
  : m_src_rec(_xywh), 
    m_ms(_m), 
    m_offset(_oxy) 
{
}



Image_data::Image_data( glm::vec2& _size, 
			std::vector< Image_data::Frame >& _frames, 
			std::map< const std::string, std::vector< unsigned short > >& _sequences )
  : m_image_size(_size), 
    m_frames_vec(_frames), 
    m_sequence_map(_sequences)
{
}



const std::vector< unsigned short >* 
Image_data::Get_sequence_vec( const std::string& _sequence_id )
{
  auto sequence_itr = m_sequence_map.find( _sequence_id );
  if( sequence_itr == m_sequence_map.end())
    return nullptr;
  return &sequence_itr->second;
}



bool 
the_Printing_manager::Load_image_data( std::string& _file_name, 
				       std::string& _image_data_id )
{
  std::string prefix = "Data/images/";
  std::string suffix = ".data";
  Image_data* image_data_ptr = nullptr;
  try
    {
      std::ifstream data_file( prefix + _file_name + suffix );
      if( data_file.is_open() && data_file.good())
	{
	  image_data_ptr = this->Parser_image_data( data_file );

	  auto pair = m_image_data_map.insert( std::make_pair( _image_data_id, image_data_ptr ));
	  if( ! pair.second )
	    throw std::invalid_argument( "(xx) Printer ERROR! When LOADING 'Image-Data'. The ID: '"+ _image_data_id +"' is allready in use! " );

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



Image_data*
the_Printing_manager::Parser_image_data( std::ifstream& _file )
{
  glm::vec2 image_size;
  std::vector< Image_data::Frame > frames_vec;
  std::map< const std::string, std::vector< unsigned short > > sequence_map;

  // Get the Image Size:
  Parser_image_size( _file, image_size );

  std::string function;
  Check_for_line_comments( _file );
  _file >> function;
  if( function.size() != 4 )
    throw std::invalid_argument( "(xx) Printer ERROR! Expected: Only the characters:  xywh  (but in any order). And not this: '"+ function +"'! " );

  // Get all the Frames:
  while( _file.good())
    {
      SDL_Rect xywh;  xx::Zero_out_SDL_Rect( xywh );
      float ms = 0.0f;
      SDL_Point oxy;  xx::Zero_out_SDL_Point( oxy );

      // Getting the Frame's Source Rectangle:
      Parse_xywh( _file, xywh, function );
      if(( xywh.x + xywh.w ) > image_size.x )
	throw xx::Image_size_mismatch( xx::String_cast( "(xx) Printer ERROR! frame outside the image. " ) + xywh.x +"+"+ xywh.w +">"+ image_size.x +" (frame x + frame w > image w)! " );
      if(( xywh.y + xywh.h ) > image_size.y )
	throw xx::Image_size_mismatch( xx::String_cast( "(xx) Printer ERROR! frame outside the image. " ) + xywh.y +"+"+ xywh.h +">"+ image_size.y +" (frame y + frame h > image h)! " );

      // Getting the Frame's Milliseconds:
      Parse_milliseconds( _file, ms );

      Check_for_line_comments( _file );
      _file >> function;
      if(( function.size() == 0 )||( ! _file.good()))
	throw std::ios::failure( "(xx) Printer ERROR! file corrupted! " );

      // Getting the Frame's Offset:
      if(( function[0] == 'o' )||( function[0] == 'O' ))
	{
	  Parse_offset( _file, oxy, function );
	  Check_for_line_comments( _file );
	  _file >> function;
	}

      // Saving the Frame:
      frames_vec.push_back( Image_data::Frame( xywh, ms, oxy ));

      if( function[0] == '"' )
	break;
      else if( function.size() == 4 )
	continue;
      else
	throw std::invalid_argument( "(xx) Printer ERROR! Expected: The characters:  xywh  (but in any order) or:  oxy  or:  oyx  or a String, starting with a double-quote: \" . Unexpected: '"+ function +"'! " );
    }//while

  // Getting the all the Sequences:
  Parse_sequences( _file, function, sequence_map, frames_vec.size());

  // Make and return the Image Data:
  return new Image_data( image_size, frames_vec, sequence_map );

  /*/  PRINT FRAME'S DATA:
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
	  printer_ptr->m_position.x = _p->Parse_file< float >( _file );
	  printer_ptr->m_position.y = _p->Parse_file< float >( _file );
	  printer_ptr->m_scale.x = _p->Parse_file< float >( _file );
	  printer_ptr->m_scale.y = _p->Parse_file< float >( _file );
	}
      else
	{
	  _p->Parse_file< float >( _file );
	  _p->Parse_file< float >( _file );
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
	  std::string action_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
	  std::string texture_id = std::string( _p->Parse_file< xx::String_cast >( _file ));
	  glm::vec2 scale( _p->Parse_file< float >( _file ),
			   _p->Parse_file< float >( _file ));

	  // Find the 'Image-Data':
	  auto image_data_itr = m_image_data_map.find( _image_data_id );
	  if( image_data_itr == m_image_data_map.end())
	    throw std::invalid_argument("(xx) Printer ERROR! When make an Action. No Image-Data with the ID: '"+ _image_data_id +"'! ");

	  // Get pointer to the Sequence vector:
	  auto sequence_vec_ptr = image_data_itr->second->Get_sequence_vec( _sequence_id );
	  if( sequence_vec_ptr == nullptr )
	    throw std::invalid_argument("(xx) Printer ERROR! When make an Action. The Image-Data with the ID: '"+ _image_data_id +
					"', does not contain any Sequence with the ID: '"+ _sequence_id +"'! ");

	  // Get pointer to the Frames vector:
	  auto frames_vec_ptr = &image_data_itr->second->m_frames_vec;

	  // Create the 'Action' and add it to the Printer:
	  auto action_pair = _printer_ptr->m_actions_map.insert( std::make_pair( action_id, Printer::Action( texture_id,
													     &image_data_itr->second->m_image_size,
													     scale, 
													     frames_vec_ptr, 
													     sequence_vec_ptr )));
	  if( action_pair.second == false )
	    throw std::invalid_argument("(xx) Printer ERROR! When make an Action. The actions ID: '" + action_id + "' is allready in use! ");
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



void 
the_Printing_manager::Harvest_triggers( Printer* _printer_ptr, 
					std::map< const std::string, event::i_Trigger* >& _trigger_gatherer )
{
  for( auto triger_pair : _printer_ptr->m_triggers_map )
    {
      auto pair = _trigger_gatherer.insert( std::make_pair( triger_pair.first, triger_pair.second ));
      assert( pair.second != false );//ASSERT.
    }
}



void 
the_Printing_manager::Harvest_hooks( Printer* _printer_ptr, 
				     std::map< const std::string, event::i_Hook* >& _hook_gatherer )
{
  for( auto hook_pair : _printer_ptr->m_hooks_map )
    {
      auto pair = _hook_gatherer.insert( std::make_pair( hook_pair.first, hook_pair.second ));
      assert( pair.second != false );//ASSERT.
    }
}



void 
the_Printing_manager::Clean()
{
  for( auto& map_pair : m_image_data_map )
    delete map_pair.second;
  m_image_data_map.clear();
  std::cout <<"PRINTING MANAGER :: Clean() is Done.\n";
}
