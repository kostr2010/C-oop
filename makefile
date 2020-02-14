CC = gcc
CFLAGS = -I. -Wall -g
PROG = main
PROG_OBJ = hmap.o tree.o list.o main.o
PROG_LIB = map.h hmap.h tree.h list.h

all: echo $(PROG) clear

echo:
	@ echo sneaky echo

$(PROG): $(PROG_OBJ) $(PROG_LIB)
	$(CC) -o $@ $(PROG_OBJ)

clear:
	rm -rf *.o

