#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static int _concat(lua_State *L) {
    const char* s_1 = luaL_checkstring(L, 1);
    const char* s_2 = luaL_checkstring(L, 2);
    lua_pushstring(L, s_1);
    lua_pushstring(L, s_2);
    lua_concat(L, 2);
    return 1;
}

static const struct luaL_Reg my_lib[] = {
    {"concat", _concat},
    {NULL, NULL},
};

int luaopen_libmy_lib(lua_State *L) {
    luaL_newlib(L, my_lib);
    return 1;
}
