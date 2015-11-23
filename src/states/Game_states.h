
#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "Init.h"
#include "Objects.h"


/*
void Push_P();
void Push_M();
void Change_M_to_P();
void Change_P_to_M();
void Pop();
*/


// Abstract Base Class. 
class Game_states_blueprint
{
 public:
  virtual ~Game_states_blueprint() {};
  virtual void on_Enter() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void on_Exit() = 0;
  virtual std::string Get_state_id() const = 0;
};



// --- MENU STATE ---
class Menu_state : public Game_states_blueprint
{
 public:
  virtual ~Menu_state() {}
  virtual void on_Enter();
  virtual void Update();
  virtual void Render();
  virtual void on_Exit();
  virtual std::string Get_state_id() const { return sm_menu_id; }

 private:
  static const std::string sm_menu_id;

  std::vector< Object_default* > m_objects_vec;

  // Call back functions for menu items:
  static void smf_Menu_to_play();
  static void smf_Exit_from_menu();

  char m_c;
};



// --- PLAY STATE ---
class Play_state : public Game_states_blueprint
{
 public:
  virtual ~Play_state() {}
  virtual void on_Enter();
  virtual void Update();
  virtual void Render();
  virtual void on_Exit();
  virtual std::string Get_state_id() const { return sm_menu_id; };

 private:
  static const std::string sm_menu_id;

  std::vector< Object_default* > m_objects_vec;

  // Call back functions for menu items:
  static void smf_Play_to_menu();

  char m_c;
};



#endif
