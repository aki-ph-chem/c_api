#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>
#include "tool.h" /* for eroor, stack_dump */ 

// VM of Lua
lua_State* L = NULL;

// wrapp function f in Lua
double dadd_two(double x, double y) {
    lua_getglobal(L,"add_two");
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);

    // call function from Lua VM
    if(lua_pcall(L, 2, 1, 0) != 0)
        error(L, "error running function `add_two`: %s", lua_tostring(L,-1));

    // retrieve result
    if(!lua_isnumber(L, -1))
        error(L,"function `add_two` must return a number");
    double z = lua_tonumber(L, -1);
    lua_pop(L, -1);

    return z;
}

int iadd_two(int x, int y) {
    lua_getglobal(L,"add_two");
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);

    // call function from Lua VM 
    if(lua_pcall(L, 2, 1, 0) != 0)
        error(L, "error running function `add_two`: %s", lua_tostring(L,-1));

    // retrieve result
    if(!lua_isnumber(L, -1))
        error(L,"function `add_two` must return a number");
     int res = (int)lua_tonumber(L, -1);
    lua_pop(L, -1);

    return res;
}

int main(void) {
    // gen Lua stack 
    L = luaL_newstate();
    luaL_openlibs(L);
    // load *.lua file
    if(luaL_loadfile(L,"lua_func.lua") || lua_pcall(L, 0, 0, 0))
        fprintf(stderr,"Error: No such file: %s \n", lua_tostring(L,-1));
    double res_double = dadd_two(1.1, 2.3);
    printf("res_double = %lf\n",res_double);

    int res_int = iadd_two(1, 1); 
    printf("res_int = %d\n",res_int);
}
