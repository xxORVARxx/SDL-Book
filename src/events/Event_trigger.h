
#ifndef EVENT_TRIGGER_H
#define EVENT_TRIGGER_H



namespace event
{
  // Event-Trigger Interface:
  class i_Trigger
  {
  public:
    virtual ~i_Trigger()
    {
      for( event::i_Link* link : m_links_vec )
	{
	  delete link;
	}
      m_links_vec.clear();
    }

    // --- Functions ---
    void Add_link( event::i_Link* _link_ptr ) 
    {
      m_links_vec.push_back( _link_ptr );
    }

    virtual event::i_Parameter* Get_variable_1() = 0;
    virtual event::i_Parameter* Get_variable_2() = 0;

  protected:
    // --- Variables ---
    std::vector< event::i_Link* > m_links_vec;
  };
}//event



namespace event
{
  class Trigger : public i_Trigger
  {
  public:
    virtual ~Trigger() {}

    // --- Functions ---
    virtual event::i_Parameter* Get_variable_1()
    {
      assert( false );//ASSERT.
    }
    virtual event::i_Parameter* Get_variable_2()
    {
      assert( false );//ASSERT.
    }

    // When Triggered:
    void operator()()
    {
      for( event::i_Link* link : m_links_vec )
	link->Callback();
    }
  };
}//event



namespace event
{
  template< typename T1 >
  class Trigger_T : public i_Trigger
  {
  public:
    Trigger_T() : m_variable_ptr( false ) {}
    virtual ~Trigger_T() {}

    // --- Functions ---
    virtual event::Parameter_variable< T1 >* Get_variable_1()
    {
      return &m_variable_ptr;
    }
    virtual event::Parameter_variable< T1 >* Get_variable_2()
    {
      assert( false );//ASSERT.
    }

    // When Triggered:
    void operator()( T1 _variable )
    {
      m_variable_ptr.Set( _variable );
      for( event::i_Link* link : m_links_vec )
	link->Callback();
    }

  private:
    // --- Variables ---
    event::Parameter_variable< T1 > m_variable_ptr;
  };
}//event



#endif
