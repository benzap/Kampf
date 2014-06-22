#include "l_CustomAttribute.hpp"

CustomAttribute* lua_pushcustomAttribute(lua_State *L, CustomAttribute* customAttribute) {
    if (customAttribute == nullptr) {
	customAttribute = new CustomAttribute();
    }

    CustomAttribute** customAttributePtr = static_cast<CustomAttribute**>
	(lua_newuserdata(L, sizeof(CustomAttribute)));
  
    *customAttributePtr = customAttribute;

    luaL_getmetatable(L, LUA_USERDATA_CUSTOMATTRIBUTE);
    lua_setmetatable(L, -2);  

    return customAttribute;
}

CustomAttribute* lua_tocustomAttribute(lua_State *L, int index) {
    CustomAttribute* customAttribute = *static_cast<CustomAttribute**>
	(luaL_checkudata(L, index, LUA_USERDATA_CUSTOMATTRIBUTE));
    if (customAttribute == NULL) {
	luaL_error(L, "Provided userdata is not of type 'CustomAttribute'");
    }
    return customAttribute;
}

boolType lua_iscustomAttribute(lua_State *L, int index) {
    if (lua_isuserdata(L, index)) {
	auto chk = lua_isUserdataType(L, index, 
				      LUA_USERDATA_CUSTOMATTRIBUTE); 
	return chk;
    }
    return false;
}

static int l_CustomAttribute_CustomAttribute(lua_State *L) {
    lua_pushcustomAttribute(L);
    lua_insert(L, 1);

    if (lua_gettop(L) > 1) {
	l_CustomAttribute_set(L);
	lua_pop(L, 1);
    }

    return 1;
}

static int l_CustomAttribute_isCustomAttribute(lua_State *L) {
    if (lua_iscustomAttribute(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_CustomAttribute_gc(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);
    delete attr;
    return 0;
}

static int l_CustomAttribute_tostring(lua_State *L) {
    
    l_CustomAttribute_type(L);
    stringType theType = luaL_checkstring(L, -1);
    lua_pop(L, 1);
    
    stringType msg = "CustomAttribute: " + theType;
    lua_pushstring(L, msg.c_str());

    return 1;
}

static int l_CustomAttribute_type(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);

    enumAttribute theType = attr->getType();
    
    if (theType == enumAttribute::BOOLEAN) {
	lua_pushstring(L, "BOOL");
    }

    else if (theType == enumAttribute::INTEGER) {
	lua_pushstring(L, "INTEGER");
    }

    else if (theType == enumAttribute::FLOAT) {
	lua_pushstring(L, "FLOAT");
    }

    else if (theType == enumAttribute::CHAR) {
	lua_pushstring(L, "CHAR");
    }

    else if (theType == enumAttribute::VOID) {
	lua_pushstring(L, "VOID");
    }

    else if (theType == enumAttribute::INTEGER_VECTOR) {
	lua_pushstring(L, "ARRAY");
    }

    else if (theType == enumAttribute::FLOAT_VECTOR) {
	lua_pushstring(L, "ARRAY");
    }

    else if (theType == enumAttribute::STRING) {
	lua_pushstring(L, "STRING");
    }

    else if (theType == enumAttribute::VECTOR3) {
	lua_pushstring(L, "VECTOR");
    }

    else {
	lua_pushstring(L, "UNKNOWN");
    }

    return 1;
}

static int l_CustomAttribute_get(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);

    enumAttribute theType = attr->getType();
    
    if (theType == enumAttribute::BOOLEAN) {
	boolType boolValue = attr->get_bool();
	lua_pushboolean(L, (int) boolValue);
    }

    if (theType == enumAttribute::INTEGER) {
	integerType intValue = attr->get_int();
	lua_pushnumber(L, intValue);
    }

    else if (theType == enumAttribute::FLOAT) {
	floatType floatValue = attr->get_float();
	lua_pushnumber(L, floatValue);
    }

    else if (theType == enumAttribute::CHAR) {
	charType charArray[2] = " ";
	charArray[0] = attr->get_char();
	lua_pushstring(L, charArray);
    }

    else if (theType == enumAttribute::VOID) {
	lua_pushnil(L);
    }

    else if (theType == enumAttribute::INTEGER_VECTOR) {
	intArrayType iarray = attr->get_intArray();
	lua_createtable(L, iarray.size(), 0);
	for (int i = 0; i < iarray.size(); i++) {
	    lua_pushnumber(L, iarray[i]);
	    lua_rawseti(L, -2, i+1);
	}
    }

    else if (theType == enumAttribute::FLOAT_VECTOR) {
	floatArrayType farray = attr->get_floatArray();
	lua_createtable(L, farray.size(), 0);
	for (int i = 0; i < farray.size(); i++) {
	    lua_pushnumber(L, farray[i]);
	    lua_rawseti(L, -2, i+1);
	}
    }

    else if (theType == enumAttribute::STRING) {
	stringType stringValue = attr->get_string();
	lua_pushstring(L, stringValue.c_str());
    }

    else if (theType == enumAttribute::VECTOR3) {
	Vector3 vec = attr->get_vector();
	lua_pushvector(L, new Vector3(vec));
    }

    else {
	lua_pushstring(L, "UNKNOWN");
    }

    return 1;
}

static int l_CustomAttribute_set(lua_State *L) {
    if (lua_gettop(L) < 2) {
	luaL_error(L, "Did not provide a value to set");
    }
    auto attr = lua_tocustomAttribute(L, 1);
    
    int luaType = lua_type(L, 2);

    if (luaType == LUA_TNUMBER) {
	floatType fValue = lua_tonumber(L, 2);
	attr->set(fValue);
    }
    else if (luaType == LUA_TSTRING) {
	stringType sValue = lua_tostring(L, 2);
	attr->set(sValue);
    }
    else if (luaType == LUA_TBOOLEAN) {
	integerType bValue = lua_toboolean(L, 2);
	attr->set(bValue);
    }
    //TODO: do proper checking, currently assumes a table of floats
    else if (luaType == LUA_TTABLE) {
	//get the number of elements in the table
	auto tableSize = lua_objlen(L, 2);

	//create a new float array
	floatArrayType* floatArray = new floatArrayType();
	floatType fValue;
	for (int i = 1; i <= tableSize; i++) {
	    lua_rawgeti(L, 2, i);
	    fValue = lua_tonumber(L, -1);
	    floatArray->push_back(fValue);
	    lua_pop(L, 1);
	}
	attr->set(floatArray);
    }
    else {
	luaL_error(L, "Type cannot be converted");
    }

    return 0;
}

static int l_CustomAttribute_getInteger(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);

    enumAttribute theType = attr->getType();
    
    if (theType == enumAttribute::INTEGER) {
	auto iValue = attr->get_int();
	lua_pushnumber(L, iValue);
    }
    else if (theType == enumAttribute::FLOAT) {
	std::cerr << "Lua-Binding: conversion from float" << std::endl;
	auto fValue = attr->get_float();
	lua_pushnumber(L, static_cast<integerType>(fValue));
    }

    return 1;
}

static int l_CustomAttribute_setInteger(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);
    integerType iValue = luaL_checkint(L, 2);
    
    attr->set(iValue);

    return 0;
}

static int l_CustomAttribute_getFloat(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);

    auto fValue = attr->get_float();
    lua_pushnumber(L, fValue);

    return 1;
}

static int l_CustomAttribute_setFloat(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);
    floatType fValue = luaL_checknumber(L, 2);
    
    attr->set(fValue);

    return 0;
}

static int l_CustomAttribute_getChar(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);

    char cArray[2] = " ";
    cArray[0] = attr->get_char();
    lua_pushstring(L, cArray);

    return 1;
}

static int l_CustomAttribute_setChar(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);
    stringType sValue = luaL_checkstring(L, 2);
    
    attr->set(sValue.c_str()[0]);

    return 0;
}

static int l_CustomAttribute_getArray(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);
    
    enumAttribute attrType = attr->getType();
    if (attrType == enumAttribute::FLOAT_VECTOR) {
	auto farray = attr->get_floatArray();
	lua_createtable(L, farray.size(), 0);
	for (int i = 0; i < farray.size(); i++) {
	    lua_pushnumber(L, farray[i]);
	    lua_rawseti(L, -2, i+1);
	}
    }
    else if (attrType == enumAttribute::INTEGER_VECTOR) {
    	auto iarray = attr->get_intArray();
	lua_createtable(L, iarray.size(), 0);
	for (int i = 0; i < iarray.size(); i++) {
	    lua_pushnumber(L, iarray[i]);
	    lua_rawseti(L, -2, i+1);
	}
    }
    else {
	luaL_error(L, "CustomAttribute does not include an array type");
    }

    return 1;
}

static int l_CustomAttribute_setArray(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);

    //get the number of elements in the table
    auto tableSize = lua_objlen(L, 2);

    //create a new float array
    floatArrayType floatArray;
    floatType fValue;
    for (int i = 1; i <= tableSize; i++) {
	lua_rawgeti(L, 2, i);
	fValue = lua_tonumber(L, -1);
	floatArray.push_back(fValue);
	lua_pop(L, 1);
    }
    attr->set(floatArray);

    return 0;
}

static int l_CustomAttribute_getString(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);
    
    auto sValue = attr->get_string();
    lua_pushstring(L, sValue.c_str());

    return 1;
}

static int l_CustomAttribute_setString(lua_State *L) {
    auto attr = lua_tocustomAttribute(L, 1);
    stringType sValue = luaL_checkstring(L, 2);
    attr->set(sValue);

    return 0;
}

static const struct luaL_Reg l_CustomAttribute_Registry [] = {
    {"CustomAttribute", l_CustomAttribute_CustomAttribute},
    {"isCustomAttribute", l_CustomAttribute_isCustomAttribute},
    {NULL, NULL}
};

static const struct luaL_Reg l_CustomAttribute [] = {
    {"__gc", l_CustomAttribute_gc},
    {"__tostring", l_CustomAttribute_tostring},
    {"type", l_CustomAttribute_type},
    {"get", l_CustomAttribute_get},
    {"set", l_CustomAttribute_set},
    {"getInteger", l_CustomAttribute_getInteger},
    {"setInteger", l_CustomAttribute_setInteger},
    {"getFloat", l_CustomAttribute_getFloat},
    {"setFloat", l_CustomAttribute_setFloat},
    {"getChar", l_CustomAttribute_getChar},
    {"setChar", l_CustomAttribute_setChar},
    {"getArray", l_CustomAttribute_getArray},
    {"setArray", l_CustomAttribute_setArray},
    {"getString", l_CustomAttribute_getString},
    {"setString", l_CustomAttribute_setString},
    {NULL, NULL}
};

int luaopen_customAttribute(lua_State *L) {
    //CustomAttribute
    luaL_newmetatable(L, LUA_USERDATA_CUSTOMATTRIBUTE);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_CustomAttribute);

    lua_pop(L, 1);

    luaL_register(L, KF_LUA_LIBNAME, l_CustomAttribute_Registry);
    return 1;
}

