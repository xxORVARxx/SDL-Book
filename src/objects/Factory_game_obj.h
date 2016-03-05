
#ifndef Factory_game_obj_h
#define Factory_game_obj_h

#include "Init.h"

class Base_game_obj;



// All Game-Object that the 'Factory' can create:
namespace fac
{
  enum game_object
  {
    GAME_OBJ,
    GAME_OBJ_GRID,
    GAME_OBJ_SHEET,
    GAME_OBJ_SHEET_BUTTON,
    GAME_OBJ_SHEET_ENEMY,
    GAME_OBJ_SHEET_PLAYER
  };
}//fac



class Base_creator_game_obj
{
 public:
  virtual ~Base_creator_game_obj() = default;
  virtual Base_game_obj* Create_game_object() const = 0;
};



class the_Factory_game_obj
{
 private:
  the_Factory_game_obj() = default;
  the_Factory_game_obj( const the_Factory_game_obj& ) = delete;
  the_Factory_game_obj& operator= ( const the_Factory_game_obj& ) = delete;

 public:
  ~the_Factory_game_obj() = default;

  static the_Factory_game_obj& Instance()
  {
    static the_Factory_game_obj instance;
    return instance;
  }

  bool Register_creator( fac::game_object _object_id, Base_creator_game_obj* _creater_ptr );
  Base_game_obj* Create( fac::game_object _object_id );

  void Clean();

 private:
  std::map< const fac::game_object, Base_creator_game_obj* > m_creators_map;
};



#endif
