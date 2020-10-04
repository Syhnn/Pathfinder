#include "Core.hpp"

#include <chrono>
#include <iostream>
#include "SDL.h"

#include "Window.hpp"


using namespace std;


Core::Core() :
  quit(false),
  first(true),
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


void Core::handle_inputs() {
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      if (e.button.button == SDL_BUTTON_LEFT) {
        int x(0), y(0);
        SDL_GetMouseState(&x, &y);
        g.invertWall(make_pair(x / GRID_TILE_SIZE, y / GRID_TILE_SIZE));
        p.reset();
        first = true;
      }
    }
  }
}

void Core::update() {
  // step in pathfinding
  p.breadthFirstSearchStep();
  // get the grid thingy

}

void Core::display() {
  if (first) {
    first = false;

    std::vector<std::vector<int>> grid = p.getGridState();

    main_window->clear();
    main_window->set_color(0xdd, 0xdd, 0xdd, 0xff);
    for (int i(0); i < GRID_WIDTH; ++i) {
      for (int j(0); j < GRID_HEIGHT; ++j) {
        if (grid[i][j] == node_state::empty) {
          main_window->draw_rectagle(GRID_TILE_SIZE * i + 1, GRID_TILE_SIZE * j + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
        }
      }
    }
    main_window->set_color(0xaa, 0xaa, 0xdd, 0xff);
    for (int i(0); i < GRID_WIDTH; ++i) {
      for (int j(0); j < GRID_HEIGHT; ++j) {
        if (grid[i][j] == node_state::wall) {
          main_window->draw_rectagle(GRID_TILE_SIZE * i + 1, GRID_TILE_SIZE * j + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
        }
      }
    }
  }

  main_window->set_color(0xee, 0x3a, 0x3a, 0xff);
  for (auto node : p.getDiscovered()) {
    main_window->draw_rectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }
  main_window->set_color(0xaa, 0xdd, 0xaa, 0xff);
  for (auto node : p.getVisited()) {
    main_window->draw_rectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }
  main_window->set_color(0xdd, 0xaa, 0xdd, 0xff);
  for (auto node : p.getPath()) {
    main_window->draw_rectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }

  main_window->set_color(0x5a, 0xee, 0x5a, 0xff);
  main_window->draw_rectagle(GRID_TILE_SIZE * start.first + 1, GRID_TILE_SIZE * start.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  main_window->set_color(0xee, 0x3a, 0x3a, 0xff);
  main_window->draw_rectagle(GRID_TILE_SIZE * finish.first + 1, GRID_TILE_SIZE * finish.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  main_window->render();
}

void Core::mainloop() {
  Uint32 start_time;
  Uint32 time;

  start_time = SDL_GetTicks();
  while (!quit) {
    //std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    handle_inputs();
    //cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << endl;
    update();
    //if (SDL_GetTicks() - start_time > SCREEN_TICKS_PER_FRAME) {
      display();
      //start_time = SDL_GetTicks();
    //}
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
