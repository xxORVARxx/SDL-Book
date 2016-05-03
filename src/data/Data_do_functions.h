
#ifndef DATA_DO_FUNCTIONS_H
#define DATA_DO_FUNCTIONS_H

namespace data{ class Parser; }



namespace data
{
  class Do_functions
  {
  public:
   
    // List of Do Functions:
    void c_Container_erase( std::ifstream& _file, Parser* _p );

    void o_Make_SDL_gobj( std::ifstream& _file );

    void t_Swap_texture_maps();
    void t_Move_or_load_texture( std::ifstream& _file, Parser* _p );
    void t_Clear_texture_map();
    void t_Clear_current_texture_map();

    void s_Make_camera();

    // List of Template Do Functions:
    template< typename T > 
    void c_Container_add( std::ifstream& _file, Parser* _p );

  };
}//data



#endif
