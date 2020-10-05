#include "Core.hpp"


#include <iostream>
#include "SDL.h"

#include "Window.hpp"


using namespace std;


Core::Core() :
  quit(false),
  clear_grid(true),
  redraw_walls(true),
  path_found(false),
  playing(false),
  step_count(0),
  main_window(new Window()),
  g(GRID_WIDTH, GRID_HEIGHT),
  start(10, 10), 
  finish(35, 20),
  p(&g, make_pair(10, 10), make_pair(35, 20))
{
  for (int i(0); i < 25; ++i)
    g.setWall(make_pair(15, i), true);
  for (int i(0); i < 25; ++i)
    g.setWall(make_pair(25, GRID_HEIGHT-1-i), true);
}

Core::~Core() {
  delete main_window;
}


void Core::handleInputs() {
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      // on left click, toggle walls
      if (e.button.button == SDL_BUTTON_LEFT) {
        int x(0), y(0);
        SDL_GetMouseState(&x, &y);
        if (y < GRID_TILE_SIZE * GRID_HEIGHT) {
          g.invertWall(make_pair(x / GRID_TILE_SIZE, y / GRID_TILE_SIZE));
          restart();
        } else {
          if (x < SCREEN_WIDTH / 3) {
            restart();
          } else if (x < 2 * SCREEN_WIDTH / 3) {
            playing = !playing;
          } else {
            ++step_count;
          }
        }
      }
    }
  }
}

void Core::update() {
  if ((playing || step_count > 0) && !path_found) {
    path_found = p.breadthFirstSearchStep();
    if (step_count)
      --step_count;
  }
}

void Core::display() {
  if (clear_grid) {
    clear_grid = false;
    redraw_walls = true;

    main_window->clear();
    main_window->setColor(0xdd, 0xdd, 0xdd, 0xff);
    for (int i(0); i < GRID_WIDTH; ++i) {
      for (int j(0); j < GRID_HEIGHT; ++j) {
        main_window->drawRectagle(GRID_TILE_SIZE * i + 1, GRID_TILE_SIZE * j + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
      }
    }
    main_window->drawButtons();
  }

  if (redraw_walls) {
    redraw_walls = false;
    main_window->setColor(0xaa, 0xaa, 0xdd, 0xff);
    for (auto node : g.getWalls()) {
      main_window->drawRectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
    }
  }
  
  main_window->setColor(0xee, 0x3a, 0x3a, 0xff);
  for (auto node : p.getDiscovered()) {
    main_window->drawRectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }
  main_window->setColor(0xaa, 0xdd, 0xaa, 0xff);
  for (auto node : p.getVisited()) {
    main_window->drawRectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }
  main_window->setColor(0xdd, 0xaa, 0xdd, 0xff);
  for (auto node : p.getPath()) {
    main_window->drawRectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }

  main_window->setColor(0x5a, 0xee, 0x5a, 0xff);
  main_window->drawRectagle(GRID_TILE_SIZE * start.first + 1, GRID_TILE_SIZE * start.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  main_window->setColor(0xee, 0x3a, 0x3a, 0xff);
  main_window->drawRectagle(GRID_TILE_SIZE * finish.first + 1, GRID_TILE_SIZE * finish.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  main_window->render();
}

void Core::mainloop() {
  Uint32 start_time;
  Uint32 time;

  start_time = SDL_GetTicks();
  while (!quit) {
    handleInputs();
    update();
    if (SDL_GetTicks() - start_time > SCREEN_TICKS_PER_FRAME) {
      display();
      start_time = SDL_GetTicks();
    }
    //time = SDL_GetTicks() - start_time;
    //if (time < SCREEN_TICKS_PER_FRAME) {
    //  SDL_Delay(SCREEN_TICKS_PER_FRAME - time);
    //}
  }
}

bool Core::init() {
  if (!main_window->init()) {
    cout << "Something went wrong initializing the window" << endl;
    return false;
  }
  
  return true;
}


// Private methods

void Core::restart() {
  p.reset();
  clear_grid = true;
  path_found = false;
}

// measure exec time
//#include <chrono>
//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
//cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << endl;
