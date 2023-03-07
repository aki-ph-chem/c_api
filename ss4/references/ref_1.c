#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    //int r = luaL_ref(L, LUA_REGISTRYINDEX);
    
    /* nilな参照をリリースする, 何も影響を与えない */
    luaL_unref(L, LUA_REGISTRYINDEX, LUA_REFNIL); 

    /* nilなレジストリから値をstackにpushする */
    lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_REFNIL);
    int _val = lua_toboolean(L, -1);
    printf("_val = %d \n", _val);
}
