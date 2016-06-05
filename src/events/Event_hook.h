
#ifndef EVENT_HOOK_H
#define EVENT_HOOK_H



namespace event
{
  // Event-Hook Interface:
  class i_Hook
  {
  public:
    i_Hook( const std::vector< event::Type > _type_vec ) 
      : m_type_vec(_type_vec) {}
    virtual ~i_Hook() = 0;

    // --- Functions ---
    const std::vector< event::Type >* Get_type()
    { 
      return &m_type_vec; 
    }

    virtual event::i_Link* Make_link() = 0;
    virtual void Callback( event::i_Parameter* _parameter_ptr ) = 0;

  protected:
    // --- Variables ---
    const std::vector< event::Type > m_type_vec;
  };
  inline i_Hook::~i_Hook() {}
}//event



namespace event
{
  template< class C1, typename T1 >
  class Hook_T : public i_Hook
  {
  public:
    Hook_T( C1* _class, void(C1::* _Callback_fptr)(T1) ) 
      : m_class(_class), m_Callback_fptr(_Callback_fptr), i_Hook( std::vector< event::Type >{ event::Get_type<T1>() } ) 
    {
      assert( m_Callback_fptr != nullptr );//ASSERT. 
    }
    virtual ~Hook_T() {};

    // --- Functions ---
    virtual event::Link_T< Hook_T, T1 >* Make_link()
    {
      return new event::Link_T< Hook_T, T1 >( this );
    }

    virtual void Callback( event::i_Parameter* _parameter_ptr )
    {
      event::Parameter_base< T1 >* p = dynamic_cast< event::Parameter_base< T1 >* >( _parameter_ptr );
      assert( p != nullptr );//ASSERT.
      (m_class->*m_Callback_fptr)( p->Get() );
    }

  private:
    // --- Variables ---
    C1* m_class;
    void(C1::* m_Callback_fptr)(T1);
  };
}//event



#endif
