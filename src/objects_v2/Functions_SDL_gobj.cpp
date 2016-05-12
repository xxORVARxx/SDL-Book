
#include "Init.h"



namespace gobj
{
  std::string Make_file_name( std::string _id, std::string _name = "" )
  {
    if( _name.empty() )
      _name = std::to_string( xx::Get_random.Discrete_num( 0, 9999 ));
    return ( xx::dt.Get_date_string( "_", "_" ) + '-' + 
	     xx::dt.Get_time_string( "_", "_", "_" ) + '-' + 
	     _id + '-' + _name );
  }
}//gobj



namespace gobj
{
  void Calculate_size_and_scale( const glm::vec2& _image_size, glm::vec2& _size, glm::vec2& _scale )
  {
    if( _scale.x )
      xx::Set_value_from_scale< float >( _image_size.x, _size.x, _scale.x );
    else
      xx::Set_scale_from_value< float >( _image_size.x, _size.x, _scale.x );

    if( _scale.y )
      xx::Set_value_from_scale< float >( _image_size.y, _size.y, _scale.y );
    else
      xx::Set_scale_from_value< float >( _image_size.y, _size.y, _scale.y );
  }
}//gobj

