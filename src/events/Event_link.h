
#ifndef EVENT_LINK_H
#define EVENT_LINK_H



namespace event
{
  // Event-Link Interface:
  class i_Link
  {
  public:
    virtual ~i_Link() = 0;
    virtual void Parse( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p ) = 0;
    virtual void Callback() = 0;
  };
  inline i_Link::~i_Link() {}
}//event



namespace event
{
  template< class C1 >
  class Link : public i_Link
  {
  public:
    Link( C1* _hook_ptr ) 
      : m_hook_ptr(_hook_ptr)
    {
      assert( m_hook_ptr != nullptr );//ASSERT.
    }
    virtual ~Link() {}

    // --- Functions ---
    virtual void Parse( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p ) {}

    virtual void Callback()
    {
      m_hook_ptr->Callback();
    }

  private:
    // --- Variables ---
    C1* m_hook_ptr;
  };
}//event



namespace event
{
  template< class C1, typename T1 >
  class Link_T : public i_Link
  {
  public:
    Link_T( C1* _hook_ptr ) 
      : m_hook_ptr(_hook_ptr)
    {
      assert( m_hook_ptr != nullptr );//ASSERT.
    }
    virtual ~Link_T() {}

    // --- Functions ---
    virtual void Parse( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p )
    {
      auto local_function = _p->Parse_file< event::Return_function_t< T1 > >( _file, event::Get_function );
      m_parameter = local_function( _trigger_ptr, _file, _p );
    }

    virtual void Callback()
    {
      assert( m_parameter.Good());//ASSERT.
      m_hook_ptr->Callback( m_parameter.m_parameter_ptr );
    }

  private:
    // --- Variables ---
    C1* m_hook_ptr;
    event::Parameater< T1 > m_parameter;
  };
}//event



#endif
