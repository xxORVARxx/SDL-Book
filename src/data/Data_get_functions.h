
#ifndef DATA_GET_FUNCTIONS_H
#define DATA_GET_FUNCTIONS_H

namespace data{ class Parser; }



namespace data
{
  class Get_functions
  {
  public:

    // List of Get Functions:
    int b_Int( std::ifstream& _file );
    long int b_Long_int( std::ifstream& _file );
    unsigned b_Unsigned( std::ifstream& _file );
    long unsigned b_Long_unsigned( std::ifstream& _file );
    float b_Float( std::ifstream& _file );
    double b_Double( std::ifstream& _file );
    long double b_Long_double( std::ifstream& _file );
    bool b_Bool( std::ifstream& _file );
    char b_Char( std::ifstream& _file );
    xx::String_cast b_String( std::ifstream& _file );

    int t_Texture_width( std::ifstream& _file );
    int t_Texture_height( std::ifstream& _file );
    int w_Display_width();
    int w_Display_height();

    // List of Template Get Functions:
    template< typename T > 
    T m_Add( std::ifstream& _file, Parser* _p );

    template< typename T >
    T m_Subtract ( std::ifstream& _file, Parser* _p );

    template< typename T >
    T m_Multiply  ( std::ifstream& _file, Parser* _p );

    template< typename T >
    T m_Divide ( std::ifstream& _file, Parser* _p );

    template< typename T >
    T f_Random_discrete_num( std::ifstream& _file );

    template< typename T >
    T f_Random_real_num( std::ifstream& _file );

  };
}//data



#endif 
