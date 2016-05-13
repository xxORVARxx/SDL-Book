
#ifndef DATA_DO_FUNCTIONS_H
#define DATA_DO_FUNCTIONS_H

namespace data{ class Parser; }



namespace data
{
  class Do_functions
  {
  public:
    Do_functions( bool* _disabled ) : m_disabled(_disabled) {}

    // --- Functions ---
    // List of Do Functions:
    void l_If( std::ifstream& _file, data::Parser* _p ) const;
    void l_If_not( std::ifstream& _file, data::Parser* _p ) const;
    void l_If_all( std::ifstream& _file, data::Parser* _p ) const;
    void l_If_none( std::ifstream& _file, data::Parser* _p ) const;
    void l_If_any( std::ifstream& _file, data::Parser* _p ) const;
    void l_If_any_not( std::ifstream& _file, data::Parser* _p ) const;

    void c_Container_erase( std::ifstream& _file, data::Parser* _p ) const;

    void s_Make_camera( std::ifstream& _file, data::Parser* _p ) const;

    void o_Make_SDL_gobj( std::ifstream& _file, data::Parser* _p ) const;

    void t_Swap_texture_maps() const;
    void t_Move_or_load_texture( std::ifstream& _file, data::Parser* _p ) const;
    void t_Clear_texture_map() const;
    void t_Clear_current_texture_map() const;

    void i_Load_image_data( std::ifstream& _file, data::Parser* _p ) const;
    void i_Erase_image_data( std::ifstream& _file, data::Parser* _p ) const;
    void i_Make_simple_printer( std::ifstream& _file, data::Parser* _p ) const;
    void i_Make_sheet_printer( std::ifstream& _file, data::Parser* _p ) const;
    void i_Make_frame_printer( std::ifstream& _file, data::Parser* _p ) const;
    void i_Make_action( std::ifstream& _file, data::Parser* _p ) const;

    // List of Template Do Functions:
    template< typename T > 
    void c_Container_add( std::ifstream& _file, data::Parser* _p ) const;

    template< typename T > 
    void c_Container_set( std::ifstream& _file, data::Parser* _p ) const;

    template< typename T > 
    void p_Print( std::ifstream& _file, data::Parser* _p ) const;

    // --- Variables ---
    bool* m_disabled;
  };
}//data



#endif
