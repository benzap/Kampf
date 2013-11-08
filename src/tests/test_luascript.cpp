#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_luascript.cpp");

  auto luaScript = LuaScript();

  luaScript.loadString("print('hello world!')");

  luaScript.loadScript("test.lua");

  luaScript.setGlobal("PI", 3.14);
  auto PI_value = luaScript.getGlobal_float("PI");

  TEST_EQUAL(PI_value, 3.14, "global - float");

  luaScript.setGlobal("numChildren", 3);

  auto numChildren = luaScript.getGlobal_int("numChildren");
  
  TEST_EQUAL(numChildren, 3, "global - int");

  luaScript.setGlobal("FirstName", "Benjamin Zaporzan");

  auto firstName = luaScript.getGlobal_string("FirstName");

  TEST_EQUAL(firstName, "Benjamin Zaporzan", "global - string");

  auto floatValues = floatArrayType {1.1, 2.2, 3.3};

  luaScript.setGlobal("Position", floatValues);
  luaScript.loadString("for i,v in ipairs(Position) do print(i,v) end");

  auto floatValues2 = luaScript.getGlobal_floatArray("Position");
  
  TEST_EQUAL(floatValues, floatValues2, "global - float array");

  for (auto i : floatValues2) {
    std::cout << i << std::endl;
  }

  auto intValues = intArrayType { 1, 2, 3 };

  luaScript.setGlobal("oneTwoThree", intValues);
  luaScript.loadString("for i,v in ipairs(oneTwoThree) do print(i,v) end");

  auto intValues2 = luaScript.getGlobal_intArray("oneTwoThree");

  TEST_EQUAL(intValues, intValues2, "global - int array");

  return 0;
}
