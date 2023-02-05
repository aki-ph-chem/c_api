CXX = gcc
CXX_FLAGS =  -llua -ldl

f = lua
n = 0
fl = ${f}_${n}

${fl}.out : ${fl}.c
	${CXX} -o $@ $< ${CXX_FLAGS}

run: ${fl}.out
	./${fl}.out

clean:
	rm *.out

.PHONY: clean run 
