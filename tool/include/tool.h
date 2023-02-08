#ifndef LIB_H_ 
#define LIB_H_

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <wchar.h>
#include <stdarg.h>

void stack_dump(lua_State* L);
void error(lua_State *L, const char* fmt, ...);

#endif //LIB_H_
      
