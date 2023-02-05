#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

//A First Example: 簡単なREPL

int main (void) {
    char buff[256];
    int error;
    lua_State *L = luaL_newstate();   /* opens Lua */
    luaL_openlibs(L);                 /* opens Lua libs */

    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        /* luaL_loadbuffer: コードのチャンクをバッファから読んで、コンパイルする. 正常終了で0を返す */
        /* lua_pcall: コンパイルされたバイトコードをVM上で実行する. 正常終了で0を返す */
        error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
            lua_pcall(L, 0, 0, 0);
        if (error) {
            /* バッファへの書き込み、コンパイルでエラーが発生するとエラーメッセージがstack上にpushされる.
              なのでそれをstring(char*)として取り出す */
            fprintf(stderr, "%s", lua_tostring(L, -1));
            lua_pop(L, 1);  /* pop error message from the stack */
        }
    }

    lua_close(L);
    return 0;
}
