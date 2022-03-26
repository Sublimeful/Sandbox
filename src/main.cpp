#include <cstdio>
#include <stdio.h>
#include "Game.hpp"

#define DISPLAYHEIGHT 600
#define DISPLAYWIDTH 800

int main(int argc, char *argv[])
{
  Game* game = new Game(DISPLAYWIDTH, DISPLAYHEIGHT);
  game->run();

  return 0;
}








