# 学び直しMakefile

- 参考
    - [A Simple Makefile Tutorial](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)

## level_1, level_2

level_1, level_2ではソースコード、ヘッダファイルは以下のように同じ階層のディレクトリに格納している。

```
.
├── add.c
├── add.h
├── greet.c
├── greet.h
├── main.c
└── Makefile
```

### [level_1](./level_1)

とりあえず、makeでビルドするように書いたレベル。
どれか一つのソースファイルを書き換えただけでも全てのソースコードをコンパイルし直すため非効率。
ヘッダファイルの変化には対応しない。

- @
    - ターゲットの名前を表す自動変数 
- ^
    - 材料全てを表す自動変数

```Makefile
CC = gcc
greet: main.c greet.c add.c
	${CC} -o $@ $^

run: greet
	./greet

clean:
	rm greet

.PHONY: clean run
```

### [level_2](./level_2)

level_1と比べて、一旦オブジェクトファイル(\*o)を生成してからリンクをして実行ファイルを生成するようにした。
このことにより差分コンパイルが可能となった。
また、ヘッダファイルの変化にも対応した。

- %.o : %.c
    - 全ての\*.cからより上流の材料として要求される\*.oを生成

```Makefile
CC = gcc
CFLAFS = -I
DEPS = greet.h

%.o: %.c ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

greet: main.o greet.o add.o 
	${CC} -o $@ $^

run: greet
	./greet

clean:
	rm greet *.o

.PHONY: clean run
```

## level_3, level_4

level_1, level_2ではソースファイル、ヘッダファイルを全て同じ階層のディレクトリに格納したいた。
しかし、これでは非常に見通しが悪い。そのため以下のようにファイルを分散させた。

```
.
├── include
│   ├── add.h
│   └── greet.h
├── main.c
├── Makefile
└── src
    ├── add.c
    └── greet.c

```

### [level_3](./level_3)

ファイル郡を分散化して、オブジェクトファイルの生成->リンクと進むように書いた。


```Makefile
CC = gcc
INCLUDE = ./include
CFLAGS = -I ${INCLUDE}
OBJ = main.o greet.o add.o

greet: ${OBJ} 
	${CC} -o $@ $^

main.o : main.c  ${INCLUDE}/*.h
	${CC} -c -o $@ ${CFLAGS} $<

%.o: ./src/%.c ${INCLUDE}/%.h
	${CC} -c $< 

run: greet
	./greet

clean:
	rm greet *.o

.PHONY: clean run

```
### [level_4](./level_4)

生成したオブジェクトファイルから一旦静的ライブラリを生成して、staticリンクで実行ファイルを生成する。

```Makefile
CC = gcc
INCLUDE = ./include
LIB_NAME = my_tool
OBJ = greet.o add.o

greet: main.o lib${LIB_NAME}.a
	${CC} -o $@ $< -L ./ -l${LIB_NAME}

main.o : main.c  ${INCLUDE}/*.h
	${CC} -c -o $@ -I ${INCLUDE} $<

lib${LIB_NAME}.a : ${OBJ} 
	ar rcs $@ -o $^

%.o: ./src/%.c ${INCLUDE}/%.h
	${CC} -c $< 

run: greet
	./greet

clean:
	rm greet *.o *.a

.PHONY: clean run

```

