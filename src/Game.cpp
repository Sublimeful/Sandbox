#include <exception>
#include <stdio.h>
#include <type_traits>
#include <vector>

#include "Game.hpp"

using namespace std;

void Game::render() {
  renderer->render_grid(grid);
  renderer->present();
}

void Game::update()
{
  if(gamepad.mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
  {
    for(int i = -1; i <= 1; i++)
    {
      for(int j = -1; j <= 1; j++)
      {
        int r = gamepad.mouseY/size_p + i;
        int c = gamepad.mouseX/size_p + j;
        if(r >= size_h || r < 0 || c >= size_w || c < 0) break;
        grid[r][c] = current_material.type;
      }
    }
  }
  for(int r = size_h - 1; r >= 0; r--)
  {
    for(int c = 0; c < size_w; c++)
    {
      if(grid[r][c] != AIR && grid[r][c] != STONE)
      {
        drop(r, c);
      }
    }
  }
}

void Game::input()
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
  gamepad.mouseState = SDL_GetMouseState(&gamepad.mouseX, &gamepad.mouseY);
}

void Game::run() {
  /* Main game loop */
  while(running)
  {
    timer->update();
    if(timer->deltaTime() >= 1.0f / 60) {
      input();
      update();
      render();
      timer->reset();
    }
  }
}

void Game::switchMaterial(MaterialType material_type) {
  current_material = materials[material_type];
}

void Game::drop(int r, int c) {
  if(r+1 >= size_h) return;
  if(grid[r+1][c] == AIR)
  {
    swap(grid[r+1][c], grid[r][c]);
  }
  else if(grid[r+1][c-1] == AIR)
  {
    swap(grid[r+1][c-1], grid[r][c]);
  }
  else if(grid[r+1][c+1] == AIR)
  {
    swap(grid[r+1][c+1], grid[r][c]);
  }
}

Game::Game(int display_width, int display_height) :
  display_width(display_width),
  display_height(display_height),
  size_w(display_width / size_p),
  size_h(display_height / size_p),
  grid(size_h, vector<int>(size_w)),
  running(true)
{
  /* Initialize windows and stuff */
  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display_width, display_height, 0);
  
  renderer = new Renderer(window, display_width, display_height, size_p, materials);
  timer = Timer::instance();

  /* Fill grid with AIR */
  for (int r = 0; r < size_h; r++) {
    for (int c = 0; c < size_w; c++) {
      grid[r].push_back(AIR);
    }
  }
}

Game::~Game() {}
