#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

#define MAX_COLOR 255
#define DUMP 
#ifdef DUMP
void dump(lua_State *L, int n){
    printf("n = %d: ",n);
    stack_dump(L);
}
#else 
void dump(lua_State *L, int n){
}
#endif

lua_State *L = NULL;

/* struct for represent color */
struct Color {
    double red, green, blue;
};

/* show member of struct Color */
void show_color(const struct Color* color) {
    printf("red = %lf, green = %lf, bule = %lf\n"
            , color->red, color->green, color->blue);
}

/* get member of table background in *.lua file */
double getfiled(const char* key) {
    double result;
    lua_pushstring(L, key);
    dump(L,9);
    lua_gettable(L, -2); /* get background[key] */ 
    dump(L,10);
    if(!lua_isnumber(L, -1))
        error(L, "invalid component in background color");
    result = (double)lua_tonumber(L, -1) * MAX_COLOR;
    lua_pop(L, 1); /* remove number */ 
    dump(L,11);
    return result;
}

/* set member of struct Color form *.lua file */
void load_config (char *filename, struct Color* color) {
    luaL_openlibs(L);

    if(luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        error(L,"cannot run cofiguration file: %s", lua_tostring(L,-1));

    dump(L, 3);
    lua_getglobal(L,"background");
    dump(L, 4);
    if(!lua_istable(L, -1)) 
        error(L,"`background` is not valid color table");
    dump(L, 5);

    color->red = getfiled("r");
    dump(L, 6);
    color->green = getfiled("g");
    dump(L, 7);
    color->blue = getfiled("b");
    dump(L, 8);
}

int main(void) {
    L = luaL_newstate();
    struct Color c_0 = {0, 0, 0};
    load_config("config_tab.lua", &c_0);
    show_color(&c_0);
}
