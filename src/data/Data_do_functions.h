
#ifndef DATA_DO_FUNCTIONS_H
#define DATA_DO_FUNCTIONS_H

namespace data{ class Parser; }



namespace data
{
  class Do_functions
  {
  public:
   
    // List of Do Functions:
    void l_If( bool _disabled, std::ifstream& _file, Parser* _p ) const;
    void l_If_not( bool _disabled, std::ifstream& _file, Parser* _p ) const;
    void l_If_all( bool _disabled, std::ifstream& _file, Parser* _p ) const;
    void l_If_none( bool _disabled, std::ifstream& _file, Parser* _p ) const;
    void l_If_any( bool _disabled, std::ifstream& _file, Parser* _p ) const;
    void l_If_any_not( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    void c_Container_erase( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    void o_Make_SDL_gobj( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    void t_Swap_texture_maps( bool _disabled ) const;
    void t_Move_or_load_texture( bool _disabled, std::ifstream& _file, Parser* _p ) const;
    void t_Clear_texture_map( bool _disabled ) const;
    void t_Clear_current_texture_map( bool _disabled ) const;

    void s_Make_camera( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    // List of Template Do Functions:
    template< typename T > 
    void c_Container_add( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    template< typename T > 
    void c_Container_set( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    template< typename T > 
    void p_Print( bool _disabled, std::ifstream& _file, Parser* _p ) const;

  };
}//data



#endif
