

INC = -Isource
COPT = -Wall
CC = gcc ${COPT} ${INC}

OBJ = build/interpreter.o build/io.o build/main.o

EXE = bfi
BLD = build
INSTALLDIR = ~/bin

all: ${BLD} ${OBJ} ${EXE}

clean:
	rm -f ${EXE} ${OBJ}

install: ${INSTALLDIR}/${EXE}

${INSTALLDIR}/${EXE}: ${INSTALLDIR} ${EXE}
	cp ${EXE} ${INSTALLDIR}/${EXE}

${BLD}:
	mkdir -p ${BLD}

build/interpreter.o: source/interpreter.c source/interpreter.h source/io.h
	${CC} -o $@ -c $<

build/io.o: source/io.c source/io.h
	${CC} -o $@ -c $<

build/main.o: source/main.c source/interpreter.h source/io.h
	${CC} -o $@ -c $<

${EXE}: ${OBJ}
	${CC} -o $@ $^

${INSTALLDIR}:
	mkdir -p ${INSTALLDIR}
