
#ifndef XX_EXCEPTION_H
#define XX_EXCEPTION_H

#include <iostream>
#include <string>
#include <exception>

/*  std::exception
 *
 *  01. xx::Exception
 *     01. xx::Printer_error
 *        01. xx::Image_size_mismatch
 *        02. xx::Image_data_not_found
 *     02. xx::Texture_error
 *     03. xx::Parsing_error
 *     04. xx::Missing_argument
 */



namespace xx
{
  class Exception : public std::exception
  {
  public:
    explicit Exception( const char* _message ) : 
      m_error_msg(_message) {}

    explicit Exception( const std::string& _message ) : 
      m_error_msg(_message) {}

    virtual ~Exception() {}

    virtual const char* what() const throw()
    {
      return m_error_msg.c_str();
    }
  protected:
    std::string m_error_msg;
  };
}//xx



namespace xx
{
  class Printer_error : public xx::Exception
  {
  public:
    explicit Printer_error( const char* _message ) : 
      xx::Exception( _message ) {}
    explicit Printer_error( const std::string& _message ) : 
      xx::Exception( _message ) {}
    virtual ~Printer_error() {}
  };



  class Image_size_mismatch : public xx::Printer_error
  {
  public:
    explicit Image_size_mismatch( const char* _message ) : 
      xx::Printer_error( _message ) {}
    explicit Image_size_mismatch( const std::string& _message ) : 
      xx::Printer_error( _message ) {}
    virtual ~Image_size_mismatch() {}
  };



  class Image_data_not_found : public xx::Printer_error
  {
  public:
    explicit Image_data_not_found( const char* _message ) : 
      xx::Printer_error( _message ) {}
    explicit Image_data_not_found( const std::string& _message ) : 
      xx::Printer_error( _message ) {}
    virtual ~Image_data_not_found() {}
  };
}//xx



namespace xx
{
  class Texture_error : public xx::Exception
  {
  public:
    explicit Texture_error( const char* _message ) : 
      xx::Exception( _message ) {}
    explicit Texture_error( const std::string& _message ) : 
      xx::Exception( _message ) {}
    virtual ~Texture_error() {}
  };
}//xx



namespace xx
{
  class Parsing_error : public xx::Exception
  {
  public:
    explicit Parsing_error( const char* _message ) : 
      xx::Exception( _message ) {}
    explicit Parsing_error( const std::string& _message ) : 
      xx::Exception( _message ) {}
    virtual ~Parsing_error() {}
  };
}//xx



namespace xx
{
  class Missing_argument : public xx::Exception
  {
  public:
    explicit Missing_argument( const char* _message ) : 
      xx::Exception( _message ) {}
    explicit Missing_argument( const std::string& _message ) : 
      xx::Exception( _message ) {}
    virtual ~Missing_argument() {}
  };
}//xx



#endif
