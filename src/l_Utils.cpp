#include "l_Utils.hpp"

boolType lua_isUserdataType(lua_State *L, int index,
			const char *tname) {
    int chk = lua_getmetatable(L, index);
    if (!chk) { return false; }
    lua_getfield(L, LUA_REGISTRYINDEX, tname);
    if (lua_equal(L, -1, -2)) {
	return true;
    }
    return false;
}
