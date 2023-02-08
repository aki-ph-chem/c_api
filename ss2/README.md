## 25

Cプログラムの設定ファイルとしてのLua。Luaを用いない簡単な方法では環境変数として渡す方法や、textファイルとして渡す方法がある。
しかし、textファイルとして渡す方法ではtextをパースする必要があり面倒くさい。

## APIのメモ

- lua_gettable(lua_State \*L, int index);
    - stackの一番上に置かれたkeyの値をpopしてtable[key]の値をstackにpushする

