#include <iostream>
#include <cassert>

#include "KF_test.hpp"

#include <SDL2\SDL.h>


int main(int argc, char *argv[]) {
  TEST_NAME("test_kampf.cpp");
  auto kampf = Kampf(enumInitType::Server); 

  SDL_Init( SDL_INIT_VIDEO );
  SDL_Quit();
  return 0;
}
