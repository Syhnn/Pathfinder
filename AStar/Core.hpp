#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <memory>

#include "Pathfinder.hpp"


const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


class Window;


class Core {
public:
  Core();
  ~Core();

  void mainloop();

  void handleInputs();
  void update();
  void display();

  bool init();

private:
  void restart();

  bool quit;
  bool clear_grid;
  bool redraw_walls;
  bool path_found;
  bool playing;
  bool click;
  bool wall_state;

  int step_count;
  int mousex;
  int mousey;

  Window* main_window;

  Pathfinder p;
  Grid g;

  std::pair<int, int> start;
  std::pair<int, int> finish;
  std::pair<int, int> pos;
};

#endif // _CORE_HPP_
