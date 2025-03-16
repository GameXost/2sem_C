CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c oper.c
OBJ = $(SRC:.c=.o)
EXEC = program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c linked_list.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
