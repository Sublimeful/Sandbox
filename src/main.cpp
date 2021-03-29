
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <array>

bool running;

unsigned int displayHeight = 300;
unsigned int displayWidth = 300;

int currentFrame, lastFrame, frameCount;

class Renderer
{
  public:
    Renderer(SDL_Window *window, unsigned int displayWidth, unsigned int displayHeight)
      : displayWidth(displayWidth)
      , displayHeight(displayHeight)
      , renderer(nullptr)
    {
      renderer = SDL_CreateRenderer(window, -1, 0);
    }
    void Present()
    {
      SDL_RenderPresent(renderer);
    }
  private:
    unsigned int displayWidth;
    unsigned int displayHeight;
    SDL_Renderer *renderer;
};

//<--Game functions
void input()
{
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      running = false; return;
    }
  }
}

void render(Renderer renderer)
{
  frameCount++;

  int timerFPS = SDL_GetTicks() - currentFrame;
  if(timerFPS < (1000/60.f))
  {
    SDL_Delay((1000/60.f) - timerFPS);
  }

  renderer.Present();
}

void update()
{
  
}
//-->

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth, displayHeight, 0);
  Renderer renderer(window, displayWidth, displayHeight);

  running = true;
  lastFrame = 0;

  while(running)
  {
    currentFrame = SDL_GetTicks();
    if(currentFrame >= lastFrame + 1000)
    {
      lastFrame = currentFrame;
      frameCount = 0;
    }
    input();
    update();
    render(renderer);
  }

  return 0;
}








