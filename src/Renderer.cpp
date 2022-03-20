#include "Renderer.hpp"

Renderer::Renderer(SDL_Window* w, unsigned int dw, unsigned int dh, unsigned int sp, Material* ms) :
  window(w), display_width(dw), display_height(dh), size_p(sp), materials(ms) {
  internal_renderer = SDL_CreateRenderer(window, -1, 0);
}

void Renderer::render_grid(std::vector<std::vector<int>> grid) {
  for(int r = 0; r < display_height / size_p; r++)
  {
    for(int c = 0; c < display_width / size_p; c++)
    {
      SDL_Rect rect;
      rect.x = c * size_p;
      rect.y = r * size_p;
      rect.w = size_p;
      rect.h = size_p;
      SDL_Color color = materials[grid[r][c]].color;
      SDL_SetRenderDrawColor(internal_renderer, color.r, color.g, color.b, color.a);
      SDL_RenderFillRect(internal_renderer, &rect);
    }
  }
}

void Renderer::present() {
  SDL_RenderPresent(internal_renderer);
}
