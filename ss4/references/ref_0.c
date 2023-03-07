#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>

//#define TEST

int main(void) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    /* push string to stack */
    char my_str[] = "foo";
    lua_pushstring(L, my_str);
    /* pop str from stack to registry and return reference r */
    int r = luaL_ref(L, LUA_REGISTRYINDEX);

#ifdef TEST
    const char *my_str_stack = lua_tostring(L, -1);
    if(!my_str_stack) {
        fprintf(stderr, "my_str_stack is NULL\n");
    }else{
        printf("str_lua = %s\n",my_str_stack);
    }
#endif

#ifndef TEST 
    /* get value from registry to stack */
    lua_rawgeti(L, LUA_REGISTRYINDEX, r);
    const char *my_str_stack = lua_tostring(L, -1);
    printf("str_lua = %s\n",my_str_stack);

    /* Finally release both the value and reference */
    luaL_unref(L, LUA_REGISTRYINDEX, r);
#endif
}
