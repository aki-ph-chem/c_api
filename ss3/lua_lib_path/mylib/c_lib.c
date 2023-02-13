#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

/* function for C library of Lua */
static int lua_dir(lua_State *L){
    DIR* dir;
    struct dirent *entry;
    const char* path = luaL_checkstring(L, 1);

    /* opent directory */
    dir = opendir(path);
    if(dir == NULL) {
        lua_pushnil(L); /* error openign the directory? */
        lua_pushstring(L, strerror(errno)); /* error message */
        return 2;
    }

    /* careate result table */
    lua_newtable(L);
    int i = 1;
    while((entry = readdir(dir))) {
        lua_pushnumber(L, i++); /* push key */
        lua_pushstring(L, entry->d_name);
        lua_settable(L, -3);
    }

    closedir(dir);
    return 1;
}

static int add(lua_State *L) {
    int x = (int)luaL_checknumber(L, -1);
    int y = (int)luaL_checknumber(L, -2); 
    lua_pushnumber(L, x + y);
    return 1;
}

static int greet(lua_State *L) {
    const char* your_name = luaL_checkstring(L, -1);
    printf("Hello %s \n", your_name);
    return 1;
}

/* this array store list of function */
static const struct luaL_Reg my_lib[] = {
    {"dir", lua_dir},
    {"c_add", add},
    {"greet", greet},
    {NULL, NULL} /* setntinel */
};

/* entry point */
int luaopen_libmy_lib(lua_State* L) {
    luaL_newlib(L, my_lib);
    return 1;
}
