
#ifndef GAME_OBJ_SHEET_BUTTON_H
#define GAME_OBJ_SHEET_BUTTON_H

#include "Init.h"
#include "Game_obj_sheet.h"



// --- BUTTON ---
class Game_obj_sheet_button : public Game_obj_sheet
{
 public:
  Game_obj_sheet_button( Game_obj_parameters& _obj_params, Game_obj_sheet_parameters& _sheet_params, void (*f_Callback)());
  virtual ~Game_obj_sheet_button() {}

  virtual void Update();
  virtual void Draw();
  virtual void Clean() { std::cout << "BUTTON :: Clean() is Done,  &  "; Game_obj_sheet::Clean(); }

 private:
  enum button_state
  {
    MOUSE_OUT = 1,
    MOUSE_OVER = 2,
    MOUSE_CLICKED = 3,
  };

  bool m_clicked;
  void (*mf_Callback)(); // Function pointer.
};



#endif
