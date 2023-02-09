CC = gcc
greet: main.c greet.c add.c
	${CC} -o $@ $^

run: greet
	./greet

clean:
	rm greet

.PHONY: clean run

