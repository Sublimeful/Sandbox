#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <SDL2/SDL.h>
#include "DataTypes.hpp"

enum MaterialType : byte
{
  AIR,
  SAND,
  WATER,
  DIRT,
  STONE
};

struct Material
{
  const char *typeName;
  MaterialType type;
  SDL_Color color;
  SDL_Color textColor;
};

#endif
