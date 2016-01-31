
#include "XML_parser.h"
#include "Texture_manager.h"

#include "Game.h"
#include "Factory_game_obj.h"



bool State_parser::Parse_state( const std::string _state_file, std::string _state_id, std::vector< Base_game_obj* >& _objects_vec )
{
  std::ifstream ifs( _state_file );
  if( ! ifs.good())
    {
      std::cout << "STATE PARSER :: ERROR: Fail to open file : "<< _state_file <<" !\n";
      return false;
    }
  try
    {
      std::cout <<"STATE PARSER :: Parsing Started...\n";
      std::cout <<"\tState to parse: '"<< _state_id <<"', using file: '"<< _state_file <<"'\n";

      xml::parser p( ifs, _state_id );

      p.next_expect( xml::parser::start_element, _state_id, xml::content::complex );
      for( xml::parser::event_type event( p.next ()) ; (( p.name() != _state_id )&&( event != xml::parser::eof )) ; event = p.next() )
	{
	  p.content( xml::content::complex );
	  if( event == xml::parser::end_element )
	    continue;
	  else if( event == xml::parser::start_element )
	    {
	      if( p.name() == "TEXTURES" )
		{
		  // Textures:
		  if( this->Parse_textures( p, _objects_vec ) == false )
		    return false;
		}
	      else if( p.name() == "OBJECTS" )
		{
		  // Objects:
		  if( this->Parse_objects( p, _objects_vec ) == false )
		    return false;
		}
	      else
		{
		  std::cout <<"STATE PARSER :: ERROR 2: Only expecting: 'TEXTURES' or 'OBJECTS', not: '"
			    << p.name() <<"'. fix the file: "<< _state_file <<", line nr "<< p.column() <<".\n";
		  return false;
		}
	    }
	  else
	    {
	      std::cout <<"STATE PARSER :: ERROR 1: Not expecting: '"
			<< p.name() <<"'. fix the file: "<< _state_file <<", line nr "<< p.column() <<".\n";
	      return false;
	    }
	}//for-end
    }//try-end
  catch( const xml::parsing& error )
    {
      std::cout << "STATE PARSER :: PARSING ERROR: "<< error.what() <<".\n";
      return false;
    }
  std::cout <<"STATE PARSER :: Parsing Ended Successfully.\n";
  return true;
}



bool State_parser::Parse_textures( xml::parser& _p, std::vector< Base_game_obj* >& _objects_vec )
{
  std::cout <<"\tHere we have some Textures:\n";
  do
    {
      _p.next_expect( xml::parser::start_element, "texture" );

      std::cout <<"\t\tImage: '"<< _p.attribute( "filename" ) <<"',  id: '"<< _p.attribute( "id" ) <<"'.\n";
      the_Texture_manager::Instance().Load_image( the_Game::Instance().Get_renderer(), 
						  _p.attribute( "id" ), _p.attribute( "filename" ));

      _p.next_expect( xml::parser::end_element );//texture
    } while( _p.peek () == xml::parser::start_element );

  return true;
}



bool State_parser::Parse_objects( xml::parser& _p, std::vector< Base_game_obj* >& _objects_vec )
{
  std::cout <<"\tHere we have some objects:\n";
  do
    {
      _p.next_expect( xml::parser::start_element, "object", xml::content::complex );


      std::string object_type = _p.attribute( "type" );
      unsigned int quantity =_p.attribute< unsigned int >( "quantity" );


      for( unsigned int i = 0 ; i < quantity ; ++i )
	{
	  Base_game_obj* the_object = the_Factory_game_obj::Instance().Create( object_type );

	  std::cout <<"\t\tObject:  ";
	  the_object->Parse( _p );
	  std::cout <<"\n";

	  _objects_vec.push_back( the_object );
	}


      _p.next_expect( xml::parser::end_element );//object
    } while( _p.peek () == xml::parser::start_element );

  return true;
}
