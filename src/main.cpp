
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>


#define WIDTH 300
#define HEIGHT 300
#define TILE_SIZE 22
#define TETRIS_W 10
#define TETRIS_H 20

bool running;

SDL_Renderer *renderer;
SDL_Window *window;

int frameCount, timerFPS, lastFrame, fps;
bool left, right, up, down;

struct block
{
  SDL_Color color;
  bool active;
};

struct shape
{
  SDL_Color color;
  bool matrix[4][4];
  double x, y;
  int size;
};



shape blocks[7] = {{{255,165,0},
  {{0,0,1,0} // L BLOCK
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },5,4,3}
,{{255,0,0}, // Z BLOCK
  {{1,1,0,0}
    ,{0,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },5,4,3}
,{{224,255,255}, // I BLOCK
  {{1,1,1,1}
    ,{0,0,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },5,4,4}
,{{0,0,255}, // J BLOCK
  {{1,0,0,0}
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },5,4,3}
,{{255,255,0}, // O BLOCK
  {{1,1,0,0}
    ,{1,1,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },5,4,2}
,{{0,0,255}, // S BLOCK
  {{0,1,1,0}
    ,{1,1,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },5,4,3}
,{{128,0,128}, // T BLOCK
  {{0,1,0,0}
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },5,4,3}}, cur;

shape reverseCols(shape s)
{
  shape tmp = s;
  for(int row = 0; row < s.size; row++)
  {
    for(int col = 0; col < s.size/2; col++)
    {
      bool t = s.matrix[row][col];
      tmp.matrix[row][col] = s.matrix[row][s.size-col-1];
      tmp.matrix[row][s.size-col-1] = t;
    }
  }
  return tmp;
}

shape transpose(shape s)
{
  shape tmp = s;
  for(int row = 0; row < s.size; row++)
  {
    for(int col = 0; col < s.size; col++)
    {
      tmp.matrix[row][col] = s.matrix[col][row];
    }
  }
  return tmp;
}

void rotate()
{
  cur = reverseCols(transpose(cur));
}

SDL_Rect rect;
void draw(shape s)
{
  for(int row = 0; row < TETRIS_W; row++)
  {
    for(int col = 0; col < TETRIS_H; col++)
    {

      
    }
  }
  for(int row = 0; row < s.size; row++)
  {
    for(int col = 0; col < s.size; col++)
    {
      if(s.matrix[row][col])
      {
        rect.x = (s.x + col) * TILE_SIZE; rect.y = (s.y + row) * TILE_SIZE;
        SDL_SetRenderDrawColor(renderer, s.color.r, s.color.g, s.color.b, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 219, 219, 219, 255);
        SDL_RenderDrawRect(renderer, &rect);
      }
    }
  }
}

void update()
{
  if(left) cur.x--;
  if(right) cur.x++;
  if(down) cur.y++;
  if(up) rotate();
}

void input()
{
  up = down = left = right = 0;
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT) running = false;
    switch(event.type)
    {
      case SDL_KEYDOWN: //down
        switch(event.key.keysym.sym)
        {
          case SDLK_LEFT:
            left = 1;
            break;
          case SDLK_RIGHT:
            right = 1;
            break;
          case SDLK_UP:
            up = 1;
            break;
          case SDLK_DOWN:
            down = 1;
            break;
          case SDLK_ESCAPE:
            running = false;
            break;
        }
    }
  }
}

void render()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  frameCount++;
  int timerFPS = SDL_GetTicks() - lastFrame;
  if(timerFPS < (1000/60))
  {
    SDL_Delay((1000/60) - timerFPS);
  }

  draw(cur);

  SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  cur = blocks[rand() % 7];
  rect.w = rect.h = TILE_SIZE;

  running = true;
  static int lastTime = 0;
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) printf("Failed at SDL_INIT!");
  if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) printf("Failed at creation of Window and Renderer");
  SDL_SetWindowTitle(window, "Tetris");

  while(running)
  {
    lastFrame = SDL_GetTicks();
    if(lastFrame >= (lastTime + 1000))
    {
      lastTime = lastFrame;
      fps = frameCount;
      frameCount = 0;
    }

    update();
    input();
    render();
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}







