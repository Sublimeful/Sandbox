#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>

#include "Material.hpp"
#include "DataTypes.hpp"

class Renderer {
  private:
    SDL_Window* window;
    unsigned int display_width;
    unsigned int display_height;
    unsigned int size_p;
    SDL_Renderer* internal_renderer;
    Material* materials;

  public:
    void render_grid(std::vector<std::vector<byte>> grid);
    void present();

  public:
    Renderer(SDL_Window* w, unsigned int dw, unsigned int dh, unsigned int sp, Material* ms);
    ~Renderer();
};

#endif
