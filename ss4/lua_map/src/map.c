#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

int lua_map(lua_State *L) {
    /* 1st argument: table (t) */
    luaL_checktype(L, 1, LUA_TTABLE);
    /* 2nd argument: function (f) */
    int n = (int)lua_rawlen(L, 1); /* get size of table */

    for (int i = 1; i <=n; ++i) {
        lua_pushvalue(L, 2);
        lua_rawgeti(L, 1, i);
        lua_call(L, 1, 1);
        lua_rawseti(L, 1, i);
    }

    return 0;
}

static const struct luaL_Reg my_lib[] = {
    {"map", lua_map},
    {NULL, NULL},
};

int luaopen_libmy_lib(lua_State *L) {
    luaL_newlib(L, my_lib);
    return 1;
}
