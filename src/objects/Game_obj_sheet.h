
#ifndef GAME_OBJ_SHEET_H
#define GAME_OBJ_SHEET_H

#include "Init.h"
#include "Game_obj.h"
#include "Factory_game_obj.h"



// This holds the 'Parameters' to pass through the 'Object' classes.
struct Game_obj_sheet_parameters : public Game_obj_parameters
{
 Game_obj_sheet_parameters( Game_obj_parameters& _obj_params, int frames, int row, float time = 66.67 ) : 
  Game_obj_parameters(_obj_params), total_num_of_frames(frames), frames_in_a_row(row), frame_time(time) {}

  int total_num_of_frames;
  int frames_in_a_row;
  float frame_time;// <- Default = '66.67' (or '15' fps)
};



// This is the default sprite-sheet 'Game-object' class which other sprite-sheet 'Object' classes can 'inharents' from. 
class Game_obj_sheet : public Game_obj
{
 public:
  Game_obj_sheet() {}
  virtual ~Game_obj_sheet() {}

  // --- Functions ---
  void Load( Game_obj_sheet_parameters& _sheet_params );
  virtual void Parse( xml::parser& _p );

  virtual void Update();
  virtual void Draw( Camera* _camera );
  virtual void Clean();

  // --- Variables ---
 protected:
  int m_total_num_of_frames;// The total number of frames on the spirit-sheet.
  int m_frames_in_a_row;// The number of frames in a row on the spirit-sheet.
  float m_frame_time;// Time between changing to the next frame (ms).

  int m_frame_width;
  int m_frame_height;
  int m_frame_counter;// The current frame being rendered.
  float m_frame_time_out;// Time-stamp since the current frame started.
  int m_frame_number;
  int m_row_number;
};



class Creator_game_obj_sheet : public Base_creator_game_obj
{
  virtual Base_game_obj* Create_game_object() const
  {
    return new Game_obj_sheet;
  }
};



#endif
