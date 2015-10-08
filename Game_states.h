
#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "Init.h"



// Abstract Base Class. 
class Game_states_blueprint
{
 public:
  virtual bool on_Enter() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual bool on_Exit() = 0;
  virtual std::string Get_state_id() const = 0;
};



// --- MENU STATE ---
class Menu_state : public Game_states_blueprint
{
 public:
  virtual bool on_Enter();
  virtual void Update();
  virtual void Render();
  virtual bool on_Exit();
  virtual std::string Get_state_id() const { return sm_menu_id; };

 private:
  static const std::string sm_menu_id;
};



// --- PLAY STATE ---
class Play_state : public Game_states_blueprint
{
 public:
  virtual bool on_Enter();
  virtual void Update();
  virtual void Render();
  virtual bool on_Exit();
  virtual std::string Get_state_id() const { return sm_menu_id; };

 private:
  static const std::string sm_menu_id;
};



#endif
