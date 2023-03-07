# 27

## Array Manipulation

array: tableの特別なケースを扱うAPIとしては以下の関数がある。

```C
void lua_rawgeti (lua_State *L, int index, int key);
void lua_rawseti (lua_State *L, int index, int key);
```

ここで第二引数のindexはstackの中でtableオブジェクトを指すindexで第三引数のkeyはtableオブジェクトの中での要素のindex

lua_pushnumber(L, key)は以下の処理に等しい。

```C
lua_pushnumber(L, key);
lua_rawget(L, t);
```

tが正なら(もしそうでないならばスタック内の新しいアイテムに対して補正を行う必要がある)

lua_rawseti(L, t, key)は以下の処理に等しい

```C
lua_pushnumber(L, key);
lua_insert(L, -2); /* put `key` below previous value*/
lua_rawset(L, t);
```

以前書いたl_dir関数の主要な部分以下のように書き換えることができる。

```C
lua_pushnumber(L, i++); /* key */
lua_pushstring(L, entry->d_name); /* value */
lua_settable(L, -3);
```

から

```C
lua_pushstring(L, entry->d_name); /* value */
lua_rawseti(L, -2, i++); /* set table at key `i` */
```

と書き換える。

map関数: 配列の各要素に対して関数を適用させる関数

```C
int l_map(lua_State *L) {
    /* 1st argument must be a table (t) */
    luaL_checktype(L, 1, LUA_TTABLE);

    /* 2nd argument must be a function (f) */
    luaL_checktype(L, 2, LUA_TFUCTION);

    int n = luaL_getn(L ,1); /* get size of table */ 

    for(int i = 1; i <= n; ++i) {
        lua_pushvalue(L, 2); /* push f */
        lua_rawgeti(L , 1, i); /* push t[i] */
        lua_call(L, 1, 1); /* call f(t[i]) */
        lua_rawseti(L, 1, i); /* t[i] = result */
    }

    return 0;
}
```

以下にmap関数で用いた関数についてまとめる。

- luaL_getn(L, t): index t の位置にある配列おサイズを得る。
    - tableオブジェクトのtable.getnはluaL_getnを呼び出している。 

- lua_call(lua_State \*L, int nargs, int results);
    - lua_pcallとはエラー処理を以外では同じ関数である。
    - またlua_pcallはエラーコードをreturnするがlua_callはreturnしないで例外を投げる。

基本的には例外をキャッチしたので`lua_call`よりも`lua_pcall`を使うべきである。

## String Manipulation 

### 分割

文字列の先頭のアドレスからlenバイト文の文字列をstackにpushする

```C
lua_pushlstring(lua_State *L, const char *s, size_t len);
```

`string.h`で定義される関数でsの指す文字列の中でc(char型にキャストされる)が最初に位置を捜す。
null文字は一部とみなす。
返り値はcへのポインタを返し、cが見つからない場合ではNULLを返す。

```C
char* strchr(const char *s, int c);
```

### 連結

```C
const char* lua_pushfstring(lua_State *L, const char *fmt, ...);
```

基本的には`stdio.h`の`sprintf`と同じであるが、書き込み先のバッファのポンタが引数にないことや、
シーケンスが`sprintf`ほど豊富でない。たとえばflags,widths,precisionsはない。

以下にシーケンスを挙げる。

- '%%'
    - 文字として'%'を挿入する
- '%s' 
    - ヌル終端された文字列をサイズ指定なしで挿入する
- '%f'
    - lua_Number型の数値を挿入する
- '%I'
    - lua_Integer型の数値を挿入する 
- '%p'
    - ポインタ型の値を挿入する
- '%d'
    - int型の数値
- '%c'
    - １バイト文字を挿入する
- '%U'
    - long intをUTF-8 のバイト列として挿入する

stackのtopからn個をポップして結合し、その結果をstackのtopにpushする。
もしnが0ならば空の文字列をpushする

```C
void lua_concat(lua_State *L, int n);
```

関数の引数がstringかどうかをチェックする。lがNULLでないならばstringのサイズが格納される。

```C
const char *luaL_checklstring(lua_State *L, int arg, size_t *l);
```

バイトcをluaL_Bufferに書き込む

```C
void luaL_addchar(luaL_Buffer *B, char c);
```

バッファBの内容をstackにpushする

```C
void luaL_pushresult(luaL_Buffer *B);
```

`luaL_Buffer`を初期化する。一度初期化されると`lua_State`Lのコピーを保持する。

```C
void luaL_buffinit(lua_State *L, luaL_Buffer *B);
```
`luaL_addlstring`は指定したサイズの文字列をバッファに渡す。
一方`luaL_addstring`はnull終端された文字列をバッファに渡す。

```C
void luaL_addlstring(luaL_Buffer *B, const char *s, size_t l);
void luaL_addstring(luaL_Buffer *B, const char *s);
```

## Registry

C側ではLuaのgenericな値を保持することができない。
また、その変数を使うライブラリは複数のLua statesで共有することはできない。

対応策としてLuaのグローバル変数を使う方法がある。
しかし、Lua側から変数が改ざんされてCのデータの整合性を損なう可能性がある。

この問題を回避するためにLuaはC側からのみ自由にアクセスが可能なregistryと呼ばれるテーブルを持っている。

レジストリはCにおいてすべて共有されるので、keyの名前には注意しなければならない。
keyの名前が衝突しないようにする方法の一つとして静的な変数のアドレスを用いる方法がある。
(静的な変数のアドレスはリンカーが衝突しないように割り振るので)

この方法を使うためには

```C
void lua_pushlightuserdata(lua_State *L, void *p);
```

を用いてCのポインタ変数を(void\*)にキャストしてからstack上にpushする。


もちろん普通の文字列をkeyにすることも可能である。(自由にアクセスできるライブラリ等では良い方法である)

## Reference
