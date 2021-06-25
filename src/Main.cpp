#include <SDL.h>
#include <iostream>

void SDL_PrintError(std::string message) {
  std::cout << "message " << SDL_GetError() << std::endl;
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_PrintError("SDL_Init Error: ");
    return 1;
  }

  SDL_Window *win =
      SDL_CreateWindow("Hello world!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    SDL_PrintError("SDL_Init Error: ");
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(
      win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr) {
    SDL_DestroyWindow(win);
    SDL_PrintError("SDL_CreateRenderer Error: ");
    SDL_Quit();
    return 1;
  }

  std::string imagePath = "hello.bmp";
  SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
  if (bmp == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_PrintError("SDL_Surface Error: ");
    SDL_Quit();
    return 1;
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
  SDL_FreeSurface(bmp);
  if (tex == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_PrintError("SDL_CreateTextureFromSurface Error: ");
    SDL_Quit();
    return 1;
  }

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, tex, NULL, NULL);
      SDL_RenderPresent(ren);

      if (e.type == SDL_KEYDOWN) {
        quit = true;
      }
    }
  }

  SDL_Quit();
  return 0;
}