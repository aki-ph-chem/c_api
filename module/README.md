# モジュール関係

## path

## パッケージ

とりあえず、簡単なパッケージを作ってみた。
今の方法ではパッケージを構成するソースコードの名前が他のパッケージと衝突する可能性がある。
もう少しモトモな方法はまた後でまとめる。

### luarocksの導入

Linuxのパッケージマネージャよりインストールする。

```bash
$ sudo pacman -S luarocks
```

luarocksをインストールしただけではluarocksが管理するディレクトリがLua側から認識されない(PATHが通っていない)状態であるので.bashrcに

```bsh
$(luarocks path)
```

として環境変数LUA_PATH,LUA_CPATHを設定する。

### パッケージの生成

1. \*.rockspecを書く

モジュールの入っているpathに\<package_name\>-\<version\>.rockspecを生成する。

注意点は各フィールドのうちpackage,versionは
\*.rockspecのファイル名を構成する\<package_name\>, \<version\>と揃える。

2.  パッケージのbuild(& install)

\*.rockspecがあるディレクトリで

```bash
$ luarocks --local make
```

を実行する。--localがある場合はlocal(/home/\<user_name\>)以下のインストールされる。
ない場合ではシステムのpathにインストールするためroot権が必要となる。

```bash
$ sudo luarocks make
```

パッケージの削除は

```bash
$ luarocks --local remove \<package_name\>
```

とすればよく

パッケージ情報の確認は

```bash
$ luarocks show \<package_name\> 
```

とすれば可能である。
