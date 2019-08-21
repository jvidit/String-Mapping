CC=g++
CFLAGS=-g -Wall
RM=/bin/rm -f

all:	assign1
StateDashMove.o: StateDashMove.h StateDashMove.cpp
	${CC} ${CFLAGS} -c StateDashMove.cpp
main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp
task2:main.o StateDashMove.o 
	${CC} ${CFLAGS} -o assign1 main.o StateDashMove.o
clean:
	${RM} *.o assign1
