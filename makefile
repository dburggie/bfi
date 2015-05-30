

INC = -Isource
COPT = -Wall
CC = gcc ${COPT} ${INC}

OBJ = build/readFile.o build/interpreter.o build/io.o build/main.o

EXE = bfi
BLD = build
INSTALLDIR = ~/bin

all: ${BLD} ${OBJ} ${EXE}

clean:
	rm -f ${EXE} ${OBJ}

install: ${INSTALLDIR} ${EXE}
	cp ${EXE} ${INSTALLDIR}/

${BLD}:
	mkdir -p ${BLD}

build/readFile.o: source/readFile.c source/readFile.h
	${CC} -o $@ -c $<

build/interpreter.o: source/interpreter.c source/interpreter.h source/io.h
	${CC} -o $@ -c $<

build/io.o: source/io.c source/io.h
	${CC} -o $@ -c $<

build/main.o: source/main.c source/readFile.h source/interpreter.h
	${CC} -o $@ -c $<

${EXE}: ${OBJ}
	${CC} -o $@ $^

${INSTALLDIR}:
	mkdir -p ${INSTALLDIR}
