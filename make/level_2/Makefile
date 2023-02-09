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

