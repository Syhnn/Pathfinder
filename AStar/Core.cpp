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
  click(false),
  wall_state(false),

  step_count(0),
  mousex(0),
  mousey(0),

  main_window(new Window()),

  start(10, 10),
  finish(35, 20),
  pos(0, 0),

  g(GRID_WIDTH, GRID_HEIGHT),

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

  if (click) {
    SDL_GetMouseState(&mousex, &mousey);
  }

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      if (e.button.button == SDL_BUTTON_LEFT) {
        SDL_GetMouseState(&mousex, &mousey);
        if (mousey < GRID_TILE_SIZE * GRID_HEIGHT) {
          click = true;
          pos = make_pair(mousex / GRID_TILE_SIZE, mousey / GRID_TILE_SIZE);
          if (!(pos == start) && !(pos == finish)) {
            wall_state = g.empty(pos);
            g.invertWall(pos);
            restart();
          }
        } else {
          if (mousex < SCREEN_WIDTH / 3) {
            restart();
          } else if (mousex < 2 * SCREEN_WIDTH / 3) {
            playing = !playing;
          } else {
            ++step_count;
          }
        }
      }
    } else if (e.type == SDL_MOUSEBUTTONUP) {
      if (e.button.button == SDL_BUTTON_LEFT) {
        click = false;
      }
    }
  }
}

void Core::update() {
  if ((playing || step_count > 0) && !path_found) {
    path_found = p.aStarStep();
    if (step_count)
      --step_count;
  }

  if (click) {
    pair<int, int> newpos = make_pair(mousex / GRID_TILE_SIZE, mousey / GRID_TILE_SIZE);
    if (newpos != pos) {
      pos = newpos;
      if (g.empty(newpos) == wall_state && (!(newpos == start) && !(newpos == finish))) {
        g.invertWall(pos);
        restart();
      }
    }
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
    main_window->setColor(0x55, 0x75, 0x71, 0xff);
    for (auto node : g.getWalls()) {
      main_window->drawRectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
    }
  }

  main_window->setColor(0xa6, 0xdc, 0xef, 0xff);
  for (auto node : p.getCost()) {
    main_window->drawRectagle(GRID_TILE_SIZE * node.first.first + 1, GRID_TILE_SIZE * node.first.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }
  main_window->setColor(0x70, 0x9f, 0xb0, 0xff);
  for (auto node : p.getFrontier()) {
    main_window->drawRectagle(GRID_TILE_SIZE * node.first.first + 1, GRID_TILE_SIZE * node.first.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }
  main_window->setColor(0xdb, 0xc6, 0xeb, 0xff);
  for (auto node : p.getPath()) {
    main_window->drawRectagle(GRID_TILE_SIZE * node.first + 1, GRID_TILE_SIZE * node.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  }

  main_window->setColor(0x86, 0x75, 0xa9, 0xff);
  main_window->drawRectagle(GRID_TILE_SIZE * start.first + 1, GRID_TILE_SIZE * start.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  main_window->setColor(0x86, 0x75, 0xa9, 0xff);
  main_window->drawRectagle(GRID_TILE_SIZE * finish.first + 1, GRID_TILE_SIZE * finish.second + 1, GRID_TILE_SIZE - 1, GRID_TILE_SIZE - 1);
  main_window->render();
}

void Core::mainloop() {
  Uint32 time;

  time = SDL_GetTicks();
  while (!quit) {
    handleInputs();
    update();
    if (SDL_GetTicks() - time > SCREEN_TICKS_PER_FRAME) {
      display();
      time = SDL_GetTicks();
    }
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
  p.resetAStar();
  clear_grid = true;
  path_found = false;
}
