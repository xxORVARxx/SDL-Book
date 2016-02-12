
#ifndef GAME_OBJ_SHEET_BUTTON_H
#define GAME_OBJ_SHEET_BUTTON_H

#include "Init.h"
#include "Game_obj_sheet.h"
#include "Factory_game_obj.h"



struct Game_obj_button_parameters : public Game_obj_sheet_parameters
{
 Game_obj_button_parameters( Game_obj_sheet_parameters& _sheet_params, void (*_f_Callback)() ) : 
  Game_obj_sheet_parameters(_sheet_params), mf_Callback(_f_Callback) {}

  void (*mf_Callback)();
};



// --- BUTTON ---
class Game_obj_sheet_button : public Game_obj_sheet
{
 public:
  Game_obj_sheet_button() {}
  virtual ~Game_obj_sheet_button() {}

  // --- Functions ---
  void Load( Game_obj_button_parameters& _button_params );
  virtual void Parse( xml::parser& _p );

  virtual void Update();
  virtual void Draw( Camera* _camera );
  virtual void Clean();

 private:
  // --- Variables ---
  enum button_state
  {
    MOUSE_OUT = 1,
    MOUSE_OVER = 2,
    MOUSE_CLICKED = 3,
  };
  bool m_clicked;
  void (*mf_Callback)(); // Function pointer.
};



class Creator_game_obj_button : public Base_creator_game_obj
{
  virtual Base_game_obj* Create_game_object() const
  {
    return new Game_obj_sheet_button;
  }
};



#endif
