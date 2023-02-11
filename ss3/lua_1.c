#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

//#define TEST

/* C lang function for Lua VM */
static int lua_sq(lua_State *L){
    double x = luaL_checknumber(L, 1); 
    lua_pushnumber(L, x * x);
    return 1;
}

int main(int argc, char** argv) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    /* add C function lua_sq as my_sq to Lua VM */
    lua_pushcfunction(L, lua_sq);
    lua_setglobal(L,"my_sq");

    char* filename = NULL;
    if(argc < 2){
#ifdef TEST
        filename = "my_sq.lua";
        if(luaL_loadfile(L,filename) || lua_pcall(L, 0, 0, 0))
            error(L, "cannot open `my_sq.lua`: %s", lua_tostring(L, -1));
#else
        fprintf(stderr, "There is no file\n");
        exit(1);
#endif
    } else {
        filename = argv[1];
        if(luaL_loadfile(L,filename) || lua_pcall(L, 0, 0, 0))
            error(L, "cannot open `my_sq.lua`: %s", lua_tostring(L, -1));
    }
}
