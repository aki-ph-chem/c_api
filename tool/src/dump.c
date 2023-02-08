#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>

void stack_dump(lua_State *L) {
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
