
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
  template< class C1, typename T1 >
  class Link_T : public i_Link
  {
  public:
    Link_T( C1* _hook_ptr ) 
      : m_hook_ptr(_hook_ptr), m_parameter_ptr(nullptr)
    {
      assert( m_hook_ptr != nullptr );//ASSERT.
    }
    virtual ~Link_T()
    {
      delete m_parameter_ptr;
    }

    // --- Functions ---
    virtual void Parse( event::i_Trigger* _trigger_ptr, std::ifstream& _file, data::Parser* _p )
    {
      m_parameter_ptr = event::Make_parameter< T1 >( _trigger_ptr, _file, _p );
    }

    virtual void Callback()
    {
      m_hook_ptr->Callback( m_parameter_ptr );
    }

    T1 Get_parameter()
    {
      assert( m_parameter_ptr != nullptr );//ASSERT.
      return m_parameter_ptr->Get();
    }

  private:
    // --- Variables ---
    C1* m_hook_ptr;
    event::Parameter_base< T1 >* m_parameter_ptr;
  };
}//event



#endif
