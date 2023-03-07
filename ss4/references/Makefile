CXX = gcc
OPT = -g -O1 # debug
MY_TOOL = -L ../tool -ltool  -I ../tool/include # my tool
CXX_FLAGS =  -llua -ldl 
f = ref
n = 0
fl = ${f}_${n}

${fl}.out : ${fl}.c
	${CXX} -o $@ $< ${CXX_FLAGS}

run: ${fl}.out
	./${fl}.out

clean:
	rm *.out

.PHONY: clean run 
