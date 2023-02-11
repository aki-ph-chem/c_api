#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

//#define DUMP

#ifdef DUMP
void dump(lua_State *L, int n){
    printf("n = %d: ",n);
    stack_dump(L);
}
#else 
void dump(lua_State *L, int n){
}
#endif

/* C lang function for Lua VM */
static int lua_sq(lua_State *L){
    double x = luaL_checknumber(L, 1); 
    lua_pushnumber(L, x * x);
    return 1;
}

int main(void){
    lua_State* L = luaL_newstate(); 
    luaL_openlibs(L);
    lua_pushcfunction(L, lua_sq);
    dump(L, 1);
    lua_pushnumber(L, 2);
    dump(L, 2);

    if(lua_pcall(L, 1, 1, 0) != 0)
        error(L, "error running function `lua_sq`: %S", lua_tostring(L, -1));
    dump(L, 3);

    int res = (int)lua_tonumber(L, -1);
    lua_pop(L, -1);
    dump(L, 4);


    printf("res = %d\n", res);
}
