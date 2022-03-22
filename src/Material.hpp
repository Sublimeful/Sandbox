#ifndef _MATERIAL_H_SUB
#define _MATERIAL_H_SUB

#include <SDL2/SDL.h>

enum MaterialType : char
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
};

MaterialType cast(int n);

#endif
