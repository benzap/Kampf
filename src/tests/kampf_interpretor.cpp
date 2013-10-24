#include <iostream>
#include <cassert>

#include "kampf.hpp"

int main(int argc, char *argv[]) {
  auto kampf = Kampf(enumInitType::Server); 
  
  //grab the luascript instance and run the interpretor
  kampf.getLua()->runInterpreter();

  return 0;
}
