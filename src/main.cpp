
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <array>

#define DISPLAYHEIGHT 600
#define DISPLAYWIDTH 800

bool running;
int currentFrame, lastFrame, frameCount;
SDL_Window *window;
const unsigned int pSize = 4;
const unsigned int sizeW = DISPLAYWIDTH/pSize;
const unsigned int sizeH = DISPLAYHEIGHT/pSize;
std::array<std::array<int, sizeW>, sizeH> grid;

enum MaterialType
{
  AIR,
  SAND,
  WATER,
  DIRT,
  STONE
};

struct Material
{
  MaterialType type;
  const char *typeName;
  SDL_Color color;
  SDL_Color textColor;
} currentMaterial,
  Materials[5] = {
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
  },
  {
    STONE,
    "STONE",
    {128, 128, 128, 255},
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
      for(int r = 0; r < sizeH; r++)
      {
        for(int c = 0; c < sizeW; c++)
        {
          SDL_Rect rect;
          rect.x = c * pSize, rect.y = r * pSize, rect.w = pSize, rect.h = pSize;
          SDL_Color color = Materials[grid[r][c]].color;
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderFillRect(renderer, &rect);
        }
      }
      SDL_Rect messageRect;
      messageRect.x = 20;
      messageRect.y = -30;
      messageRect.w = 175;
      messageRect.h = 175;
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
    TTF_Font *font = TTF_OpenFont("res/fonts/OpenSans-Bold.ttf", 20);
} *renderer;
//-->


//<--Game functions
void switchMaterial(MaterialType materialType)
{
  currentMaterial = Materials[materialType];
  renderer->switchMaterial(currentMaterial);
}

void drop(int r, int c)
{
  if(r+1 >= sizeH) return;
  if(grid[r+1][c] == AIR)
  {
    std::swap(grid[r+1][c], grid[r][c]);
  }
  else if(grid[r+1][c-1] == AIR)
  {
    std::swap(grid[r+1][c-1], grid[r][c]);
  }
  else if(grid[r+1][c+1] == AIR)
  {
    std::swap(grid[r+1][c+1], grid[r][c]);
  }
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
          case SDLK_5:
            switchMaterial(static_cast<MaterialType>(4));
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
    for(int i = -1; i <= 1; i++)
    {
      for(int j = -1; j <= 1; j++)
      {
        int r = gamePad.mouseY/pSize + i;
        int c = gamePad.mouseX/pSize + j;
        if(r >= sizeH || r < 0 || c >= sizeW || c < 0) break;
        grid[r][c] = currentMaterial.type;
      }
    }
  }
  for(int r = sizeH; r >= 0; r--)
  {
    for(int c = 0; c < sizeW; c++)
    {
      if(grid[r][c] != AIR && grid[r][c] != STONE)
      {
        drop(r, c);
      }
    }
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
  for(int r = 0; r < sizeH; r++)
  {
    for(int c = 0; c < sizeW; c++)
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








