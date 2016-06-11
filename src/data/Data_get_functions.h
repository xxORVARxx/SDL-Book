
#ifndef DATA_GET_FUNCTIONS_H
#define DATA_GET_FUNCTIONS_H

namespace data{ class Parser; }
class State;



namespace data
{
  class Get_functions
  {
  public:
    Get_functions( bool* _disabled ) : m_disabled(_disabled) {}

    // --- Functions ---
    // List of Get Functions:
    byte_t b_Byte( std::ifstream& _file ) const;
    integer_t b_Integer( std::ifstream& _file ) const;
    real_t b_Real( std::ifstream& _file ) const;
    string_t b_String( std::ifstream& _file ) const;

    byte_t c_Container_has( std::ifstream& _file, data::Parser* _p ) const;

    string_t s_This_state( data::Parser* _p ) const;
    byte_t s_Has_state( std::ifstream& _file, data::Parser* _p ) const;

    string_t o_This_object( data::Parser* _p ) const;

    integer_t t_Texture_width( std::ifstream& _file, data::Parser* _p ) const;
    integer_t t_Texture_height( std::ifstream& _file, data::Parser* _p ) const;

    byte_t i_Has_image_data( std::ifstream& _file, data::Parser* _p ) const;

    integer_t w_Display_width() const;
    integer_t w_Display_height() const;

    // List of Template Get Functions:
    template< typename T > 
    T m_Add( std::ifstream& _file, data::Parser* _p ) const;

    template< typename T >
    T m_Subtract( std::ifstream& _file, data::Parser* _p ) const;

    template< typename T >
    T m_Multiply( std::ifstream& _file, data::Parser* _p ) const;

    template< typename T >
    T m_Divide( std::ifstream& _file, data::Parser* _p ) const;


    template< typename T >
    T f_Random_discrete_num( std::ifstream& _file ) const;

    template< typename T >
    T f_Random_real_num( std::ifstream& _file ) const;


    template< typename T >
    T c_Container_get( std::ifstream& _file, data::Parser* _p ) const;

    template< typename T >
    T c_Container_take( std::ifstream& _file, data::Parser* _p ) const;

    // --- Variables ---
    bool* m_disabled;
  };
}//data



#endif 
