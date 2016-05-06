
#ifndef DATA_GET_FUNCTIONS_H
#define DATA_GET_FUNCTIONS_H

namespace data{ class Parser; }
class State;



namespace data
{
  class Get_functions
  {
  public:

    // List of Get Functions:
    int b_Int( bool _disabled, std::ifstream& _file ) const;
    long int b_Long_int( bool _disabled, std::ifstream& _file ) const;
    unsigned b_Unsigned( bool _disabled, std::ifstream& _file ) const;
    long unsigned b_Long_unsigned( bool _disabled, std::ifstream& _file ) const;
    float b_Float( bool _disabled, std::ifstream& _file ) const;
    double b_Double( bool _disabled, std::ifstream& _file ) const;
    long double b_Long_double( bool _disabled, std::ifstream& _file ) const;
    bool b_Bool( bool _disabled, std::ifstream& _file ) const;
    char b_Char( bool _disabled, std::ifstream& _file ) const;
    xx::String_cast b_String( bool _disabled, std::ifstream& _file ) const;

    bool c_Container_has( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    xx::String_cast s_This_state( bool _disabled, Parser* _p ) const;
    bool s_Has_state( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    int t_Texture_width( bool _disabled, std::ifstream& _file, Parser* _p ) const;
    int t_Texture_height( bool _disabled, std::ifstream& _file, Parser* _p ) const;
    int w_Display_width( bool _disabled ) const;
    int w_Display_height( bool _disabled ) const;

    // List of Template Get Functions:
    template< typename T > 
    T m_Add( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    template< typename T >
    T m_Subtract( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    template< typename T >
    T m_Multiply( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    template< typename T >
    T m_Divide( bool _disabled, std::ifstream& _file, Parser* _p ) const;


    template< typename T >
    T f_Random_discrete_num( bool _disabled, std::ifstream& _file ) const;

    template< typename T >
    T f_Random_real_num( bool _disabled, std::ifstream& _file ) const;


    template< typename T >
    T c_Container_get( bool _disabled, std::ifstream& _file, Parser* _p ) const;

    template< typename T >
    T c_Container_take( bool _disabled, std::ifstream& _file, Parser* _p ) const;

  };
}//data



#endif 
