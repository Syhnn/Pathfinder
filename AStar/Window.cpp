#include "Window.hpp"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"


using namespace std;


Window::Window() :
  window(nullptr),
  renderer(nullptr),
  buttons_pict(nullptr)
{}

Window::~Window() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Window::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize - SDL_Error:\n" << SDL_GetError() << endl;
    return false;
  }

  window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    cout << "Window could not be created - SDL_Error:\n" << SDL_GetError() << endl;
    SDL_Quit();
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    cout << "Renderer could not be created - SDL Error:\n" << SDL_GetError() << endl;
    return false;
  }

  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    cout << "SDL_image could not initialize - SDL_image Error:\n" << IMG_GetError() << endl;
    return false;
  }

  string path("buttons.png");
  buttons_pict = loadTexture(path);
  if (buttons_pict == NULL) {
    cout << "Couldn't load picture: " << path << endl;
    return false;
  }

  return true;
}

void Window::display() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);

  SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
  SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
  SDL_RenderFillRect(renderer, &fillRect);

  SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
  SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
  SDL_RenderDrawRect(renderer, &outlineRect);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
  SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);
  for (int i = 0; i < SCREEN_HEIGHT; i += 4)
  {
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
  }
}

void Window::clear() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);
}

void Window::render() {
  SDL_RenderPresent(renderer);
}

void Window::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Window::drawRectagle(int x, int y, int w, int h) {
  SDL_Rect r = {x, y, w, h};
  SDL_RenderFillRect(renderer, &r);
}

void Window::drawButtons() {
  //SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  //SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, SCREEN_HEIGHT - 1);
  //SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, SCREEN_HEIGHT - 50);
  //SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT - 50, 0, SCREEN_HEIGHT);
  //SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 50, SCREEN_WIDTH / 3, SCREEN_HEIGHT);
  //SDL_RenderDrawLine(renderer, 2 * SCREEN_WIDTH / 3, SCREEN_HEIGHT - 50, 2 * SCREEN_WIDTH / 3, SCREEN_HEIGHT);
  //SDL_RenderDrawLine(renderer, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 50, SCREEN_WIDTH - 1, SCREEN_HEIGHT);
  SDL_Rect bottom_panel = { 0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, 50 };
  SDL_RenderCopy(renderer, buttons_pict, NULL, &bottom_panel);
}

SDL_Texture* Window::loadTexture(string path)
{
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  if (loadedSurface == NULL) {
    cout << "Unable to load image " << path << " - SDL_image Error:\n" << IMG_GetError() << endl;
  } else {
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL) {
      cout << "Unable to create texture from " << path << " - SDL Error:\n" << SDL_GetError() << endl;
    }
    SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}
