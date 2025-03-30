CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c oper.c
OBJ = main.o oper.o
EXEC = program.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: main.c linked_list.h
	$(CC) $(CFLAGS) -c main.c -o main.o

oper.o: oper.c linked_list.h
	$(CC) $(CFLAGS) -c oper.c -o oper.o

clean:
	-del /F /Q $(OBJ) $(EXEC) 2> NUL
