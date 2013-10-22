#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_luascript.cpp");

  auto luaScript = LuaScript();

  luaScript.loadString("print('hello world!')");

  luaScript.loadScript("test.lua");


  return 0;
}
