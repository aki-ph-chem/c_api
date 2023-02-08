#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tool.h" /* for error, stack_dump */ 

void load_config (char *filename, int *width, int *height) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if(luaL_loadfile(L,filename) || lua_pcall(L,0,0,0)) {
        error(L,"cannot run cofiguration file: %s", lua_tostring(L,-1));
    }
    lua_getglobal(L,"width");
    lua_getglobal(L,"height");
    if(!lua_isnumber(L,-2))
        error(L,"`width` should be a number: %s", lua_tostring(L,-1));
    if(!lua_isnumber(L,-1))
        error(L,"`height` should be a number: %s", lua_tostring(L,-1));
    *width = (int)lua_tonumber(L, -2); 
    *height = (int)lua_tonumber(L, -1); 
}

int main(void) {
    int width = 0, height = 0;
    load_config("config.lua",&width, &height);
    printf("widht = %d, height = %d\n", width, height);
}
