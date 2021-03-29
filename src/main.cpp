
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <array>



#define DEBUG
#define WIDTH 300
#define HEIGHT 352
#define TILE_SIZE 22
#define TETRIS_W 10
#define TETRIS_H 16

bool running;

SDL_Renderer *renderer;
SDL_Window *window;

int frameCount, timerFPS, lastFrame, fps;
bool left, right, up, down, space;

bool landed[TETRIS_H][TETRIS_W];

struct block
{
  SDL_Color color;
  bool active;
};

using matrix = bool[4][4];
using spawnLocation = std::array<double, 2>;

spawnLocation getSpawn()
{
  spawnLocation a{rand()%4+(double)2,(double)-(rand() % 5) - 4};
  return a;
}

struct shape
{
  SDL_Color color;
  matrix matrix;
  double x, y;
  int size;
  int index;
};

//<-- blocks
shape blocks[7] = {{{255,165,0},
  {{0,0,1,0} // L BLOCK
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },0,0,3,0}
,{{255,0,0}, // Z BLOCK
  {{1,1,0,0}
    ,{0,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },0,0,3,1}
,{{224,255,255}, // I BLOCK
  {{0,0,0,0}
    ,{1,1,1,1}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },0,0,4,2}
,{{0,0,255}, // J BLOCK
  {{1,0,0,0}
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },0,0,3,3}
,{{255,255,0}, // O BLOCK
  {{1,1,0,0}
    ,{1,1,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },0,0,2,4}
,{{0,0,255}, // S BLOCK
  {{0,1,1,0}
    ,{1,1,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },0,0,3,5}
,{{128,0,128}, // T BLOCK
  {{0,1,0,0}
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
  },0,0,3,6}}, cur;
//-->

//<--Rotation
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
  for(int row = 0; row < s.size; row ++) {
    for(int col = 0; col < s.size; col++) {
      tmp.matrix[row][col]=s.matrix[col][row];
    }
  }
  return tmp;
}


void rotate()
{
  cur = reverseCols(transpose(cur));
}
//-->

SDL_Rect rect;
void draw(shape s)
{
  for(int row = 0; row < TETRIS_H; row++)
  {
    for(int col = 0; col < TETRIS_W; col++)
    {
      rect.x = col * TILE_SIZE; rect.y = row * TILE_SIZE;
      if(landed[row][col])
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      else
        SDL_SetRenderDrawColor(renderer, 82, 82, 82, 255);
      SDL_RenderFillRect(renderer, &rect);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
  for(int row = 0; row < s.size; row++)
  {
    for(int col = 0; col < s.size; col++)
    {
      if(s.matrix[row][col] && s.y + row >= 0)
      {
        rect.x = (s.x + col) * TILE_SIZE; rect.y = (s.y + row) * TILE_SIZE;
        SDL_SetRenderDrawColor(renderer, s.color.r, s.color.g, s.color.b, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
      }
    }
  }
}

void printLanded()
{
  printf("\n");
  for(int r = 0; r < TETRIS_H; r++)
  {
    for(int c = 0; c < TETRIS_W; c++)
    {
      printf("%d ", landed[r][c]);
    }
    printf("\n");
  }
}

void spawnNew()
{
  cur = blocks[cur.index = rand() % 7];
  cur.x = getSpawn()[0], cur.y = getSpawn()[1];
  for(int i = 0; i < rand() % 4; i++)
  {
    rotate();
  }
}

//checks if there is collision for given imaginary shape s
bool collision(shape s, int x, int y)
{
  s.x = x, s.y = y;
  for(int row = 0; row < s.size; row++)
  {
    for(int col = 0; col < s.size; col++)
    {
      if(s.matrix[row][col]) //if there is a block at position
      {
        if(s.x + col > TETRIS_W - 1 || s.x + col < 0 || s.y + row > TETRIS_H - 1) return true;
        if(s.y + row < 0) continue;
        if(landed[(int)s.y + row][(int)s.x + col]) //check if there is landed in real position
        {
          return true;
        }
      }
    }
  }
  return false;
}

bool isGrounded(shape s)
{
  for(int row = 0; row < s.size; row++)
  {
    for(int col = 0; col < s.size; col++)
    {
      if(collision(s, s.x, s.y + 1)) //adding 1 to simulate moving the block down 1 and checking for collision
      {
        return true;
      }
    }
  }
  return false;
}

void land()
{
  for(int r = 0; r < cur.size; r++)
  {
    for(int c = 0; c < cur.size; c++)
    {
      if(cur.y + r < 0) //game over
      {
        printf("GAME OVER");
        running = false;
        return;
      }
      if(cur.matrix[r][c]) 
      {
        landed[(int)cur.y + r][(int)cur.x + c] = true;
      }
    }
  }
  cur.index = -1;
}

void clearLines()
{
  for(int r = 0; r < TETRIS_H; r++) 
  {
    bool line = true;
    for(int c = 0; c < TETRIS_W; c++)
    {
      if(!landed[r][c]) 
      {
        line = false; 
        break;
      }
    }
    if(line)
    {
      for(int row = r; row > 0; row--)
      {
        for(int col = 0; col < TETRIS_W; col++) 
        {
          landed[row][col] = landed[row - 1][col];
        }
      }
    }
  }
}

void drop() //drop EET
{
  if(!collision(cur, cur.x, cur.y + 1))
  {
    cur.y++;
  }
}

//<--Update
void update()
{
  if(left && !collision(cur, cur.x - 1, cur.y)) 
  {
    cur.x--;
  }
  if(right && !collision(cur, cur.x + 1, cur.y)) 
  {
    cur.x++;
  }
  if(down && !collision(cur, cur.x, cur.y + 1)) 
  {
    cur.y++;
  }
  if(up)
  {
    if(!collision(reverseCols(transpose(cur)), cur.x, cur.y))
    {
      rotate(); 
    }
    else if(!collision(reverseCols(transpose(cur)), cur.x + 1, cur.y))
    {
      rotate(); 
      cur.x++;
    }
    else if(!collision(reverseCols(transpose(cur)), cur.x - 1, cur.y))
    {
      rotate(); 
      cur.x--;
    }
  }
  if(space)
  {
    while(!isGrounded(cur))
    {
      drop();
    }
    land();
    clearLines();
    spawnNew();
    return;
  }
  if(frameCount == 0)
  {
    drop();
    if(isGrounded(cur))
    {
      land();
      clearLines();
    }
    if(cur.index == -1)
    {
      spawnNew();
    }
  }
#ifdef DEBUG
//  printf("%5.d %5.d %5.d %5.d\n", frameCount, timerFPS, lastFrame, fps);
#endif
}
//-->

//<-- input
void input()
{
  up = down = left = right = space = 0;
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
          case SDLK_SPACE:
            space = 1;
            break;
          case SDLK_ESCAPE:
            running = false;
            break;
        #ifdef DEBUG
          case SDLK_1:
            cur = blocks[0];
            break;
          case SDLK_2:
            cur = blocks[1];
            break;
          case SDLK_3:
            cur = blocks[2];
            break;
          case SDLK_4:
            cur = blocks[3];
            break;
          case SDLK_5:
            cur = blocks[4];
            break;
          case SDLK_6:
            cur = blocks[5];
            break;
          case SDLK_7:
            cur = blocks[6];
            break;
        #endif
        }
    }
  }
}
//-->

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
  spawnNew();
  rect.w = rect.h = TILE_SIZE;

  for(int row = 0; row < TETRIS_H; row++)
  {
    for(int col = 0; col < TETRIS_W; col++)
    {
      landed[row][col] = 0;
    }
  }

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







