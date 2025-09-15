CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
OBJ = main.o editor.o terminal.o buffer.o

dte: $(OBJ)
	$(CC) $(CFLAGS) -o dte $(OBJ)

main.o: main.c editor.h terminal.h
editor.o: editor.c editor.h
terminal.o: terminal.c terminal.h
buffer.o: buffer.c buffer.h

clean:
	rm -f dte $(OBJ)