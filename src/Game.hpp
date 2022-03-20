#ifndef _GAME_H_SUB
#define _GAME_H_SUB

#include <SDL2/SDL.h>

#include <exception>
#include <vector>

#include "Timer.hpp"
#include "GamePad.hpp"
#include "Renderer.hpp"
#include "Material.hpp"

using namespace std;

class Game {
  private:
    Renderer* renderer;
    Timer* timer;
    SDL_Window* window;
    bool running;
    Material current_material;
    GamePad gamepad;
    unsigned int display_width;
    unsigned int display_height;
    unsigned int size_w;
    unsigned int size_h;
    vector<vector<int>> grid;
    vector<vector<int>> test;
    
    static const unsigned int size_p = 4;
    struct Material materials[5] = {
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

  private:
    void render();
    void update();
    void input();
  
  public:
    void run();

  public:
    void switchMaterial(MaterialType mt);
    void drop(int r, int c);
    
  public:
    Game(int w, int h);
    ~Game();
};

#endif
