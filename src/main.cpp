
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#define DISPLAYHEIGHT 300
#define DISPLAYWIDTH 300

bool running;
int currentFrame, lastFrame, frameCount;
SDL_Window *window;
int grid[DISPLAYHEIGHT][DISPLAYWIDTH];

enum MaterialType
{
  AIR,
  SAND,
  WATER,
  DIRT
};

struct Material
{
  MaterialType type;
  const char *typeName;
  SDL_Color color;
  SDL_Color textColor;
} currentMaterial,
  Materials[4] = {
  {
    AIR,
    "Air",
    {228, 240, 239, 255},
    {0, 0, 0, 255}
  },
  {
    SAND,
    "Sand",
    {255, 182, 56, 255},
    {0, 0, 0, 255}
  },
  {
    WATER,
    "Water",
    {20, 142, 255, 255},
    {0, 0, 0, 255}
  },
  {
    DIRT,
    "Dirt",
    {173, 95, 0, 255},
    {0, 0, 0, 255}
  }
};

struct GamePad
{
  int mouseX;
  int mouseY;
  Uint32 mouseState;
} gamePad;


//<--Class Renderer
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
    void render()
    {
      for(int r = 0; r < displayHeight; r++)
      {
        for(int c = 0; c < displayWidth; c++)
        {
          SDL_Rect rect;
          rect.x = c, rect.y = r, rect.w = 1, rect.h = 1;
          SDL_Color color = Materials[grid[r][c]].color;
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderFillRect(renderer, &rect);
        }
      }
      SDL_Rect messageRect;
      messageRect.x = 0;
      messageRect.y = 0;
      messageRect.w = 50;
      messageRect.h = 50;
      SDL_RenderCopy(renderer, materialText, NULL, &messageRect);
    }
    void switchMaterial(Material material)
    {
      if(font == NULL)
      {
        printf(TTF_GetError());
      }
      materialText = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, material.typeName, material.textColor));
    }
    void present()
    {
      SDL_RenderPresent(renderer);
    }
  private:
    unsigned int displayWidth;
    unsigned int displayHeight;
    SDL_Renderer *renderer;
    SDL_Texture *materialText;
    TTF_Font *font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 20);
} *renderer;
//-->


//<--Game functions
void switchMaterial(MaterialType materialType)
{
  currentMaterial = Materials[materialType];
  renderer->switchMaterial(currentMaterial);
}
void input()
{
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      running = false; return;
    }
    switch(event.type)
    {
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_1:
            switchMaterial(static_cast<MaterialType>(0));
            break;
          case SDLK_2:
            switchMaterial(static_cast<MaterialType>(1));
            break;
          case SDLK_3:
            switchMaterial(static_cast<MaterialType>(2));
            break;
          case SDLK_4:
            switchMaterial(static_cast<MaterialType>(3));
            break;
        }
    }
  }
  gamePad.mouseState = SDL_GetMouseState(&gamePad.mouseX, &gamePad.mouseY);
}

void render()
{
  frameCount++;

  int timerFPS = SDL_GetTicks() - currentFrame;
  if(timerFPS < (1000/60.f))
  {
    SDL_Delay((1000/60.f) - timerFPS);
  }

  renderer->render();
  renderer->present();
}

void update()
{
  if(gamePad.mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
  {
    grid[gamePad.mouseY][gamePad.mouseX] = currentMaterial.type;
  }
}
//-->


int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

  window = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAYWIDTH, DISPLAYHEIGHT, 0);
  renderer = new Renderer(window, DISPLAYWIDTH, DISPLAYHEIGHT);
  running = true;
  lastFrame = 0;
  for(int r = 0; r < DISPLAYHEIGHT; r++)
  {
    for(int c = 0; c < DISPLAYWIDTH; c++)
    {
      grid[r][c] = AIR;
    }
  }

  switchMaterial(AIR);
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
    render();
  }

  return 0;
}








