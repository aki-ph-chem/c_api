#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>

/* 変数のアドレスをkeyにする */

int main(void) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    /* variable with an unique address */
    static const char key = 'k'; 
    int my_number = 123;
    /* store a number */
    lua_pushlightuserdata(L, (void *)&key); /* push address */
    lua_pushnumber(L, my_number); /* push value */ 
    /* registry[&key] = my_number */
    lua_settable(L, LUA_REGISTRYINDEX);

    /* retrive a number */
    lua_pushlightuserdata(L, (void *)&key); /* push address */
    lua_gettable(L, LUA_REGISTRYINDEX); /* retrive value */
    int my_number_lua = 0;
    my_number_lua = lua_tonumber(L, -1); /* convert to number */
    printf("my_number_lua = %d\n", my_number_lua);
}
