#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <strings.h>
#include <wchar.h>

// stack の中身をダンプする関数
static void stack_dump(lua_State* L) {
    int index = 0;
    int top = lua_gettop(L);
    for( index = 1; index <= top; ++index) {
        int t = lua_type(L,index);
        switch(t) {
            case LUA_TSTRING: /* strings */
                printf("`%s`", lua_tostring(L,index));
                break;

            case LUA_TBOOLEAN: /* booleans */
                printf(lua_toboolean(L,index) ? "true" : "false");
                break;

            case LUA_TNUMBER: /* number */
                printf("%g", lua_tonumber(L,index));
                break;

            default: /* other values */
                printf("%s", lua_typename(L,t));
                break;
        }
        printf(" ");
    }
    printf("\n");
}

int main(void) {
    lua_State* L = luaL_newstate();

    // true, 10, nil, "hello"をpush
    lua_pushboolean(L,1); 
    lua_pushnumber(L,10);
    lua_pushnil(L);
    lua_pushstring(L,"hello");
    stack_dump(L);

    // -4をpush
    lua_pushvalue(L, -4); 
    stack_dump(L);

    // replace
    lua_replace(L,3);
    stack_dump(L);

    // 6をsettop
    lua_settop(L,6);
    stack_dump(L);

    // -3をremove
    lua_remove(L, -3);
    stack_dump(L);

    // -5をsettop
    lua_settop(L,-5); 
    stack_dump(L);

    lua_close(L);
    return 0;
}
