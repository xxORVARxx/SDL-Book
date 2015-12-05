
#ifndef A_STATE_INTERFACE_H
#define A_STATE_INTERFACE_H

#include "Init.h"



// Abstract Base Class. 
class State_interface
{
 public:
  virtual ~State_interface() {};
  virtual void on_Enter() = 0;
  virtual void on_Display_resize() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void on_Exit() = 0;
  virtual std::string Get_state_id() const = 0;
};



#endif
