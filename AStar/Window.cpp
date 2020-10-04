#include "Window.hpp"

#include <iostream>

#include "SDL.h"

Window::Window() :
  window(nullptr),
  renderer(nullptr)
{}

Window::~Window() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Window::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void Window::display() {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);

  SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &fillRect);

  SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &outlineRect);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
  for (int i = 0; i < SCREEN_HEIGHT; i += 4)
  {
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
  }
}

void Window::clear() {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
}

void Window::render() {
  SDL_RenderPresent(renderer);
}

void Window::set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Window::draw_rectagle(int x, int y, int w, int h) {
  SDL_Rect r = {x, y, w, h};
  SDL_RenderFillRect(renderer, &r);
}
