
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

    // List of Get Functions:
    int b_Int( std::ifstream& _file ) const;
    long int b_Long_int( std::ifstream& _file ) const;
    unsigned b_Unsigned( std::ifstream& _file ) const;
    long unsigned b_Long_unsigned( std::ifstream& _file ) const;
    float b_Float( std::ifstream& _file ) const;
    double b_Double( std::ifstream& _file ) const;
    long double b_Long_double( std::ifstream& _file ) const;
    bool b_Bool( std::ifstream& _file ) const;
    char b_Char( std::ifstream& _file ) const;
    xx::String_cast b_String( std::ifstream& _file ) const;

    bool c_Container_has( std::ifstream& _file, data::Parser* _p ) const;

    xx::String_cast o_This_object( data::Parser* _p ) const;

    bool i_Has_image_data( std::ifstream& _file, data::Parser* _p ) const;

    xx::String_cast s_This_state( data::Parser* _p ) const;
    bool s_Has_state( std::ifstream& _file, data::Parser* _p ) const;

    int t_Texture_width( std::ifstream& _file, data::Parser* _p ) const;
    int t_Texture_height( std::ifstream& _file, data::Parser* _p ) const;
    int w_Display_width() const;
    int w_Display_height() const;

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

    bool* m_disabled;
  };
}//data



#endif 
