#include <SDL.h>
#include <complex>
#include <iostream>
#include <math.h>

#define PI 3.14159265
#define WIDTH 640
#define HEIGHT 640
#define SIZE 255

int palette[SIZE][3];

void generatePalette() {
  for (int i = 0; i <= SIZE; i++) {
    palette[i][0] = i;
    palette[i][1] = i;
    palette[i][2] = i;
  }
}

double map(int n, double start1, double stop1, double start2, double stop2) {
  double newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
  return newval;
}

void renderMandelbrot(SDL_Renderer *ren) {
  for (int x = 0; x <= WIDTH; x++) {
    for (int y = 0; y <= HEIGHT; y++) {
      std::complex<double> c(map(x, 0, WIDTH, -2.0, 2.0),
                             map(y, 0, HEIGHT, -2.0, 2.0));
      std::complex<double> z(0.0, 0.0);
      int counter = 0;

      while (counter < SIZE) {
        z = z * z + c;
        if (abs(z) > 2.0)
          break;
        counter++;
      }
      SDL_SetRenderDrawColor(ren, palette[counter][0], palette[counter][1],
                             palette[counter][2], 0xff);
      SDL_RenderDrawPoint(ren, x, y);
    }
  }
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "message " << SDL_GetError() << std::endl;
    return 1;
  }

  generatePalette();
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window,
                              &renderer);

  bool done = SDL_FALSE;
  while (!done) {
    SDL_Event e;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    renderMandelbrot(renderer);
    SDL_RenderPresent(renderer);

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        done = true;
      }
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        done = true;
      }
    }
  }

  // Cleanup
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}