#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "tool.h"

/* C lang function for Lua VM */
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

int main(int argc, char** argv) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    /* add C function lua_sq as lua_dir to Lua VM */
    lua_pushcfunction(L, lua_dir);
    lua_setglobal(L,"my_dir");

    char* filename = NULL;
    if(argc < 2){
        fprintf(stderr, "There is no arg\n");
        exit(1);
    } else {
        filename = argv[1];
        if(luaL_loadfile(L,filename) || lua_pcall(L, 0, 0, 0))
            error(L, "cannot open `my_dir.lua`: %s", lua_tostring(L, -1));
    }
}
