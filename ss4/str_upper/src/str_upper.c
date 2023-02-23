#include <ctype.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static int str_upper(lua_State *L) {
    size_t l;
    luaL_Buffer b;
    const char *s = luaL_checklstring(L, 1, &l);
    luaL_buffinit(L, &b);
    for(size_t i = 0; i < l; ++i) {
        luaL_addchar(&b, toupper((unsigned char)(s[i])));
    }
    luaL_pushresult(&b);
    return 1;
}

static const struct luaL_Reg my_lib[] = {
    {"to_upper", str_upper},
    {NULL, NULL},
};

int luaopen_libmy_lib(lua_State *L) {
    luaL_newlib(L, my_lib);
    return 1;
}
