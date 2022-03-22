#ifndef _RENDERER_H_SUB
#define _RENDERER_H_SUB

#include <vector>

#include "Material.hpp"

class Renderer {
  private:
    SDL_Window* window;
    unsigned int display_width;
    unsigned int display_height;
    unsigned int size_p;
    SDL_Renderer* internal_renderer;
    Material* materials;

  public:
    void render_grid(std::vector<std::vector<char>> grid);
    void present();

  public:
    Renderer(SDL_Window* w, unsigned int dw, unsigned int dh, unsigned int sp, Material* ms);
    ~Renderer();
};

#endif
