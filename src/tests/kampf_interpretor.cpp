#include <iostream>
#include <cassert>

#include "kampf.hpp"

int main(int argc, char *argv[]) {
  auto kampf = Kampf(enumInitType::Server); 
  auto lua = kampf.getLua();

  if (argc == 2) {
    stringType filename = stringType(argv[1]);
    lua->loadScript(filename);
  }
  else {
    //grab the luascript instance and run the interpretor
    lua->runInterpreter();
  }
  return 0;
}
