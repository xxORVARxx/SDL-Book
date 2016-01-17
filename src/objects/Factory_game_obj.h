
#ifndef Factory_game_obj_h
#define Factory_game_obj_h

#include "Init.h"
#include "A_Game_obj_interface.h"



class Base_creator
{
 public:
  virtual Game_obj_default* Create_game_object() const = 0;
  virtual ~Base_creator() {}
};



class Factory_game_obj
{
 public:
  bool Register_type( std::string type_id, Base_creator* ptr_creater );
  Game_obj_default* Create( std::string type_id );

 private:
  std::map< std::string, Base_creator* > m_creators;
};



#endif
