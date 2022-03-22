#ifndef _GAME_H
#define _GAME_H

#include <SDL2/SDL.h>

#include <exception>
#include <vector>
#include <unordered_map>

#include "Timer.hpp"
#include "GamePad.hpp"
#include "Renderer.hpp"
#include "Material.hpp"
#include "DataTypes.hpp"

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
    unsigned int brush_size;
    static const unsigned int size_p = 4;
    std::vector<std::vector<byte>> grid;
    std::unordered_map<MaterialType, byte> weight_values = std::unordered_map<MaterialType, byte>
      ({
       {AIR, 0},
       {WATER, 1},
       {SAND, 5},
       {DIRT, 5},
       {STONE, 10}
     });
    struct Material materials[5] = {
      {
        "Air",
        AIR,
        {228, 240, 239, 255},
        {0, 0, 0, 255}
      },
      {
        "Sand",
        SAND,
        {255, 182, 56, 255},
        {0, 0, 0, 255}
      },
      {
        "Water",
        WATER,
        {20, 142, 255, 255},
        {0, 0, 0, 255}
      },
      {
        "Dirt",
        DIRT,
        {173, 95, 0, 255},
        {0, 0, 0, 255}
      },
      {
        "STONE",
        STONE,
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
    void flow(int r, int c);
    int get_weight(byte c);
    
  public:
    Game(int w, int h);
    ~Game();
};

#endif
