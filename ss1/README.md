## 24

- Luaの値
    - lua_valueという型(union)の値で表す

## stack周りのAPI

- void lua_pushnil(lua_State \*L) 
    - nilの値をstackにpushする
- void lua_pushboolean(lua_State \*L, int bool)
    - bool(int で0かそれ以外か)をstackにpush 
- void lua_pushlstring(lua_State \*L, const char \*s, size_t longth)
    - ヌル終端されていない長さlengthのchar\*型の値をstackにpushする
- void lua_pushstring(lua_State \*L, const char \*s)
    - ヌル終端されている長さlengthのchar\*型の値をstackにpushする

stackのサイズはlua.hにて

```C
#define LUA_MINSTACK	20
```

と定義されている。これは普通に使うにあは十分な大きさであるがもしより多くの容量が必要ならば以下の関数を用いる。

- int lua_checkstack(lua_Stack \*L, int sz)

stackから値を取り出す関数はlua_to\<type\>(lua_State \*L, int index)であるが、
型のチェックを挟みたい場合はlua_is\<type\>(lua_State \*L, int index)を用いる(lua_is\<type\>はマクロ)。

例としては以下がある

- int lua_toboolean(lua_State \*L, int index) 
   - bool値をintして得る 
- double lua_tonumber(lua_State \*L, int index)
   - double値を得る 
- const char\* lua_tostring(lus_State \*L, int index)
   - const char\*を得る 
- size_t lua_strlen(lus_State \*L, int index) 
   - 文字列のサイズを得る 

呼び出す型とstackにある型が一致しなくてもlua_to\<type\>を呼び出すことが可能である。
しかし、lua_toboolean,lua_tonumber, lua_strlenは0を返し、他の関数はNULLを返す。

Lua_is\<type\>を呼ばなくてもLua_to\<type\>を呼び出して、返り値のNULLチェックをすればok

Cの関数の呼び出しが終わるとLuaはstackの中身をクリアするのでLuaのstringへのポインタを関数の外部に保存してはならない。

lua_tostringが返す文字列はヌル終端されている。

## 他のstackの操作

- int lua_gettop(lua_State \*L)
    - topの値のindexを得る

- void lua_settop(lua_State \*L, int index)
    - topの値のindexを特定の値に変更する。新しい値が古い値よりも大きければtopの値は破棄される
    - もしそうでないならばtopにnilをpushする。得にlua_settop(L,0)はstackの中身を全て破棄する(空にする)

負のインデックス-xは正のインデックス-x + 1に等しい。
そのためlua_pop(L,n)は以下のようにマクロとして書ける。
このマクロlua_pop(L,n)はtopからn個の要素をpopする

```C
#define lua_pop(L,n) lua_settop(L, -(n) -1)
```

- void lua_pushvalue(lua_State \*L, int index)
   - indexの位置にある要素をコピーしてtopにプッシュ 

- void lua_remove(lua_State \*L, int index)
   - indexの位置にある要素を削除してシフトダウン

- void lua_insert(lua_State \*L, int index)
   - topにある要素をindexの場所に移動してシフトアップ

- void lua_replace(lua_State \*L, int index)
    - topの値をpopしてindexの位置に動かす 


以下の操作はstackに影響を与えない

```C
lua_settop(L, -1);  /* set top to its current value */
lua_insert(L, -1);  /* move top element to the top */
```

stackの状態を確かめるには以下のようなdump関数を作ると便利である。

```C
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
```
## エラーハンドリング

ほぼ全てのLua APIの関数はerrのコードを返す代わりに例外を投げる(longjmpをcallする)

典型的なアプリケーションではプロテクトされずに実行される。
この状態では"not enough memory"のようなエラーに対してできることは大してない。
pnic関数を呼び出して終了するくらいしかない。

全てのAPIの関数が例外を投げるわけではない。lua_close,lua_pcall, lua_loadはsafeである。
多くの関数はluaL_loadfile failsのようなメモリアロケーションのエラーに対してのみ例外を投げる。

いくつかのプログラムではメモリ不足でできることは無いので例外を無視する。
この場合ではpanicする。

もし、メモリアロケーションエラーでプログラムを終了したくないならば、プロテクトモードで実行する必要がある。
p_callを介して呼び出される関数はプロテクトモードで実行される。
プロテクトモードではメモリアロケーションエラーが起こってもインタープリンタは一貫した状態を保つ。
Cの関数をLuaからプロテクトモードで呼び出すにはlua_cpcall関数を使えばよい。(詳細はreferenceマニュアルかソース中のlua.c)

Luaは型安全である(Cは型安全でない)しかしCで拡張した場合、その安全性が破られることがある。
そのため、安全で十分なエラーハンドリングが求められる。

CでLuaのライブラリを書く際の標準的なエラーハンドリング法はエラーを検知した時にlua_errorを呼ぶことである。
lua_error関数はクリアすべきものを全てクリアして呼び出し元のlua_pcallに巻き戻してエラーメッセージを出す。
