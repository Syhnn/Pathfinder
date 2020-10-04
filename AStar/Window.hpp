#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <cstdint>


const int GRID_WIDTH = 50;
const int GRID_HEIGHT = 40;
const int GRID_TILE_SIZE = 16;

const int SCREEN_WIDTH = GRID_TILE_SIZE * GRID_WIDTH;
const int SCREEN_HEIGHT = GRID_TILE_SIZE * GRID_HEIGHT;

struct SDL_Window;
struct SDL_Renderer;


class Window {
public:
  Window();
  ~Window();

  bool init();
  void display();
  void render();
  void clear();
  void set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void draw_rectagle(int x, int y, int w, int h);

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
};

#endif // _WINDOW_HPP_
