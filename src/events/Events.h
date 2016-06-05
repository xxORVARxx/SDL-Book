
#ifndef EVENTS_H
#define EVENTS_H

#include "Init.h"
#include "Event_functions.h"

namespace event{ class i_Hook; }
namespace event{ class i_Link; }
namespace event{ class i_Trigger; }
namespace data{ class Parser; }



namespace event
{
  class Events_manager
  {
  public:
    Events_manager();

    // --- Functions ---
    void Parse( std::ifstream& _file, data::Parser* _p );

  private:
    void Parse_get_hook( std::ifstream& _file, data::Parser* _p );
    void Parse_get_trigger( std::ifstream& _file, data::Parser* _p );

    // --- Variables ---
    event::i_Hook* m_hook_ptr;
    event::i_Trigger* m_trigger_ptr;
  };
}//event



#endif
