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

  void handle_inputs();
  void update();
  void display();

  bool init();

private:
  bool quit;
  bool first;

  Window* main_window;


  /////
  Pathfinder p;
  Grid g;

  std::pair<int, int> start;
  std::pair<int, int> finish;

  /////
};

#endif // _CORE_HPP_
