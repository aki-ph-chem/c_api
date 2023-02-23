#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <string.h>

static int lua_split(lua_State *L) {
    const char *s = luaL_checkstring(L, 1); 
    const char *sep = luaL_checkstring(L, 2);
    const char *e;
    int i = 1;

    lua_newtable(L); /* table for result */
    /* repeat for each separator */
    while((e = strchr(s, *sep)) != NULL) {
        lua_pushlstring(L, s, e - s); /* push substring */
        lua_rawseti(L, -2, i++);
        s = e + 1; /* skip separator */
    }
    /* push last substring */
    lua_pushstring(L, s);
    lua_rawseti(L, -2, i);

    return 1;
}

static const struct luaL_Reg my_lib[] = {
    {"split", lua_split},
    {NULL, NULL},
};

int luaopen_libmy_lib(lua_State *L) {
    luaL_newlib(L, my_lib);
    return 1;
}
