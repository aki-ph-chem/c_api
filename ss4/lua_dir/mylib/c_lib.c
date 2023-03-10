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
        lua_pushnil(L); /* error openign the directory? */ lua_pushstring(L, strerror(errno)); /* error message */
        return 2;
    }

    /* careate result table */
    lua_newtable(L);
    int i = 1;
    while((entry = readdir(dir))) {
        lua_pushstring(L, entry->d_name);
        lua_rawseti(L, -2, i++); /* set table at key `i` */
    }

    closedir(dir);
    return 1;
}

/* this array store list of function */
static const struct luaL_Reg my_lib[] = {
    {"dir", lua_dir},
    {NULL, NULL} /* setntinel */
};

/* entry point */
int luaopen_libmy_lib(lua_State* L) {
    luaL_newlib(L, my_lib);
    return 1;
}
