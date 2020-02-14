CC = gcc
CFLAGS = -I. -Wall -g
PROG = main
PROG_OBJ = hmap.o tree.o list.o main.o

all: $(PROG) clear

$(PROG): map.h hmap.h  tree.h  list.h $(PROG_OBJ)
	$(CC) -o $@ $(PROG_OBJ)

clear:
	rm -rf *.o

